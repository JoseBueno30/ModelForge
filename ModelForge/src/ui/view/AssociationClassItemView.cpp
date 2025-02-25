#include <ui/view/AssociationClassItemView.h>

AssociationClassItemView::AssociationClassItemView(std::shared_ptr<MetaModel::MetaAssociationClass> model, BoxItemView* class1, BoxItemView* class2)
    : ClassItemView(model), AssociationItemView(model, class1, class2){
    QPointF center = (this->getP1() + this->getP2()) /2;

    this->ClassItemView::setPosition(center.x() - this->getDimensions().x() / 2, center.y() + 40);
}

QRectF AssociationClassItemView::boundingRect() const {
    qreal margin = 10;
    return this->ClassItemView::boundingRect().united(this->AssociationItemView::boundingRect()).adjusted(-margin, -margin, margin, margin);
}
void AssociationClassItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    this->AssociationItemView::paint(painter, option, widget);
    //qDebug()<<"Scene:" << this->scenePos() << "\tnormal:" << this->pos();
    QPointF center = (this->getP1() + this->getP2()) /2;
    QPointF auxP2(center.x(), center.y() + 40);
    QLineF line(center, auxP2);

    painter->setPen(QPen(Qt::white, 1, Qt::DashLine));
    painter->drawLine(line);
    this->ClassItemView::paint(painter, option, widget);
}
