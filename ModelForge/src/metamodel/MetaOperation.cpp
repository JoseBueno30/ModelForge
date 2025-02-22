#include <metamodel/MetaOperation.h>

#include <stdexcept>

namespace MetaModel{

PrePostClause::PrePostClause(const std::string& name, std::unique_ptr<OCLExpr> expression)
    : name(name),  expression(std::move(expression)){}

std::string PrePostClause::getName() const{
    return name;
}

void PrePostClause::setName(const std::string& name){
    this->name = name;
}

const OCLExpr& PrePostClause::getExpression() const{
    return *expression;
}

void PrePostClause::setExpression(std::unique_ptr<OCLExpr> expression){
    this->expression = std::move(expression);
}



MetaOperation::MetaOperation(std::string& name, std::string& operationDefinition, const std::shared_ptr<MetaType>& returnType)
    : name(name), operationDefinition(operationDefinition), returnType(returnType){}

std::string MetaOperation::getName() const{
    return name;
}

void MetaOperation::setName(const std::string& name){
    this->name = name;
}

std::string MetaOperation::getOperationDefinition() const{
    return operationDefinition;
}

void MetaOperation::setOperationDefinition(const std::string& operationDefinition){
    this->operationDefinition = operationDefinition;
}

const MetaType& MetaOperation::getReturnType() const{
    return *returnType;
}
void MetaOperation::setReturnType(const std::shared_ptr<MetaType>& returnType){
    this->returnType = returnType;
}

const std::map<std::string, std::unique_ptr<MetaVariable>>& MetaOperation::getVariables() const{
    return variables;
}

const MetaVariable* MetaOperation::getVariable(const std::string& key) const{
    auto iterator = variables.find(key);
    if(iterator != variables.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaOperation::addVariable(const std::string& key, std::unique_ptr<MetaVariable> variable){
    if (!variable) {
        throw std::invalid_argument("Null variable");
    }

    if (variables.find(key) != variables.end()) {
        throw std::runtime_error("Operation: " + name + " already contains variable named: " + key);
    }

    variables[key] = std::move(variable);
}

void MetaOperation::removeVariable(const std::string& key){
    variables.erase(key);
}

const std::map<std::string, std::unique_ptr<PrePostClause>>& MetaOperation::getPreConditions() const{
    return preConditions;
}

const PrePostClause* MetaOperation::getPreCondition(const std::string& key) const{
    auto iterator = preConditions.find(key);
    if(iterator != preConditions.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaOperation::addPreCondition(const std::string& key, std::unique_ptr<PrePostClause> preCondition){
    if (!preCondition) {
        throw std::invalid_argument("Null PreCondition");
    }

    if (isPrePostConditionDefined(key)) {
        throw std::runtime_error("Operation: " + name + " already contains Pre/Post condition named: " + key);
    }

    preConditions[key] = std::move(preCondition);
}

void MetaOperation::removePreCondition(const std::string& key){
    preConditions.erase(key);
}

const std::map<std::string, std::unique_ptr<PrePostClause>>& MetaOperation::getPostConditions() const{
    return postConditions;
}

const PrePostClause* MetaOperation::getPostCondition(const std::string& key) const{
    auto iterator = postConditions.find(key);
    if(iterator != postConditions.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaOperation::addPostCondition(const std::string& key, std::unique_ptr<PrePostClause> postCondition){
    if (!postCondition) {
        throw std::invalid_argument("Null PostCondition");
    }

    if (isPrePostConditionDefined(key)) {
        throw std::runtime_error("Operation: " + name + " already contains Pre/Post condition named: " + key);
    }

    postConditions[key] = std::move(postCondition);
}

void MetaOperation::removePostCondition(const std::string& key){
    postConditions.erase(key);
}

bool MetaOperation::isPrePostConditionDefined(const std::string& key){
    return (preConditions.find(key) != preConditions.end()) ||
           (postConditions.find(key) != postConditions.end());
}
}
