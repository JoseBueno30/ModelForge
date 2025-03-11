#include <ui/view/GeneralizationItemView.h>

GeneralizationItemView::GeneralizationItemView(ClassItemView* superClass, ClassItemView* subClass) : superClass(superClass), subClass(subClass){
    superClass->addGeneralization(this);
    subClass->addGeneralization(this);

    setZValue(-1);
    updatePosition();
}

void GeneralizationItemView::updatePosition(){
    if(!superClass || !subClass) throw std::runtime_error("ERROR: No hay clases en la asociacion.");

    QRectF class1Rect = superClass->boundingRect();
    QRectF class2Rect = subClass->boundingRect();

    //qDebug() << class1Rect << "\t" <<class2Rect;

    //qDebug() << class1Rect.center() + class1->scenePos() << "\t" << class2Rect.center() + class2->scenePos();

    QLineF line(class1Rect.center() + superClass->scenePos(), class2Rect.center() + subClass->scenePos());

    QPointF p1 = getNearestEdgeIntersection(QRectF(superClass->scenePos().x(), superClass->scenePos().y(),
                                                   class1Rect.width(), class1Rect.height()), line, p1);
    QPointF p2 = getNearestEdgeIntersection(QRectF(subClass->scenePos().x(), subClass->scenePos().y(),
                                                   class2Rect.width(), class2Rect.height()), line, p2);
    setP1(p1);
    setP2(p2);
    update();
    qDebug() << "P1: " << this->p1 << "\tP2:" << this->p2;

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

    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine,Qt::FlatCap));
    QLineF line(this->p2, this->p1);
    //qDebug() << line;
    // Arrow metrics:
    // drawArrow(line, painter);
    // line.setLength(92.5);
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

    //painter->setBrush(Qt::white);
    painter->drawPolygon(arrowHead);

    return QPointF((arrowP1.x() + arrowP2.x()) / 2, (arrowP1.y() + arrowP2.y()) / 2);
}
