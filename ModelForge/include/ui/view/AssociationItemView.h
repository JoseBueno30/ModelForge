#ifndef ASSOCIATIONITEMVIEW_H
#define ASSOCIATIONITEMVIEW_H

#include <QGraphicsItem>
#include <QPainter>
#include <metamodel/MetaAssociation.h>
using std::shared_ptr;


class AssociationItemView : public QGraphicsItem{
public:
    AssociationItemView(shared_ptr<MetaModel::MetaAssociation> model,
                        QGraphicsItem* class1,
                        QGraphicsItem* class2);

    QRectF associationNameRect();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition();

private:
    shared_ptr<MetaModel::MetaAssociation> model;
    QGraphicsItem* class1;
    QGraphicsItem* class2;
    QPointF p1;
    QPointF p2;

    void drawArrow();
    void drawDiamond();
    QPointF getNearestEdgeIntersection(const QRectF &rect, const QLineF &line);

    void setP1(QPointF p){this->p1 = p;}
    void setP2(QPointF p){this->p2 = p;}

};

#endif // ASSOCIATIONITEMVIEW_H
