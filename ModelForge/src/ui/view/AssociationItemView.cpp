#include <ui/view/AssociationItemView.h>

AssociationItemView::AssociationItemView(shared_ptr<MetaModel::MetaAssociation> model, ClassItemView* class1, ClassItemView* class2)
    : model(model), class1(class1), class2(class2){

    class1->addAssociation(this);
    class2->addAssociation(this);

    setZValue(-1);
    updatePosition();
}

void AssociationItemView::updatePosition(){
    if(!class1 || !class2) throw std::runtime_error("ERROR: No hay clases en la asociacion.");

    QRectF class1Rect = class1->boundingRect();
    QRectF class2Rect = class2->boundingRect();

    //qDebug() << class1Rect << "\t" <<class2Rect;

    //qDebug() << class1Rect.center() + class1->scenePos() << "\t" << class2Rect.center() + class2->scenePos();

    QLineF line(class1Rect.center() + class1->scenePos(), class2Rect.center() + class2->scenePos());

    QPointF p1 = getNearestEdgeIntersection(QRectF(class1->scenePos().x(), class1->scenePos().y(),
                                                   class1Rect.width(), class1Rect.height()), line, p1);
    QPointF p2 = getNearestEdgeIntersection(QRectF(class2->scenePos().x(), class2->scenePos().y(),
                                                   class2Rect.width(), class2Rect.height()), line, p2);
    setP1(p1);
    setP2(p2);
    update();
    qDebug() << "P1: " << this->p1 << "\tP2:" << this->p2;
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

    return polygon.boundingRect().center(); // Fallback
}

void AssociationItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!class1 || !class2) return;

    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine,Qt::FlatCap));
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

QRectF AssociationItemView::boundingRect() const {return QRectF(p1, p2).normalized().adjusted(-10, -10, 10, 10);}
QRectF AssociationItemView::associationNameRect(){return QRectF();}


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

    if(filled) painter->setBrush(Qt::white);

    painter->drawPolygon(diamondHead);
    return diamondP3;
}

QPointF AssociationItemView::getP1()const{
    return this->p1;
}
QPointF AssociationItemView::getP2() const{
    return this->p2;
}
QGraphicsItem* AssociationItemView::getClass1() const{
    return this->class1;
}
QGraphicsItem* AssociationItemView::getClass2() const{
    return this->class2;
}
shared_ptr<MetaModel::MetaAssociation> AssociationItemView::getAssociationModel(){
    return this->model;
}
