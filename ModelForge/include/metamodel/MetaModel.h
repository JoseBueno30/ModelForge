#ifndef METAMODEL_H
#define METAMODEL_H

#include "MetaAssociation.h"
#include "MetaAssociationClass.h"
#include "MetaClass.h"
#include "MetaElement.h"
#include "MetaEnum.h"

#include <string>
#include <memory>
#include <map>

namespace MetaModel{

class MetaModel : public MetaElement{
private:
    std::string name;
    std::map<std::string, std::shared_ptr<MetaEnum>> enums;
    std::map<std::string, std::shared_ptr<MetaClass>> classes;
    std::map<std::string, std::shared_ptr<MetaAssociation>> associations;
    std::map<std::string, std::shared_ptr<MetaAssociationClass>> associationClasses;

public:
    MetaModel(const std::string& name);

    std::string getName() const;
    void setName(const std::string& name);

    const std::map<std::string, std::shared_ptr<MetaEnum>>& getEnums() const;
    std::shared_ptr<MetaEnum> getEnum(const std::string& key);
    void addEnum(std::shared_ptr<MetaEnum> modelEnum);
    void removeEnum(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaClass>>& getClasses() const;
    std::shared_ptr<MetaClass> getClass(const std::string& key);
    void addClass(std::shared_ptr<MetaClass> modelClass);
    void removeClass(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaAssociation>>& getAssociations() const;
    std::shared_ptr<MetaAssociation> getAssociation(const std::string& key);
    void addAssociation(std::shared_ptr<MetaAssociation> modelAssociation);
    void removeAssociation(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaAssociationClass>>& getAssociationClasses() const;
    std::shared_ptr<MetaAssociationClass> getAssociationClass(const std::string& key);
    void addAssociationClass(std::shared_ptr<MetaAssociationClass> modelAssociationClass);
    void removeAssociationClass(const std::string& key);

    bool modelContainsKey(const std::string& key);

    void accept(ModelToText::VisitorInterface& visitor) const override;
};

}

#endif // METAMODEL_H
