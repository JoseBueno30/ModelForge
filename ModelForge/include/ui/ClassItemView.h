#ifndef CLASSITEMVIEW_H
#define CLASSITEMVIEW_H

#include <ui/ClassItemModel.h>

#include <QGraphicsItem>
#include <QPainter>

class ClassItemView : public QGraphicsItem{
public:
    ClassItemView(ClassItemModel *model);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ClassItemModel * model;
};

#endif // CLASSITEMVIEW_H
