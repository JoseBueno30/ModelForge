#include <metamodel/MetaClass.h>

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

const std::vector<std::shared_ptr<MetaClass>>& MetaClass::getSuperClasses() const{
    return superClasses;
}

void MetaClass::addSuperClass(const std::shared_ptr<MetaClass>& metaClass){
    if(metaClass){
        superClasses.push_back(metaClass);
    }
}
void MetaClass::removeSuperClass(int pos){
    if(pos>=0 && pos <  static_cast<int>(superClasses.size())){
        superClasses.erase(superClasses.begin() + pos);

        if(superClasses.size() < superClasses.capacity()/2){
            superClasses.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaAttribute>>& MetaClass::getAttributes() const{
    return attributes;
}

void MetaClass::addAttribute(std::unique_ptr<MetaAttribute> &attribute){
    if(attribute){
        attributes.push_back(std::move(attribute));
    }
}

void MetaClass::removeAttribute(int pos){
    if(pos>=0 && pos <  static_cast<int>(attributes.size())){
        attributes.erase(attributes.begin() + pos);

        if(attributes.size() < attributes.capacity()/2){
            attributes.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaOperation>>& MetaClass::getOperations() const{
    return operations;
}

void MetaClass::addOperation(std::unique_ptr<MetaOperation> operation){
    if(operation){
        operations.push_back(std::move(operation));
    }
}

void MetaClass::removeOperation(int pos){
    if(pos>=0 && pos <  static_cast<int>(operations.size())){
        operations.erase(operations.begin() + pos);

        if(operations.size() < operations.capacity()/2){
            operations.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaConstraint>>& MetaClass::getConstraints() const{
    return constraints;
}

void MetaClass::addConstraint(std::unique_ptr<MetaConstraint> constraint){
    if(constraint){
        constraints.push_back(std::move(constraint));
    }
}

void MetaClass::removeConstraint(int pos){
    if(pos>=0 && pos <  static_cast<int>(constraints.size())){
        constraints.erase(constraints.begin() + pos);

        if(constraints.size() < constraints.capacity()/2){
            constraints.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaStateMachine>>& MetaClass::getStateMachines() const{
    return stateMachines;
}

void MetaClass::addStateMachine(std::unique_ptr<MetaStateMachine> stateMachine){
    if(stateMachine){
        stateMachines.push_back(std::move(stateMachine));
    }
}

void MetaClass::removeStateMachine(int pos){
    if(pos>=0 && pos <  static_cast<int>(stateMachines.size())){
        stateMachines.erase(stateMachines.begin() + pos);

        if(stateMachines.size() < stateMachines.capacity()/2){
            stateMachines.shrink_to_fit();
        }
    }
}


}
