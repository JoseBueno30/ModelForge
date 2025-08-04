#ifndef VISITORINTERFACE_H
#define VISITORINTERFACE_H

#include <metamodel/MetaModel.h>

#include <any>

namespace ModelToText {

class VisitorInterface{
private:


public:
    virtual std::any visit(const MetaModel::MetaModel& metaModel) = 0;

    virtual std::any visit(const MetaModel::MetaEnum& metaEnum) = 0;

    virtual std::any visit(const MetaModel::MetaClass& metaClass) = 0;

    virtual std::any visit(const MetaModel::MetaAssociation& metaAssociation) = 0;

    virtual std::any visit(const MetaModel::MetaAssociationClass& metaAssociationClass) = 0;

    virtual std::any visit(const MetaModel::MetaAttribute& metaAttribute) = 0;

    virtual std::any visit(const MetaModel::MetaOperation& metaOperation) = 0;

    virtual std::any visit(const MetaModel::MetaConstraint& metaConstraint) = 0;

    virtual std::any visit(const MetaModel::MetaAssociationEnd& metaAssociatonEnd) = 0;

    virtual std::any visit(const MetaModel::SimpleType& simpleType) = 0;

    virtual std::any visit(const MetaModel::CollectionType& collectionType) = 0;

    virtual std::any visit(const MetaModel::TupleType& tupleType) = 0;
};

}

#endif // VISITORINTERFACE_H
