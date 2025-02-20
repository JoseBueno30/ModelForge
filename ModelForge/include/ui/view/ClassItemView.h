#ifndef CLASSITEMVIEW_H
#define CLASSITEMVIEW_H

#include <ui/view/BoxItemView.h>
#include <QPainter>
#include <metamodel/MetaClass.h>

using std::shared_ptr;

class ClassItemView : public BoxItemView{
public:
    ClassItemView(shared_ptr<MetaModel::MetaClass> model);
    ClassItemView(shared_ptr<MetaModel::MetaClass> model, int x, int y, int width, int height);

    QRectF classNameRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ~ClassItemView();

private:
    shared_ptr<MetaModel::MetaClass> model;

    void calculateMinimumSize();

};

#endif // CLASSITEMVIEW_H
