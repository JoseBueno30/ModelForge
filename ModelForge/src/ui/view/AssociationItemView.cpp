#include <ui/view/AssociationItemView.h>

AssociationItemView::AssociationItemView(shared_ptr<MetaModel::MetaAssociation> model, QGraphicsItem* class1, QGraphicsItem* class2)
    : model(model), class1(class1), class2(class2){

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
                                                   class1Rect.width(), class1Rect.height()), line);
    QPointF p2 = getNearestEdgeIntersection(QRectF(class2->scenePos().x(), class2->scenePos().y(),
                                                   class2Rect.width(), class2Rect.height()), line);

    setP1(p1);
    setP2(p2);
    qDebug() << "P1: " << this->p1 << "\tP2:" << this->p2;
}

QPointF AssociationItemView::getNearestEdgeIntersection(const QRectF &rect, const QLineF &line){
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

    return QPoint(); // Fallback
}

void AssociationItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!class1 || !class2) return;

    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine,Qt::FlatCap));
    QLineF line(this->p1, this->p2);

    //TODO DIBUJAR TIPO DE ASOCIACION
    //qDebug() << "tipo: " << this->model->getType();
    if(this->model->getType() == 1){
        drawArrow(line, painter);
        line.setLength(92.5);
    }else if(this->model->getType() == 2){
        drawDiamond(line, painter);
    }


    painter->drawLine(line);
}

QRectF AssociationItemView::boundingRect() const {return QRectF(p1, p2).normalized().adjusted(-2, -2, 2, 2);}
QRectF AssociationItemView::associationNameRect(){return QRectF();}

void AssociationItemView::drawArrow(QLineF &line, QPainter *painter){
    double angle = std::atan2(-line.dy(), line.dx()) - M_PI_2;
    qDebug() << "Angulo: " << angle;
    qreal arrowSize = 8;
    QPointF head(line.pointAt(0.99));

    QPointF arrowP1 = head + QPointF(std::sin(angle + M_PI / 6) * arrowSize, std::cos(angle + M_PI / 6) * arrowSize);
    QPointF arrowP2 = head + QPointF(std::sin(angle - M_PI / 6) * arrowSize, std::cos(angle - M_PI / 6) * arrowSize);

    QPolygonF arrowHead;
    arrowHead << head << arrowP1 << arrowP2;

    //painter->setBrush(Qt::white);
    painter->drawPolygon(arrowHead);
}
void AssociationItemView::drawDiamond(QLineF &line, QPainter *painter){}
