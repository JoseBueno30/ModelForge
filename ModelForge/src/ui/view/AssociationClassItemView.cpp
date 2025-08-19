#include "ui/components/ThemeManager.h"
#include <ui/view/AssociationClassItemView.h>

AssociationClassItemView::AssociationClassItemView(std::shared_ptr<MetaModel::MetaAssociationClass> model, ClassItemView* class1, ClassItemView* class2)
    : model(model), classItem(new ClassItemView(std::shared_ptr<MetaModel::MetaClass>(model, model.get()))),
    associationItem(new AssociationItemView(std::shared_ptr<MetaModel::MetaAssociation>(model, model.get()), class1, class2))
{
    QPointF center = (this->associationItem->getP1() + this->associationItem->getP2()) /2;
    class1->addAssociation(this->associationItem);
    class1->addAssociationClass(this);
    class2->addAssociation(this->associationItem);
    class2->addAssociationClass(this);

    associationItem->setAssociationClassItem(this);

    this->classItem->addAssociationClass(this);
    this->classItem->setPos(center.x() - this->classItem->getDimensions().x() / 2, center.y() + 40);
    //this->setPos(this->boundingRect().center());
}

QRectF AssociationClassItemView::boundingRect() const {
    qreal margin = 10;
    QPointF center = (this->associationItem->getP1() + this->associationItem->getP2()) /2;
    QRectF auxRect = this->classItem->sceneBoundingRect();
    QLineF auxLine(center, auxRect.center());
    QPointF p2 = this->associationItem->getNearestEdgeIntersection(auxRect, auxLine, p2);
    return QRectF(center, p2).normalized().adjusted(-100, -100, 100, 100);;
}
void AssociationClassItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // painter->save();
    // painter->translate(this->associationItem->pos());
    // this->associationItem->paint(painter, option, widget);
    // painter->restore();
    //qDebug()<<"Scene:" << this->scenePos() << "\tnormal:" << this->pos();
    QPointF center = (this->associationItem->getP1() + this->associationItem->getP2()) /2;

    QRectF auxRect = this->classItem->sceneBoundingRect();
    QLineF auxLine(center, auxRect.center());
    QPointF p2 = this->associationItem->getNearestEdgeIntersection(auxRect, auxLine, p2);
    // QPointF auxP2(center.x(), center.y() + 40); // TODO Find the nearest class edge and use its center
    QLineF line(center, p2);

    painter->setPen(QPen(QColor(ThemeManager::getAssociationColor()), 1, Qt::DashLine));
    painter->drawLine(line);

    // painter->translate(this->classItem->pos());
    // this->classItem->paint(painter, option, widget);
}

void AssociationClassItemView::addItemsToScene(){
    this->scene()->addItem(this->classItem);
    this->scene()->addItem(this->associationItem);
}

std::shared_ptr<MetaModel::MetaAssociationClass> AssociationClassItemView::getAssociationClassModel(){
    return this->model;
}

ClassItemView* AssociationClassItemView::getClass1(){
    return this->associationItem->getClass1();
}

ClassItemView* AssociationClassItemView::getClass2(){
    return this->associationItem->getClass2();
}

ClassItemView* AssociationClassItemView::getAssociationClassItemView(){
    return this->classItem;
}

AssociationItemView* AssociationClassItemView::getAssociationClassAssociationItemView(){
    return this->associationItem;
}
