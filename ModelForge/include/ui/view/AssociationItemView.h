#ifndef ASSOCIATIONITEMVIEW_H
#define ASSOCIATIONITEMVIEW_H

#include <ui/view/ClassItemView.h>
#include <QGraphicsItem>
#include <QPainter>
#include <metamodel/MetaAssociation.h>
using std::shared_ptr;


class AssociationItemView : virtual public QGraphicsItem{
public:
    AssociationItemView(shared_ptr<MetaModel::MetaAssociation> model,
                        ClassItemView* class1,
                        ClassItemView* class2);

    QRectF associationNameRect();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition();

    QPointF getP1() const;
    QPointF getP2() const;
    QGraphicsItem* getClass1() const;
    QGraphicsItem* getClass2() const;
    shared_ptr<MetaModel::MetaAssociation> getAssociationModel();
    QPointF getNearestEdgeIntersection(const QRectF &rect, const QLineF &line, const QPointF& last);

private:
    shared_ptr<MetaModel::MetaAssociation> model;
    BoxItemView* class1;
    BoxItemView* class2;
    QPointF p1;
    QPointF p2;

    void drawArrow(QLineF &line, QPainter *painter);
    QPointF drawDiamond(QLineF &line, QPainter *painter, bool filled);

    void setP1(QPointF p){this->p1 = p;}
    void setP2(QPointF p){this->p2 = p;}
};

#endif // ASSOCIATIONITEMVIEW_H
