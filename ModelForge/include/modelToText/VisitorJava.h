#ifndef VISITORJAVA_H
#define VISITORJAVA_H

#include "VisitorInterface.h"
#include <metamodel/MetaModel.h>

#include<string>
#include<fstream>

namespace ModelToText {

class VisitorJava: public VisitorInterface{
private:
    std::string directoryPath;
    const std::map<std::string, std::shared_ptr<MetaModel::MetaClass>>* metaClasses;
    std::string globalConstraints;


public:
    explicit VisitorJava(const std::string& directoryPath);
    ~VisitorJava();

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

#endif // VISITORJAVA_H
