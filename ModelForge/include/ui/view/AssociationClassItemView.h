#ifndef ASSOCIATIONCLASSITEMVIEW_H
#define ASSOCIATIONCLASSITEMVIEW_H


#include <ui/view/AssociationItemView.h>
#include <ui/view/ClassItemView.h>

#include <metamodel/MetaAssociationClass.h>

class AssociationClassItemView : public ClassItemView, public AssociationItemView{
public:
    AssociationClassItemView(std::shared_ptr<MetaModel::MetaAssociationClass> model, BoxItemView* class1, BoxItemView* class2);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // ASSOCIATIONCLASSITEMVIEW_H
