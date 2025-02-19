#ifndef METAMODEL_H
#define METAMODEL_H

#include "MetaAssociation.h"
#include "MetaAssociationClass.h"
#include "MetaClass.h"
#include "MetaEnum.h"

#include <string>
#include <memory>
#include <vector>

namespace MetaModel{

class MetaModel{
private:
    std::string name;
    std::vector<std::unique_ptr<MetaEnum>> enums;
    std::vector<std::unique_ptr<MetaClass>> classes;
    std::vector<std::unique_ptr<MetaAssociation>> associations;
    std::vector<std::unique_ptr<MetaAssociationClass>> associationClasses;

private:
    MetaModel(const std::string& name);

    std::string getName() const;
    void setName(const std::string& name);

    const std::vector<std::unique_ptr<MetaEnum>>& getEnums() const;
    void addEnum(std::unique_ptr<MetaEnum> modelEnum);
    void removeEnum(int pos);

    const std::vector<std::unique_ptr<MetaClass>>& getClasses() const;
    void addClass(std::unique_ptr<MetaClass> modelClass);
    void removeClass(int pos);

    const std::vector<std::unique_ptr<MetaAssociation>>& getAssociations() const;
    void addAssociation(std::unique_ptr<MetaAssociation> modelAssociation);
    void removeAssociation(int pos);

    const std::vector<std::unique_ptr<MetaAssociationClass>>& getAssociationClasses() const;
    void addAssociationClass(std::unique_ptr<MetaAssociationClass> modelAssociationClass);
    void removeAssociationClass(int pos);
};

}

#endif // METAMODEL_H
