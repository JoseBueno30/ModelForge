#include <ui/view/GeneralizationItemView.h>

#include <ui/components/ThemeManager.h>

GeneralizationItemView::GeneralizationItemView(ClassItemView* superClass, ClassItemView* subClass) : superClass(superClass), subClass(subClass){
    superClass->addGeneralization(this);
    subClass->addGeneralization(this);

    setZValue(-1);
    updatePosition();

    setFlag(QGraphicsItem::ItemIsSelectable);
}

void GeneralizationItemView::updatePosition(){
    if(!superClass || !subClass) throw std::runtime_error("ERROR: No hay clases en la asociacion.");

    QRectF class1Rect = superClass->boundingRect();
    QRectF class2Rect = subClass->boundingRect();

    QLineF line(class1Rect.center() + superClass->scenePos(), class2Rect.center() + subClass->scenePos());

    QPointF p1 = getNearestEdgeIntersection(QRectF(superClass->scenePos().x(), superClass->scenePos().y(),
                                                   class1Rect.width(), class1Rect.height()), line, p1);
    QPointF p2 = getNearestEdgeIntersection(QRectF(subClass->scenePos().x(), subClass->scenePos().y(),
                                                   class2Rect.width(), class2Rect.height()), line, p2);
    setP1(p1);
    setP2(p2);
    update();
}

QPointF GeneralizationItemView::getNearestEdgeIntersection(const QRectF &rect, const QLineF &line, const QPointF& last){
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

    return polygon.boundingRect().center();
}

QRectF GeneralizationItemView::boundingRect() const {return QRectF(p1, p2).normalized().adjusted(-10, -10, 10, 10);}


void GeneralizationItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!superClass || !subClass) return;

    lineColor = this->isSelected() ? QColor(Qt::blue) : ThemeManager::getAssociationColor();

    painter->setPen(QPen(lineColor, 1, Qt::SolidLine,Qt::FlatCap));
    QLineF line(this->p2, this->p1);

    QPointF newP2 = drawArrowHead(line, painter);
    line.setP2(newP2);

    painter->drawLine(line);

    // TODO paint multiplicity and name
}

QPointF GeneralizationItemView::drawArrowHead(QLineF &line, QPainter *painter){
    double angle = std::atan2(-line.dy(), line.dx()) - M_PI_2;

    qreal arrowSize = 12;
    QPointF head(line.pointAt(0.99));

    QPointF arrowP1 = head + QPointF(std::sin(angle + M_PI / 6) * arrowSize, std::cos(angle + M_PI / 6) * arrowSize);
    QPointF arrowP2 = head + QPointF(std::sin(angle - M_PI / 6) * arrowSize, std::cos(angle - M_PI / 6) * arrowSize);

    QPolygonF arrowHead;
    arrowHead << head << arrowP1 << arrowP2;

    painter->drawPolygon(arrowHead);

    return QPointF((arrowP1.x() + arrowP2.x()) / 2, (arrowP1.y() + arrowP2.y()) / 2);
}

QPainterPath GeneralizationItemView::shape() const{
    QPainterPath path;
    QPen pen(Qt::black, 2); // ancho real del trazo que se dibuja
    path.moveTo(this->getP1());
    path.lineTo(this->getP2());

    QPainterPathStroker stroker;
    stroker.setWidth(pen.widthF() + 6); // área de "tolerancia" al clic
    return stroker.createStroke(path);
}


ClassItemView* GeneralizationItemView::getSuperClass(){
    return this->superClass;
}

ClassItemView* GeneralizationItemView::getSubClass(){
    return this->subClass;
}

void GeneralizationItemView::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (shape().contains(event->pos())) {
        setSelected(true);
    }
}
