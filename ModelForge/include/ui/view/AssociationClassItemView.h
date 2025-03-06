#ifndef ASSOCIATIONCLASSITEMVIEW_H
#define ASSOCIATIONCLASSITEMVIEW_H


#include "metamodel/MetaAssociationClass.h"
#include <ui/view/AssociationItemView.h>
#include <ui/view/ClassItemView.h>


class AssociationClassItemView : public BoxItemView{
public:
    AssociationClassItemView(std::shared_ptr<MetaModel::MetaAssociationClass> model, ClassItemView* class1, ClassItemView* class2);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addItemsToScene();
private:
    ClassItemView* classItem;
    AssociationItemView* associationItem;
};

#endif // ASSOCIATIONCLASSITEMVIEW_H
