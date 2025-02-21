#include <metamodel/MetaModel.h>

namespace MetaModel{

MetaModel::MetaModel(const std::string& name)
    : name(name){}

std::string MetaModel::getName() const{
    return name;
}

void MetaModel::setName(const std::string& name){
    this->name = name;
}

const std::map<std::string, std::shared_ptr<MetaEnum>>& MetaModel::getEnums() const{
    return enums;
}

const MetaEnum* MetaModel::getEnum(const std::string& key) const{
    auto iterator = enums.find(key);
    if(iterator != enums.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaModel::addEnum(const std::string& key, std::shared_ptr<MetaEnum> modelEnum){
    if(modelEnum){
        enums[key] = modelEnum;
    }
}

void MetaModel::removeEnum(const std::string& key){
    enums.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaClass>>& MetaModel::getClasses() const{
    return classes;
}

const MetaClass* MetaModel::getClass(const std::string& key) const{
    auto iterator = classes.find(key);
    if(iterator != classes.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaModel::addClass(const std::string& key, std::shared_ptr<MetaClass> modelClass){
    if(modelClass){
        classes[key] = modelClass;
    }
}

void MetaModel::removeClass(const std::string& key){
    classes.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaAssociation>>& MetaModel::getAssociations() const{
    return associations;
}

const MetaAssociation* MetaModel::getAssociation(const std::string& key) const{
    auto iterator = associations.find(key);
    if(iterator != associations.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaModel::addAssociation(const std::string& key, std::shared_ptr<MetaAssociation> modelAssociation){
    if(modelAssociation){
        associations[key] = modelAssociation;
    }
}

void MetaModel::removeAssociation(const std::string& key){
    associations.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaAssociationClass>>& MetaModel::getAssociationClasses() const{
    return associationClasses;
}

const MetaAssociationClass* MetaModel::getAssociationClass(const std::string& key) const{
    auto iterator = associationClasses.find(key);
    if(iterator != associationClasses.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaModel::addAssociationClass(const std::string& key, std::shared_ptr<MetaAssociationClass> modelAssociationClass){
    if(modelAssociationClass){
        associationClasses[key] = modelAssociationClass;
    }
}

void MetaModel::removeAssociationClass(const std::string& key){
    associationClasses.erase(key);
}


}
