#include <ui/view/AssociationItemView.h>

#include <ui/components/ModelGraphicsScene.h>
#include <ui/components/ThemeManager.h>

void AssociationItemView::applyOffsetToSharedAssociations(){
    std::vector<AssociationItemView *> associationsShared = class1->associationsShared(class2);
    int cont = 1;
    for(auto association : associationsShared){
        qreal offset = (qreal) cont/(associationsShared.size() + 1);
        //qDebug() << "Offset calculated: " << cont << " / " << (associationsShared.size() + 1) << " = " << offset;

        association->setOffset(offset);
        cont++;
    }
}

AssociationItemView::AssociationItemView(shared_ptr<MetaModel::MetaAssociation> model, ClassItemView* class1, ClassItemView* class2)
    : model(model), class1(class1), class2(class2){

    class1->addAssociation(this);
    class2->addAssociation(this);

    setZValue(-1);

    applyOffsetToSharedAssociations();

    updatePosition();
    setFlag(QGraphicsItem::ItemIsSelectable);
}

ClassesOrientation AssociationItemView::checkOrientation(QRectF& class1Rect, QRectF& class2Rect){
    qreal angle = QLineF(class1Rect.center() + this->class1->scenePos(), class2Rect.center() + this->class2->scenePos()).angle();
    int angleOffset = 20;
    //qDebug() <<"Angulo: " << angle;
    return angle < angleOffset || angle > 360 - angleOffset || (angle > 180 - angleOffset && angle < 180 + angleOffset) ? HORIZONTAL : VERTICAL;
}

void AssociationItemView::updatePosition(){
    //qDebug() << "Offset: " << offset;

    if(!class1 || !class2) throw std::runtime_error("ERROR: No hay clases en la asociacion.");

    QRectF class1Rect = class1->boundingRect();
    QRectF class2Rect = class2->boundingRect();

    //qDebug() << class1Rect << "\t" <<class2Rect;

    //qDebug() << class1Rect.center() + class1->scenePos() << "\t" << class2Rect.center() + class2->scenePos();
    QLineF axis1;
    QLineF axis2;
    if(checkOrientation(class1Rect, class2Rect) == VERTICAL){
        axis1 = QLineF(QPointF(0, class1Rect.center().y()), QPointF(class1->getDimensions().x(), class1Rect.center().y()));
        axis2 = QLineF(QPointF(0, class2Rect.center().y()), QPointF(class2->getDimensions().x(), class2Rect.center().y()));
    }else{
        axis1 = QLineF(QPointF(class1Rect.center().x(), 0), QPointF(class1Rect.center().x(), class1->getDimensions().y()));
        axis2 = QLineF(QPointF(class2Rect.center().x(), 0), QPointF(class2Rect.center().x(), class2->getDimensions().y()));
    }

    QPointF offsetCenter1 = axis1.pointAt(offset);
    QPointF offsetCenter2 = axis2.pointAt(offset);
    QLineF line(offsetCenter1 + class1->scenePos(), offsetCenter2 + class2->scenePos());

    QPointF p1 = getNearestEdgeIntersection(QRectF(class1->scenePos().x(), class1->scenePos().y(),
                                                     class1Rect.width(), class1Rect.height()), line, p1);

    QPointF p2 = getNearestEdgeIntersection(QRectF(class2->scenePos().x(), class2->scenePos().y(),
                                                   class2Rect.width(), class2Rect.height()), line, p2);

    setP1(p1);
    setP2(p2);
    update();
    //qDebug() << "P1: " << this->p1 << "\tP2:" << this->p2;
}

QPointF AssociationItemView::getNearestEdgeIntersection(const QRectF &rect, const QLineF &line, const QPointF& last){
    QPolygonF polygon(rect);
    QLineF edges[] = {
        QLineF(polygon.at(0), polygon.at(1)),  // Top
        QLineF(polygon.at(1), polygon.at(2)),  // Right
        QLineF(polygon.at(2), polygon.at(3)),  // Bottom
        QLineF(polygon.at(3), polygon.at(0))   // Left
    };

    for (const QLineF &edge : edges) {
        QPointF intersection;
        if (edge.intersects(line, &intersection) == QLineF::BoundedIntersection) {
            return intersection;
        }
    }

    return rect.center(); // Fallback
}

void AssociationItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!class1 || !class2) return;
    painter->setPen(QPen(lineColor, 1, Qt::SolidLine,Qt::FlatCap));
    QLineF line(this->p1, this->p2);
    //qDebug() << line;
    // Arrow metrics:
    // drawArrow(line, painter);
    // line.setLength(92.5);
    if(this->model->getType() != 0){
         QPointF newP2 = drawDiamond(line, painter, this->model->getType() == 2);
        line.setP2(newP2);
    }

    painter->drawLine(line);

    // TODO paint multiplicity and name
}

QRectF AssociationItemView::boundingRect() const {return QRectF(p1, p2).normalized().adjusted(-100, -100, 100, 100);}
QRectF AssociationItemView::associationNameRect(){return QRectF();}
QPainterPath AssociationItemView::shape() const{
    QPainterPath path;
    QPen pen(Qt::black, 2); // ancho real del trazo que se dibuja
    path.moveTo(this->getP1());
    path.lineTo(this->getP2());

    // Aumentamos artificialmente el ancho del área sensible
    QPainterPathStroker stroker;
    stroker.setWidth(pen.widthF() + 6); // área de "tolerancia" al clic
    return stroker.createStroke(path);
}


QPointF AssociationItemView::drawDiamond(QLineF &line, QPainter *painter, bool filled){
    double angle = std::atan2(-line.dy(), line.dx()) - M_PI_2;
    qreal diamondSize = 8;
    QPointF head(line.pointAt(0.99));

    QPointF diamondP1 = head + QPointF(std::sin(angle + M_PI / 6) * diamondSize, std::cos(angle + M_PI / 6) * diamondSize);
    QPointF diamondP2 = head + QPointF(std::sin(angle - M_PI / 6) * diamondSize, std::cos(angle - M_PI / 6) * diamondSize);

    QPointF center = (diamondP1 + diamondP2) / 2;
    QPointF diamondP3 = 2 * center - head;

    QPolygonF diamondHead;
    diamondHead << head << diamondP1 << diamondP3 << diamondP2;

    if(filled) painter->setBrush(lineColor);

    painter->drawPolygon(diamondHead);
    return diamondP3;
}

QPointF AssociationItemView::getP1()const{
    return this->p1;
}
QPointF AssociationItemView::getP2() const{
    return this->p2;
}
ClassItemView* AssociationItemView::getClass1() const{
    return this->class1;
}
ClassItemView* AssociationItemView::getClass2() const{
    return this->class2;
}

void AssociationItemView::setClass1(ClassItemView* newClass){
    this->class1 = newClass;
}
void AssociationItemView::setClass2(ClassItemView* newClass){
    this->class2 = newClass;
}

void AssociationItemView::setAssociationClassItem(AssociationClassItemView* associationClass){
    this->associationClass = associationClass;
}
AssociationClassItemView* AssociationItemView::getAssociationClassItem() const{
    return this->associationClass;
}

shared_ptr<MetaModel::MetaAssociation> AssociationItemView::getAssociationModel(){
    return this->model;
}


void AssociationItemView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if (shape().contains(event->pos())) {
        ModelGraphicsScene* scene = dynamic_cast<ModelGraphicsScene*>(this->scene());
        scene->emitEditAssociationSignal(this);
    }
}

void AssociationItemView::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (shape().contains(event->pos())) {
        setSelected(true);
    }
}
