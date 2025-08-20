#include <algorithm>
#include <metamodel/MetaAssociationClass.h>

#include <iostream>
#include <stdexcept>

#include <modelToText/VisitorInterface.h>

namespace MetaModel{

MetaAssociationClass::MetaAssociationClass(const std::string& name, bool isAbstract, int type)
    : MetaClass(name, isAbstract), MetaAssociation(name, type){}

MetaAssociationClass::MetaAssociationClass(const std::string& name, bool isAbstract, int type, std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds)
    : MetaClass(name, isAbstract), MetaAssociation(name, type){

}

std::string MetaAssociationClass::getName() const{
    return MetaClass::getName();
}

void MetaAssociationClass::setName(const std::string& name){
    MetaClass::setName(name);
    MetaAssociation::setName(name);
}

void MetaAssociationClass::addSuperClass(std::shared_ptr<MetaClass> metaClass){
    if (!std::dynamic_pointer_cast<MetaAssociationClass>(metaClass)) {
        throw std::invalid_argument("MetaAssociationClass can only inherit from another MetaAssociationClass");
    }
    MetaClass::addSuperClass(metaClass);
}

void MetaAssociationClass::addAssociationEnd(std::shared_ptr<MetaAssociationEnd> associationEnd){
    if (!associationEnd) {
        throw std::invalid_argument("Null association end");
    }

    if (this->MetaAssociation::associationEnds.find(associationEnd->getRole()) != this->MetaAssociation::associationEnds.end()) {
        throw std::runtime_error("Role '" + associationEnd->getRole() + "' already declared in association: " + this->getName());
    }

    std::cout << "ADDING ASSOC END: " << associationEnd->getRole() << " FROM ASSOCIATION CLASS: " << this->getName() << std::endl;

    for(const auto &pair : associationEnd->getClassSharedPtr()->getAssociationEnds()){
        std::cout << "ASSOC END CLASS ENDS: " << pair.first << std::endl;
    }

    std::string intermediateRole = this->getName();
    std::transform(intermediateRole.begin(), intermediateRole.end(), intermediateRole.begin(), ::tolower);
    std::shared_ptr<MetaAssociationEnd> intermediateAssociationEnd = std::make_shared<MetaAssociationEnd>(
        std::dynamic_pointer_cast<MetaAssociationClass>(associationEnd->getAssociationSharedPtr()),
        associationEnd->getAssociationSharedPtr(),
        intermediateRole,
        associationEnd->getType(),
        associationEnd->getIsNavigable(),
        associationEnd->getIsOrdered(),
        associationEnd->getIsUnique(),
        associationEnd->getIsUnion(),
        associationEnd->getMultiplicitySharedPtr(),
        associationEnd->getVisibility());

    // Add custom associationEnd pointing to association class to other ends classes
    for(const auto &associationEndPair : this->MetaAssociation::getAssociationEnds()){
        auto otherAssociationEnd = associationEndPair.second;

        std::cout << "ADDING TO OTHER ASSOC END: " << otherAssociationEnd->getRole() << " FROM ASSOCIATION CLASS: " << this->getName() << std::endl;

        for(const auto &pair : otherAssociationEnd->getClassSharedPtr()->getAssociationEnds()){
            std::cout << "OTHER ASSOC END CLASS ENDS: " << pair.first << std::endl;
        }

        std::shared_ptr<MetaAssociationEnd> otherIntermediateAssociationEnd = std::make_shared<MetaAssociationEnd>(
            std::dynamic_pointer_cast<MetaAssociationClass>(otherAssociationEnd->getAssociationSharedPtr()),
            otherAssociationEnd->getAssociationSharedPtr(),
            intermediateRole,
            otherAssociationEnd->getType(),
            otherAssociationEnd->getIsNavigable(),
            otherAssociationEnd->getIsOrdered(),
            otherAssociationEnd->getIsUnique(),
            otherAssociationEnd->getIsUnion(),
            otherAssociationEnd->getMultiplicitySharedPtr(),
            otherAssociationEnd->getVisibility());

        if (associationEnd != otherAssociationEnd) {
            std::cout << "DIFERENT" << std::endl;
            otherAssociationEnd->getClassSharedPtr()->addAssociationEnd(intermediateAssociationEnd);
            associationEnd->getClassSharedPtr()->addAssociationEnd(otherIntermediateAssociationEnd);
        }
    }

    this->MetaAssociation::associationEnds[associationEnd->getRole()] = std::move(associationEnd);
}
void MetaAssociationClass::removeAssociationEnd(const std::string& key){

    std::cout << "<AssocClass> REMOVING ASSOC END: " << key << " FROM ASSOC CLASS: " << this->getName() << std::endl;


    std::string intermediateRole = this->getName();
    std::transform(intermediateRole.begin(), intermediateRole.end(), intermediateRole.begin(), ::tolower);
    auto associationEnd = this->MetaAssociation::getAssociationEnd(key);

    std::cout << "<AssocClass> REMOVING INTERMEDIATE ROLE: " << intermediateRole << " FROM ASSOC END : "<< associationEnd->getRole() <<" CLASS: " <<  associationEnd->getClassSharedPtr()->getName() << std::endl;
    associationEnd->getClassSharedPtr()->removeAssociationEnd(intermediateRole);

    this->MetaAssociation::associationEnds.erase(key);

    // for(const auto &associationEndPair : this->MetaAssociation::getAssociationEnds()){
    //     auto otherAssociationEnd = associationEndPair.second;

    //     otherAssociationEnd->getClassSharedPtr()->removeAssociationEnd(intermediateRole);
    // }
}

std::any MetaAssociationClass::accept(ModelToText::VisitorInterface& visitor) const{
    return visitor.visit(*this);
}

}
