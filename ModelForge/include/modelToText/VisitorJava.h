#ifndef VISITORJAVA_H
#define VISITORJAVA_H

#include "VisitorInterface.h"
#include <metamodel/MetaModel.h>

#include<string>
#include<fstream>
#include <set>

namespace ModelToText {

class VisitorJava: public VisitorInterface{
private:
    std::ofstream outFile;
    std::string directoryPath;
    std::string packageName;
    const std::map<std::string, std::shared_ptr<MetaModel::MetaClass>>* metaClasses;
    std::string globalConstraints;
    std::set<std::string> currentClassImports;


public:
    explicit VisitorJava(const std::string& directoryPath);
    ~VisitorJava();

    std::any visit(const MetaModel::MetaModel& metaModel) override;

    std::any visit(const MetaModel::MetaEnum& metaEnum) override;

    std::any visit(const MetaModel::MetaClass& metaClass) override;

    std::any visit(const MetaModel::MetaAssociation& metaAssociation) override;

    std::any visit(const MetaModel::MetaAssociationClass& metaAssociationClass) override;

    std::any visit(const MetaModel::MetaAttribute& metaAttribute) override;

    std::any visit(const MetaModel::MetaOperation& metaOperation) override;

    std::any visit(const MetaModel::MetaConstraint& metaConstraint) override;

    std::any visit(const MetaModel::MetaAssociationEnd& metaAssociatonEnd) override;

    std::any visit(const MetaModel::SimpleType& simpleType) override;

    std::any visit(const MetaModel::CollectionType& collectionType) override;

    std::any visit(const MetaModel::TupleType& tupleType) override;

    void save();

    std::any visitType(const MetaModel::MetaType& metaType);

    std::string visibilityToString(MetaModel::Visibility vis);
    void manageTypeImport(const std::shared_ptr<MetaModel::MetaType>& metaType);

    std::string simpleTypeToJavaString(const MetaModel::SimpleType& type);
};

}

#endif // VISITORJAVA_H
