#ifndef CLASSITEMVIEW_H
#define CLASSITEMVIEW_H

#include <ui/ClassItemModel.h>

#include <QGraphicsItem>
#include <QPainter>

class ClassItemView : public QGraphicsItem{
public:
    ClassItemView(ClassItemModel *model);

    QRectF boundingRect() const override;
    QRectF classNameRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ClassItemModel * model;
    int x,y,width,height;

    void calculateMinimumSize();

};

#endif // CLASSITEMVIEW_H
