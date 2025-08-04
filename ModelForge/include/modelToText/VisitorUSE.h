#ifndef VISITORUSE_H
#define VISITORUSE_H

#include "VisitorInterface.h"
#include <metamodel/MetaModel.h>

#include<string>
#include<fstream>

namespace ModelToText {

class VisitorUSE : public VisitorInterface{
private:
    std::ofstream outFile;
    const std::map<std::string, std::shared_ptr<MetaModel::MetaClass>>* metaClasses;
    std::unordered_set<std::string> visitedClasses;
    std::string globalConstraints;


public:
    explicit VisitorUSE(const std::string& filename);
    ~VisitorUSE();

    std::any visit(const MetaModel::MetaModel& metaModel) override;

    std::any visit(const MetaModel::MetaEnum& metaEnum) override;

    std::any visit(const MetaModel::MetaClass& metaClass) override;

    std::any visit(const MetaModel::MetaAssociation& metaAssociation) override;

    std::any visit(const MetaModel::MetaAssociationClass& metaAssociationClass) override;

    std::any visit(const MetaModel::MetaAttribute& metaAttribute) override;

    std::any visit(const MetaModel::MetaOperation& metaOperation) override;

    std::any visit(const MetaModel::MetaConstraint& metaConstraint) override;

    std::any visit(const MetaModel::MetaAssociationEnd& metaAssociatonEnd) override;

    std::any visit(const MetaModel::SimpleType& simpleType) override {return 0;};

    std::any visit(const MetaModel::CollectionType& collectionType) override {return 0;};

    std::any visit(const MetaModel::TupleType& tupleType) override {return 0;};

    std::string visibilityToString(MetaModel::Visibility vis);

    void save();
};

}

#endif // VISITORUSE_H
