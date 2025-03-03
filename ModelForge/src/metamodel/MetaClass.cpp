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
        throw std::invalid_argument("Null SuperClass");
    }

    if (superClasses.find(metaClass->getName()) != superClasses.end()) {
        throw std::runtime_error("Generalization already declared: " + metaClass->getName());
    }

    if(this->equals(*metaClass)){
        throw std::runtime_error("Class: " + metaClass->getName() + " cannot be a SuperClass of itself");
    }

    if(this->hasInheritanceCycle(*metaClass)){
        throw std::runtime_error("Detected cycle in generalization hierarchy. Class: " + metaClass->getName() + " is already a child of Class: " + this->getName());
    }

    for(const auto& pair: superClasses){
        auto otherSuperClass = pair.second;

        for(const auto& otherSuperClassAttributePair: otherSuperClass->getAllAttributes()){
            auto otherSuperClassAttribute = otherSuperClass->getAttribute(otherSuperClassAttributePair.first);

            for(const auto& superClassAttributePair: metaClass->getAllAttributes()){
                auto superClassAttribute = otherSuperClass->getAttribute(superClassAttributePair.first);

                if(superClassAttribute->getName()==otherSuperClassAttribute->getName() && !superClassAttribute->getType().equals(otherSuperClassAttribute->getType())){
                    throw std::runtime_error("Inheritance conflict: attribute" + superClassAttribute->getName() + " occurs with different type in the bases classes of " + this->name);
                }
            }
        }

        for(const auto& otherSuperClassOperationPair: otherSuperClass->getAllOperations()){
            auto otherSuperClassOperation = otherSuperClass->getOperation(otherSuperClassOperationPair.first);

            for(const auto& superClassOperationPair: metaClass->getAllOperations()){
                auto superClassOperation = otherSuperClass->getOperation(superClassOperationPair.first);

                if(superClassOperation->getName()==otherSuperClassOperation->getName() &&
                    !superClassOperation->getReturnType().equals(otherSuperClassOperation->getReturnType()) &&
                    !(metaClass->isSubClassOf(*otherSuperClass) || otherSuperClass->isSubClassOf(*metaClass))){
                    throw std::runtime_error("Inheritance conflict: operation" + superClassOperation->getName() + " occurs with different signatures in the bases classes of " + this->name);
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
        throw std::runtime_error("Generalization already declared: " + metaClass->getName());
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

const MetaAttribute* MetaClass::getAttribute(const std::string& key) const{
    auto iterator = attributes.find(key);
    if(iterator != attributes.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addAttribute(const std::shared_ptr<MetaAttribute>& attribute){
    if (!attribute) {
        throw std::invalid_argument("Null attribute");
    }

    if (attributes.find(attribute->getName()) != attributes.end()) {
        throw std::runtime_error("Attribute already declared: " + attribute->getName());
    }

    attributes[attribute->getName()] = attribute;
}

void MetaClass::removeAttribute(const std::string& key){
    attributes.erase(key);
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

const MetaOperation* MetaClass::getOperation(const std::string& key) const{
    auto iterator = operations.find(key);
    if(iterator != operations.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addOperation(const std::shared_ptr<MetaOperation>& operation){
    if (!operation) {
        throw std::invalid_argument("Null operation");
    }

    if (operations.find(operation->getName()) != operations.end()) {//More generalization restrictions needed
        throw std::runtime_error("Operation already declared: " + operation->getName());
    }

    operations[operation->getName()] = operation;
}

void MetaClass::removeOperation(const std::string& key){
    operations.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaConstraint>>& MetaClass::getConstraints() const{
    return constraints;
}

const MetaConstraint* MetaClass::getConstraint(const std::string& key) const{
    auto iterator = constraints.find(key);
    if(iterator != constraints.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addConstraint(const std::shared_ptr<MetaConstraint>& constraint){
    if (!constraint) {
        throw std::invalid_argument("Null constraint");
    }

    if (constraints.find(constraint->getName()) != constraints.end()) {//More generalization restrictions needed
        throw std::runtime_error("Constraint already declared: " + constraint->getName());
    }

    constraints[constraint->getName()] = constraint;
}

void MetaClass::removeConstraint(const std::string& key){
    constraints.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaStateMachine>>& MetaClass::getStateMachines() const{
    return stateMachines;
}

const MetaStateMachine* MetaClass::getStateMachine(const std::string& key) const{
    auto iterator = stateMachines.find(key);
    if(iterator != stateMachines.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaClass::addStateMachine(const std::shared_ptr<MetaStateMachine>& stateMachine){
    if (!stateMachine) {
        throw std::invalid_argument("Null state machine");
    }

    if (stateMachines.find(stateMachine->getName()) != stateMachines.end()) {//More generalization restrictions needed
        throw std::runtime_error("StateMachine already declared: " + stateMachine->getName());
    }

    stateMachines[stateMachine->getName()] = stateMachine;
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

}
