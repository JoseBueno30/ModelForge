#ifndef ENUMITEMVIEW_H
#define ENUMITEMVIEW_H

#include <ui/view/BoxItemView.h>
#include <QGraphicsItem>
#include <metamodel/MetaEnum.h>
#include <QPainter>

using std::shared_ptr;

class EnumItemView : public BoxItemView{
public:
    EnumItemView(shared_ptr<MetaModel::MetaEnum> model);
    EnumItemView(shared_ptr<MetaModel::MetaEnum> model, int x, int y, int width, int height);

    QRectF enumNameRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ~EnumItemView();

private:
    shared_ptr<MetaModel::MetaEnum> model;

    void calculateMinimumSize();
};

#endif // ENUMITEMVIEW_H
