#ifndef GENERALIZATIONITEMVIEW_H
#define GENERALIZATIONITEMVIEW_H

#include "ui/view/ClassItemView.h"
#include <QGraphicsItem>


class GeneralizationItemView : public QGraphicsItem{
private:
    ClassItemView *superClass;
    ClassItemView *subClass;

    QPointF p1;
    QPointF p2;

    void setP1(QPointF p){this->p1 = p;}
    void setP2(QPointF p){this->p2 = p;}

    QPointF drawArrowHead(QLineF &line, QPainter *painter);

public:

    GeneralizationItemView(ClassItemView* superClass, ClassItemView* subClass);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    void updatePosition();
    QPointF getNearestEdgeIntersection(const QRectF &rect, const QLineF &line, const QPointF& last);

    ClassItemView* getSuperClass();
    ClassItemView* getSubClass();
};

#endif // GENERALIZATIONITEMVIEW_H
