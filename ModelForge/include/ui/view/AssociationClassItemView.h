#ifndef ASSOCIATIONCLASSITEMVIEW_H
#define ASSOCIATIONCLASSITEMVIEW_H


#include <ui/view/ClassItemView.h>

#include <metamodel/MetaAssociationClass.h>

class AssociationClassItemView : public ClassItemView{
public:
    AssociationClassItemView(MetaModel::MetaAssociationClass);
};

#endif // ASSOCIATIONCLASSITEMVIEW_H
