#ifndef ENUMITEMVIEW_H
#define ENUMITEMVIEW_H

#include <QGraphicsItem>

#include <metamodel/MetaEnum.h>


class EnumItemView : public QGraphicsItem{
public:
    EnumItemView(MetaModel::MetaEnum model);
};

#endif // ENUMITEMVIEW_H
