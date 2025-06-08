#ifndef ENUMITEMVIEW_H
#define ENUMITEMVIEW_H

#include <ui/view/BoxItemView.h>
#include <QGraphicsItem>
#include <metamodel/MetaEnum.h>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <ui/components/ModelGraphicsView.h>

using std::shared_ptr;

class EnumItemView : public BoxItemView{
public:
    EnumItemView(shared_ptr<MetaModel::MetaEnum> model);
    EnumItemView(shared_ptr<MetaModel::MetaEnum> model, int x, int y, int width, int height);

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    QRectF enumNameRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void calculateMinimumSize();

    std::shared_ptr<MetaModel::MetaEnum> getMetaEnumModel();

    virtual ~EnumItemView() = default;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
    shared_ptr<MetaModel::MetaEnum> model;


};

#endif // ENUMITEMVIEW_H
