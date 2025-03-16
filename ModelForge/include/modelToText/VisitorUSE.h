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

    void visit(MetaModel::MetaModel metaModel) override;

    void visit(MetaModel::MetaEnum metaEnum) override;

    void visit(MetaModel::MetaClass metaClass) override;

    void visit(MetaModel::MetaAssociation metaAssociation) override;

    void visit(MetaModel::MetaAssociationClass metaAssociationClass) override;

    void save();
};

}

#endif // VISITORUSE_H
