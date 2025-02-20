#ifndef ASSOCIATIONITEMVIEW_H
#define ASSOCIATIONITEMVIEW_H

#include <QGraphicsItem>

#include <metamodel/MetaAssociation.h>


class AssociationItemView : QGraphicsItem{
public:
    AssociationItemView(MetaModel::MetaAssociation model);
};

#endif // ASSOCIATIONITEMVIEW_H
