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

    std::any visit(MetaModel::MetaModel metaModel) override;

    std::any visit(MetaModel::MetaEnum metaEnum) override;

    std::any visit(MetaModel::MetaClass metaClass) override;

    std::any visit(MetaModel::MetaAssociation metaAssociation) override;

    std::any visit(MetaModel::MetaAssociationClass metaAssociationClass) override;

    std::any visit(MetaModel::MetaAttribute metaAttribute) override;

    std::any visit(MetaModel::MetaOperation metaOperation) override;

    std::any visit(MetaModel::MetaConstraint metaConstraint) override;

    std::any visit(MetaModel::MetaAssociationEnd metaAssociatonEnd) override;

    void save();
};

}

#endif // VISITORUSE_H
