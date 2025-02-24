#include <metamodel/MetaClass.h>

#include <stdexcept>

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
        throw std::invalid_argument("Null super class");
    }

    if (superClasses.find(metaClass->getName()) != superClasses.end()) {//More generalization restrictions needed
        throw std::runtime_error("Generalization already declared: " + metaClass->getName());
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
        throw std::runtime_error("Generalization already declared: " + metaClass->getName());
    }

    childrenClasses[metaClass->getName()] = metaClass;
}
void MetaClass::removeChildrenClass(const std::string& key){
    childrenClasses.erase(key);
}

const std::map<std::string, std::unique_ptr<MetaAttribute>>& MetaClass::getAttributes() const{
    return attributes;
}

const MetaAttribute* MetaClass::getAttribute(const std::string& key) const{
    auto iterator = attributes.find(key);
    if(iterator != attributes.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addAttribute(std::unique_ptr<MetaAttribute> attribute){
    if (!attribute) {
        throw std::invalid_argument("Null super class");
    }

    if (attributes.find(attribute->getName()) != attributes.end()) {//More generalization restrictions needed
        throw std::runtime_error("Generalization already declared: " + attribute->getName());
    }

    attributes[attribute->getName()] = std::move(attribute);
}

void MetaClass::removeAttribute(const std::string& key){
    attributes.erase(key);
}

const std::map<std::string, std::unique_ptr<MetaOperation>>& MetaClass::getOperations() const{
    return operations;
}

const MetaOperation* MetaClass::getOperation(const std::string& key) const{
    auto iterator = operations.find(key);
    if(iterator != operations.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addOperation(std::unique_ptr<MetaOperation> operation){
    if (!operation) {
        throw std::invalid_argument("Null operation");
    }

    if (operations.find(operation->getName()) != operations.end()) {//More generalization restrictions needed
        throw std::runtime_error("Operation already declared: " + operation->getName());
    }

    operations[operation->getName()] = std::move(operation);
}

void MetaClass::removeOperation(const std::string& key){
    operations.erase(key);
}

const std::map<std::string, std::unique_ptr<MetaConstraint>>& MetaClass::getConstraints() const{
    return constraints;
}

const MetaConstraint* MetaClass::getConstraint(const std::string& key) const{
    auto iterator = constraints.find(key);
    if(iterator != constraints.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addConstraint(std::unique_ptr<MetaConstraint> constraint){
    if (!constraint) {
        throw std::invalid_argument("Null constraint");
    }

    if (constraints.find(constraint->getName()) != constraints.end()) {//More generalization restrictions needed
        throw std::runtime_error("Constraint already declared: " + constraint->getName());
    }

    constraints[constraint->getName()] = std::move(constraint);
}

void MetaClass::removeConstraint(const std::string& key){
    constraints.erase(key);
}

const std::map<std::string, std::unique_ptr<MetaStateMachine>>& MetaClass::getStateMachines() const{
    return stateMachines;
}

const MetaStateMachine* MetaClass::getStateMachine(const std::string& key) const{
    auto iterator = stateMachines.find(key);
    if(iterator != stateMachines.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addStateMachine(std::unique_ptr<MetaStateMachine> stateMachine){
    if (!stateMachine) {
        throw std::invalid_argument("Null state machine");
    }

    if (stateMachines.find(stateMachine->getName()) != stateMachines.end()) {//More generalization restrictions needed
        throw std::runtime_error("StateMachine already declared: " + stateMachine->getName());
    }

    stateMachines[stateMachine->getName()] = std::move(stateMachine);
}

void MetaClass::removeStateMachine(const std::string& key){
    stateMachines.erase(key);
}


}
