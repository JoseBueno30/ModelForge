#include <iostream>
#include <metamodel/MetaClass.h>

#include <ostream>
#include <stdexcept>

#include <modelToText/VisitorInterface.h>

namespace MetaModel{

MetaClass::MetaClass(const std::string& name, bool isAbstract)
    : name(name), isAbstract(isAbstract){}

std::string MetaClass::getName() const{
    return name;
}
void MetaClass::setName(const std::string& name){
    this->name = name;
}

bool MetaClass::getIsAbstract() const{
    return isAbstract;
}
void MetaClass::setIsAbstract(bool isAbstract){
    this->isAbstract = isAbstract;
}

const std::map<std::string, std::shared_ptr<MetaClass>>& MetaClass::getSuperClasses() const{
    return superClasses;
}

const MetaClass* MetaClass::getSuperClass(const std::string& key) const{
    auto iterator = superClasses.find(key);
    if(iterator != superClasses.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addSuperClass(const std::shared_ptr<MetaClass> metaClass){
    if (!metaClass) {
        throw std::invalid_argument("Null SuperClass");
    }

    if (superClasses.find(metaClass->getName()) != superClasses.end()) {
        throw std::invalid_argument("Generalization already declared: " + metaClass->getName());
    }

    if(this->equals(*metaClass)){
        throw std::invalid_argument("Class: " + metaClass->getName() + " cannot be a SuperClass of itself");
    }

    if(this->hasInheritanceCycle(*metaClass)){
        throw std::invalid_argument("Detected cycle in generalization hierarchy. Class: " + metaClass->getName() + " is already a child of Class: " + this->getName());
    }


    for(const auto& pair: superClasses){
        auto otherSuperClass = pair.second;


        for(const auto& otherSuperClassAttributePair: otherSuperClass->getAllAttributes()){
            auto otherSuperClassAttribute = otherSuperClass->getAttribute(otherSuperClassAttributePair.first);

            for(const auto& superClassAttributePair: metaClass->getAllAttributes()){
                auto superClassAttribute = metaClass->getAttribute(superClassAttributePair.first);

                if(superClassAttribute->getName()==otherSuperClassAttribute->getName() && !superClassAttribute->getType().equals(otherSuperClassAttribute->getType())){
                    throw std::invalid_argument("Inheritance conflict: attribute" + superClassAttribute->getName() + " occurs with different type in the bases classes of " + this->name);
                }
            }
        }

        for(const auto& otherSuperClassOperationPair: otherSuperClass->getAllOperations()){
            auto otherSuperClassOperation = otherSuperClass->getOperation(otherSuperClassOperationPair.first);

            for(const auto& superClassOperationPair: metaClass->getAllOperations()){
                auto superClassOperation = metaClass->getOperation(superClassOperationPair.first);

                if(superClassOperation->getName()==otherSuperClassOperation->getName() &&
                    !superClassOperation->getReturnType().equals(otherSuperClassOperation->getReturnType()) &&
                    !(metaClass->isSubClassOf(*otherSuperClass) || otherSuperClass->isSubClassOf(*metaClass))){
                    throw std::invalid_argument("Inheritance conflict: operation" + superClassOperation->getName() + " occurs with different signatures in the bases classes of " + this->name);
                }
            }
        }
    }

    superClasses[metaClass->getName()] = metaClass;
}
void MetaClass::removeSuperClass(const std::string& key){
    superClasses.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaClass>>& MetaClass::getChildrenClasses() const{
    return childrenClasses;
}

const MetaClass* MetaClass::getChildrenClass(const std::string& key) const{
    auto iterator = childrenClasses.find(key);
    if(iterator != childrenClasses.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addChildrenClass(const std::shared_ptr<MetaClass> metaClass){
    if (!metaClass) {
        throw std::invalid_argument("Null super class");
    }

    if (childrenClasses.find(metaClass->getName()) != childrenClasses.end()) {//More generalization restrictions needed
        throw std::invalid_argument("Generalization already declared: " + metaClass->getName());
    }

    childrenClasses[metaClass->getName()] = metaClass;
}
void MetaClass::removeChildrenClass(const std::string& key){
    childrenClasses.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaAttribute>>& MetaClass::getAttributes() const{
    return attributes;
}

std::map<std::string, const MetaAttribute*> MetaClass::getAllAttributes() const{
    std::map<std::string, const MetaAttribute*> allAttributes;

    for (const auto& attributePair : attributes) {
        allAttributes[attributePair.first] = attributePair.second.get();
    }

    for (const auto& superClassPair : superClasses) {

        std::map<std::string, const MetaAttribute*> superClassAttributes = superClassPair.second->getAllAttributes();

        for (const auto& superClassAttribute : superClassAttributes) {
            if (allAttributes.find(superClassAttribute.first) == allAttributes.end()) {
                allAttributes[superClassAttribute.first] = superClassAttribute.second;
            }
        }
    }

    return allAttributes;
}

std::shared_ptr<MetaAttribute> MetaClass::getAttribute(const std::string& key){
    auto iterator = attributes.find(key);
    if(iterator != attributes.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaClass::addAttribute(std::shared_ptr<MetaAttribute> attribute){
    if (!attribute) {
        throw std::invalid_argument("Null attribute");
    }

    if (attributes.find(attribute->getName()) != attributes.end()) {
        throw std::invalid_argument("Class '" + name + "' already contains attribute named: '" + attribute->getName() + "'.");
    }

    auto allAttributes = this->getAllAttributes();
    if (allAttributes.find(attribute->getName()) != allAttributes.end()){
        throw std::invalid_argument("Attribute '" + attribute->getName() + "' already defined in SuperClass.");
    }

    attributes[attribute->getName()] = std::move(attribute);
}

void MetaClass::removeAttribute(const std::string& key){
    attributes.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaAssociationEnd>>  MetaClass::getAssociationEnds() const{
    return this->associationEnds;
}

std::map<std::string, const MetaAssociationEnd *>  MetaClass::getAllAssociationEnds() const{
    std::map<std::string, const MetaAssociationEnd*> allAssociationEnds;

    for (const auto& associationEndPair : associationEnds) {
        allAssociationEnds[associationEndPair.first] = associationEndPair.second.get();
    }

    for (const auto& superClassPair : superClasses) {

        std::map<std::string, const MetaAssociationEnd*> superClassAssociationEnds = superClassPair.second->getAllAssociationEnds();

        for (const auto& superClassAssociationEnd: superClassAssociationEnds) {
            if (allAssociationEnds.find(superClassAssociationEnd.first) == allAssociationEnds.end()) {
                allAssociationEnds[superClassAssociationEnd.first] = superClassAssociationEnd.second;
            }
        }
    }

    return allAssociationEnds;
}
std::shared_ptr<MetaAssociationEnd>  MetaClass::getAssociationEnd(const std::string& key){
    auto iterator = associationEnds.find(key);
    if(iterator != associationEnds.end()){
        return (iterator->second);
    }
    return nullptr;
}
void  MetaClass::addAssociationEnd(std::shared_ptr<MetaAssociationEnd> associationEnd){
    if (!associationEnd) {
        throw std::invalid_argument("Null AssociationEnd");
    }

    if (associationEnds.find(associationEnd->getRole()) != associationEnds.end()) {
        throw std::invalid_argument("Class '" + name + "' already contains associationEnd roled: '" + associationEnd->getRole() + "'.");
    }

    auto allAssociationEnds = this->getAllAssociationEnds();
    if (allAssociationEnds.find(associationEnd->getRole()) != allAssociationEnds.end()){
        throw std::invalid_argument("AssociationEnd '" + associationEnd->getRole() + "' already defined in SuperClass.");
    }


    associationEnds[associationEnd->getRole()] = associationEnd;
}
void  MetaClass::removeAssociationEnd(const std::string& key){
    associationEnds.erase(key);
}


const std::map<std::string, std::shared_ptr<MetaOperation>>& MetaClass::getOperations() const{
    return operations;
}

std::map<std::string, const MetaOperation*> MetaClass::getAllOperations() const{
    std::map<std::string, const MetaOperation*> allOperations;

    for (const auto& operationPair : operations) {
        allOperations[operationPair.first] = operationPair.second.get();
    }

    for (const auto& superClassPair : superClasses) {

        std::map<std::string, const MetaOperation*> superClassOperations = superClassPair.second->getAllOperations();

        for (const auto& superClassOperation : superClassOperations) {
            if (allOperations.find(superClassOperation.first) == allOperations.end()) {
                allOperations[superClassOperation.first] = superClassOperation.second;
            }
        }
    }

    return allOperations;
}

std::shared_ptr<MetaOperation> MetaClass::getOperation(const std::string& key){
    auto iterator = operations.find(key);
    if(iterator != operations.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaClass::addOperation(std::shared_ptr<MetaOperation> operation){
    if (!operation) {
        throw std::invalid_argument("Null operation");
    }

    if (operations.find(operation->getName()) != operations.end()) {
        throw std::invalid_argument("Class '" + name + "' already contains operation named: '" + operation->getName() + "'.");
    }

    auto allOperations = this->getAllOperations();
    auto superOperation = allOperations.find(operation->getName());
    if (superOperation != allOperations.end()){
        if(!operation->isValidOverrideOf(*(superOperation->second))){
            throw std::invalid_argument("Redefinition of operation '" + operation->getName() + "' requires same number and type of arguments.");
        }
    }

    operations[operation->getName()] = std::move(operation);
}

void MetaClass::removeOperation(const std::string& key){
    operations.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaConstraint>>& MetaClass::getConstraints() const{
    return constraints;
}

std::shared_ptr<MetaConstraint> MetaClass::getConstraint(const std::string& key){
    auto iterator = constraints.find(key);
    if(iterator != constraints.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaClass::addConstraint(std::shared_ptr<MetaConstraint> constraint){
    if (!constraint) {
        throw std::invalid_argument("Null constraint");
    }

    if (constraints.find(constraint->getName()) != constraints.end()) {
        throw std::invalid_argument("Constraint already declared: " + constraint->getName());
    }

    constraints[constraint->getName()] = std::move(constraint);
}

void MetaClass::removeConstraint(const std::string& key){
    constraints.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaStateMachine>>& MetaClass::getStateMachines() const{
    return stateMachines;
}

std::shared_ptr<MetaStateMachine> MetaClass::getStateMachine(const std::string& key){
    auto iterator = stateMachines.find(key);
    if(iterator != stateMachines.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaClass::addStateMachine(std::shared_ptr<MetaStateMachine> stateMachine){
    if (!stateMachine) {
        throw std::invalid_argument("Null state machine");
    }

    if (stateMachines.find(stateMachine->getName()) != stateMachines.end()) {//More generalization restrictions needed
        throw std::invalid_argument("StateMachine already declared: " + stateMachine->getName());
    }

    stateMachines[stateMachine->getName()] = std::move(stateMachine);
}

void MetaClass::removeStateMachine(const std::string& key){
    stateMachines.erase(key);
}

bool MetaClass::isSubClassOf(const MetaClass& metaClass) const{

    return this->getSuperClasses().find(metaClass.getName()) != this->getSuperClasses().end();

}

bool MetaClass::isSuperClassOf(const MetaClass& metaClass) const{

    return metaClass.getSuperClasses().find(this->getName()) != metaClass.getSuperClasses().end();

}

bool MetaClass::hasInheritanceCycle(const MetaClass& metaClass) const{

    std::unordered_set<std::string> visited;
    return metaClass.hasAncestor(*this, visited);
}

bool MetaClass::hasAncestor(const MetaClass& ancestor, std::unordered_set<std::string>& visited) const{
    for (const auto& pair : superClasses) {

        const MetaClass& superClass = *pair.second;

        if (superClass.getName() == ancestor.getName()) {
            return true;
        }

        if (visited.find(superClass.getName()) == visited.end()) {
            visited.insert(superClass.getName());

            if (superClass.hasAncestor(ancestor, visited)) {
                return true;
            }
        }
    }
    return false;
}

bool MetaClass::equals(const MetaType& type) const{
    const MetaClass* metaClass= dynamic_cast<const MetaClass*>(&type);

    return metaClass != nullptr && this->name == metaClass->getName();
}

std::string MetaClass::toString() const{
    return this->getName();
}

std::any MetaClass::accept(ModelToText::VisitorInterface& visitor) const{
    return visitor.visit(*this);
}

}
