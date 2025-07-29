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

    struct JavaMemberCode {
        std::string name;
        std::string type;

        std::string field;
        std::string getter;
        std::string setter;

        std::string adder = "";
        std::string remover = "";

        std::string paramDeclaration;
        std::string paramSet;
    };

    std::string capitalize(const std::string& name);

    std::any visitType(const MetaModel::MetaType& metaType);

    std::string visibilityToString(MetaModel::Visibility vis);

    std::string simpleTypeToJavaString(const MetaModel::SimpleType& type);

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

};

}

#endif // VISITORJAVA_H
