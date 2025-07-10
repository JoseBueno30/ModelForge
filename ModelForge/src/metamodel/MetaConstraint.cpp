#include <metamodel/MetaConstraint.h>
#include "metamodel/MetaClass.h"
#include <modelToText/VisitorInterface.h>

#include <stdexcept>


namespace MetaModel{


MetaConstraint::MetaConstraint(const std::shared_ptr<MetaClass>& metaClass, const std::string& name, bool isExistential)
    : metaClass(metaClass), name(name), isExistential(isExistential){

    this->addVariable("self");

}

MetaConstraint::MetaConstraint(const std::shared_ptr<MetaClass>& metaClass, const std::vector<std::string>& variableNames, const std::string& name, bool isExistential)
    : metaClass(metaClass), name(name), isExistential(isExistential){

    for(const auto& variableName : variableNames){
        this->addVariable(variableName);
    }
}

std::string MetaConstraint::getName() const{
    return name;
}

void MetaConstraint::setName(const std::string& name){
    this->name = name;
}

const MetaClass& MetaConstraint::getClass() const{
    return *metaClass;
}
void MetaConstraint::setClass(const std::shared_ptr<MetaClass>& metaClass){
    this->metaClass = metaClass;
}

bool MetaConstraint::getIsExistential() const{
    return isExistential;
}

void MetaConstraint::setIsExistential(const bool isExistential){
    this->isExistential = isExistential;
}

const Expr& MetaConstraint::getExpression() const{
    return *expression;
}
void MetaConstraint::setExpression(const std::shared_ptr<Expr>& expression){
    if(!std::dynamic_pointer_cast<Boolean>(expression->getType())){
        throw std::invalid_argument("An invariant must be a Boolean expression");
    }
    this->expression = expression;
}

const std::map<std::string, std::shared_ptr<MetaVariable>>& MetaConstraint::getVariables() const{
    return variables;
}

const MetaVariable* MetaConstraint::getVariable(const std::string& key) const{
    auto iterator = variables.find(key);
    if(iterator != variables.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaConstraint::addVariable(const std::string& variableName){

    if (variableName == "") {
        throw std::invalid_argument("Invalid variable name");
    }

    if (variables.find(variableName) != variables.end()) {
        throw std::invalid_argument("Redefinition of : '" + variableName+ "' in constraint: '" + name +"'.");
    }

    variables[variableName] = std::make_shared<MetaVariable>(variableName, std::static_pointer_cast<MetaType>(this->metaClass));
}

void MetaConstraint::removeVariable(const std::string& key){
    variables.erase(key);
}

std::any MetaConstraint::accept(ModelToText::VisitorInterface& visitor) const{
    return visitor.visit(*this);
}

}
