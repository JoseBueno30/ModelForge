#include <metamodel/MetaModel.h>
#include<stdexcept>

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
    if (!modelEnum) {
        throw std::invalid_argument("Null enum");
    }

    if (modelContainsKey(key)) {
        throw std::runtime_error("Model already contains element named: " + key);
    }

    enums[key] = modelEnum;
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
    if (!modelClass) {
        throw std::invalid_argument("Null class");
    }

    if (modelContainsKey(key)) {
        throw std::runtime_error("Model already contains element named: " + key);
    }

    classes[key] = modelClass;
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
    if (!modelAssociation) {
        throw std::invalid_argument("Null association");
    }

    if (modelContainsKey(key)) {
        throw std::runtime_error("Model already contains element named: " + key);
    }

    associations[key] = modelAssociation;
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
    if (!modelAssociationClass) {
        throw std::invalid_argument("Null associationClass");
    }

    if (modelContainsKey(key)) {
        throw std::runtime_error("Model already contains element named: " + key);
    }

    associationClasses[key] = modelAssociationClass;
}

void MetaModel::removeAssociationClass(const std::string& key){
    associationClasses.erase(key);
}


bool MetaModel::modelContainsKey(const std::string& key){
    return (enums.find(key) != enums.end()) ||
           (classes.find(key) != classes.end()) ||
           (associations.find(key) != associations.end()) ||
           (associationClasses.find(key) != associationClasses.end());
}

}
