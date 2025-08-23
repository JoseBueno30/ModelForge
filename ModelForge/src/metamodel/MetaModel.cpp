#include <metamodel/MetaModel.h>
#include <modelToText/VisitorInterface.h>
#include <iostream>
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
    std::cout << "REMOVING CLASS: " << key << std::endl;
    std::cout << "<Remove MetaClass> nAssocEnd: " << metaClass->getAssociationEnds().size() << std::endl;
    for(const auto &assocEndPair : metaClass->getAssociationEnds()){
        auto association = assocEndPair.second->getAssociationSharedPtr();

        std::cout << "REMOVING ASSOCEND: " << assocEndPair.first << std::endl;
        std::cout << "ASOCIACION NULA ? " << !association << std::endl;

        if(std::dynamic_pointer_cast<MetaAssociationClass>(association)){
            std::cout << "REMOVING ASSOC CLASS FROM CLASS: " << association->getName() << std::endl;
            this->removeAssociationClass(association->getName());
        }else{
            std::cout << "REMOVING ASSOC FROM CLASS: " << association->getName() << std::endl;
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
    std::cout << "REMOVING ASSOCIATION: " << key << std::endl;
    auto association = this->getAssociation(key);

    for(const auto &associationEndPair : association->getAssociationEnds()){
        association->removeAssociationEnd(associationEndPair.first);
    }
    std::cout<<"SALE BUCLE" << std::endl;
    associations.erase(key);
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
            std::cout << "ANYADIENDO INTERMEDIA CON " << associationEndPair.second->getClassSharedPtr()->getName() << std::endl;//"DE LA ASOCIACION " << associationEndPair.second->getAssociationSharedPtr()->getName() << std::endl;
            modelAssociationClass->addIntermediateAssociationEnd(associationEndPair.second);
        }catch(std::invalid_argument e){
            std::cerr << "FALLA ANYADIR INTERMEDIAS con "<<associationEndPair.second->getClassSharedPtr()->getName() << std::endl;
        }
    }

    associationClasses[modelAssociationClass->getName()] = std::move(modelAssociationClass);
}

void MetaModel::removeAssociationClass(const std::string& key){
    std::cout << "REMOVING ASSOCIATION CLASS: " << key << std::endl;
    auto associationClass = this->getAssociationClass(key);

    for(const auto &associationEndPair : associationClass->MetaAssociation::getAssociationEnds()){
        std::cout << "REMOVE ASSOC END: " << associationEndPair.first << std::endl;
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
