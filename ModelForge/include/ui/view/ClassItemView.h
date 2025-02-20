#ifndef CLASSITEMVIEW_H
#define CLASSITEMVIEW_H

#include <QGraphicsItem>
#include <QPainter>

#include <metamodel/MetaClass.h>

class ClassItemView : public QGraphicsItem{
public:
    ClassItemView(MetaModel::MetaClass *model);
    ClassItemView(MetaModel::MetaClass *model, int x, int y, int width, int height);

    QRectF boundingRect() const override;
    QRectF classNameRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    MetaModel::MetaClass * model;
    int x,y,width,height;

    void calculateMinimumSize();

};

#endif // CLASSITEMVIEW_H
