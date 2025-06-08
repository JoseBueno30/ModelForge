#ifndef GENERALIZATIONITEMVIEW_H
#define GENERALIZATIONITEMVIEW_H

#include "ui/view/ClassItemView.h"
#include <QGraphicsItem>
#include <ui/components/ThemeManager.h>

class GeneralizationItemView : public QGraphicsItem{
private:
    ClassItemView *superClass;
    ClassItemView *subClass;

    QPointF p1;
    QPointF p2;

    QColor lineColor;

    void setP1(QPointF p){this->p1 = p;}
    void setP2(QPointF p){this->p2 = p;}

    QPointF getP1()const{return this->p1;}
    QPointF getP2()const{return this->p2;}

    QPointF drawArrowHead(QLineF &line, QPainter *painter);

public:

    GeneralizationItemView(ClassItemView* superClass, ClassItemView* subClass);

    enum { Type = UserType + 5 };
    int type() const override { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void updatePosition();
    QPointF getNearestEdgeIntersection(const QRectF &rect, const QLineF &line, const QPointF& last);

    ClassItemView* getSuperClass();
    ClassItemView* getSubClass();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override{
        if (change == QGraphicsItem::ItemSelectedChange) {
            if(value.toBool()){
                lineColor = Qt::blue;
            }else{
                lineColor = ThemeManager::getAssociationColor();
            }
        }
        this->update();
        return QGraphicsItem::itemChange(change, value);
    }
};

#endif // GENERALIZATIONITEMVIEW_H
