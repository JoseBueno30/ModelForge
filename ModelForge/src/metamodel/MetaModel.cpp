#include <iostream>
#include <metamodel/MetaModel.h>
#include <modelToText/VisitorInterface.h>
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

std::shared_ptr<MetaEnum> MetaModel::getEnum(const std::string& key){
    auto iterator = enums.find(key);
    if(iterator != enums.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaModel::addEnum(std::shared_ptr<MetaEnum> modelEnum){
    if (!modelEnum) {
        throw std::invalid_argument("Null enum");
    }

    if (modelContainsKey(modelEnum->getName())) {
        throw std::runtime_error("Model already contains element named: " + modelEnum->getName());
    }

    enums[modelEnum->getName()] = std::move(modelEnum);
}

void MetaModel::removeEnum(const std::string& key){
    enums.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaClass>>& MetaModel::getClasses() const{
    return classes;
}

std::shared_ptr<MetaClass> MetaModel::getClass(const std::string& key){
    auto iterator = classes.find(key);
    if(iterator != classes.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaModel::addClass(std::shared_ptr<MetaClass> modelClass){
    if (!modelClass) {
        throw std::invalid_argument("Null class");
    }

    if (modelContainsKey(modelClass->getName())) {
        throw std::runtime_error("Model already contains element named: " + modelClass->getName());
    }

    classes[modelClass->getName()] = std::move(modelClass);
}

void MetaModel::removeClass(const std::string& key){
    auto metaClass = this->getClass(key);
    for(const auto &assocEndPair : metaClass->getAssociationEnds()){
        auto association = assocEndPair.second->getAssociationSharedPtr();

        if(std::dynamic_pointer_cast<MetaAssociationClass>(association)){
            this->removeAssociationClass(association->getName());
        }else{
            this->removeAssociation(association->getName());
        }
    }

    for(const auto &superClassPair: metaClass->getSuperClasses()){
        superClassPair.second->removeChildrenClass(key);
    }

    for(const auto &childrenClassPair: metaClass->getChildrenClasses()){
        childrenClassPair.second->removeSuperClass(key);
    }

    classes.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaAssociation>>& MetaModel::getAssociations() const{
    return associations;
}

std::shared_ptr<MetaAssociation> MetaModel::getAssociation(const std::string& key){
    auto iterator = associations.find(key);
    if(iterator != associations.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaModel::addAssociation(std::shared_ptr<MetaAssociation> modelAssociation){
    if (!modelAssociation) {
        throw std::invalid_argument("Null association");
    }

    if (modelContainsKey(modelAssociation->getName())) {
        throw std::runtime_error("Model already contains element named: " + modelAssociation->getName());
    }

    for(const auto &associationEndPair : modelAssociation->getAssociationEnds()){
        for(const auto &otherAssociationEndPair : modelAssociation->getAssociationEnds()){

            if (associationEndPair != otherAssociationEndPair){
                try{
                    otherAssociationEndPair.second->getClassSharedPtr()->addAssociationEnd(associationEndPair.second);
                    associationEndPair.second->getClassSharedPtr()->addAssociationEnd(otherAssociationEndPair.second);
                }catch(std::invalid_argument e){}
            }
        }
    }

    associations[modelAssociation->getName()] = std::move(modelAssociation);

}

void MetaModel::removeAssociation(const std::string& key){
    auto association = this->getAssociation(key);
    if(association){
        for(const auto &associationEndPair : association->getAssociationEnds()){
            association->removeAssociationEnd(associationEndPair.first);
        }
        associations.erase(key);
    }
}

const std::map<std::string, std::shared_ptr<MetaAssociationClass>>& MetaModel::getAssociationClasses() const{
    return associationClasses;
}

std::shared_ptr<MetaAssociationClass> MetaModel::getAssociationClass(const std::string& key){
    auto iterator = associationClasses.find(key);
    if(iterator != associationClasses.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaModel::addAssociationClass(std::shared_ptr<MetaAssociationClass> modelAssociationClass){
    if (!modelAssociationClass) {
        throw std::invalid_argument("Null associationClass");
    }

    if (modelContainsKey(modelAssociationClass->getName())) {
        throw std::runtime_error("Model already contains element named: " + modelAssociationClass->getName());
    }

    for(auto &associationEndPair : modelAssociationClass->MetaAssociation::getAssociationEnds()){
        try{
            modelAssociationClass->addIntermediateAssociationEnd(associationEndPair.second);
        }catch(std::invalid_argument e){
            //throw std::runtime_error("Failed to add intermediate association");
        }
    }

    associationClasses[modelAssociationClass->getName()] = std::move(modelAssociationClass);
}

void MetaModel::removeAssociationClass(const std::string& key){
    auto associationClass = this->getAssociationClass(key);

    for(const auto &associationEndPair : associationClass->MetaAssociation::getAssociationEnds()){
        associationClass->removeAssociationEnd(associationEndPair.first);
    }

    associationClasses.erase(key);
}


bool MetaModel::modelContainsKey(const std::string& key){
    return (enums.find(key) != enums.end()) ||
           (classes.find(key) != classes.end()) ||
           (associations.find(key) != associations.end()) ||
           (associationClasses.find(key) != associationClasses.end());
}

std::any MetaModel::accept(ModelToText::VisitorInterface& visitor) const {
    return visitor.visit(*this);
}

}
