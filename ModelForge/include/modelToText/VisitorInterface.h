#ifndef VISITORINTERFACE_H
#define VISITORINTERFACE_H

#include <metamodel/MetaModel.h>

#include <any>

namespace ModelToText {

class VisitorInterface{
private:


public:
    virtual std::any visit(MetaModel::MetaModel metaModel) = 0;

    virtual std::any visit(MetaModel::MetaEnum metaEnum) = 0;

    virtual std::any visit(MetaModel::MetaClass metaClass) = 0;

    virtual std::any visit(MetaModel::MetaAssociation metaAssociation) = 0;

    virtual std::any visit(MetaModel::MetaAssociationClass metaAssociationClass) = 0;

    virtual std::any visit(MetaModel::MetaAttribute metaAttribute) = 0;

    virtual std::any visit(MetaModel::MetaOperation metaOperation) = 0;

    virtual std::any visit(MetaModel::MetaConstraint metaConstraint) = 0;

    virtual std::any visit(MetaModel::MetaAssociationEnd metaAssociatonEnd) = 0;
};

}

#endif // VISITORINTERFACE_H
