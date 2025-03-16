#include <metamodel/MetaOperation.h>

#include <stdexcept>

namespace MetaModel{

PrePostClause::PrePostClause(const std::string& name, const std::shared_ptr<OCLExpr>& expression, bool isPre, bool isPost)
    : name(name),  expression(expression), isPre(isPre), isPost(isPost){}

std::string PrePostClause::getName() const{
    return name;
}

void PrePostClause::setName(const std::string& name){
    this->name = name;
}

const OCLExpr& PrePostClause::getExpression() const{
    return *expression;
}

void PrePostClause::setExpression(const std::shared_ptr<OCLExpr>& expression){
    this->expression = expression;
}

bool PrePostClause::getIsPre() const{
    return isPre;
}
void PrePostClause::setIsPre(bool isPre){
    this->isPre = isPre;
}

bool PrePostClause::getIsPost() const{
    return isPost;
}
void PrePostClause::setIsPost(bool isPost){
    this->isPost = isPost;
}


MetaOperation::MetaOperation(const std::string& name, const std::string& operationDefinition, const std::shared_ptr<MetaType>& returnType)
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

const std::map<std::string, std::shared_ptr<MetaVariable>>& MetaOperation::getVariables() const{
    return variables;
}

const MetaVariable* MetaOperation::getVariable(const std::string& key) const{
    auto iterator = variables.find(key);
    if(iterator != variables.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaOperation::addVariable(const std::shared_ptr<MetaVariable>& variable){
    if (!variable) {
        throw std::invalid_argument("Null variable");
    }

    if (variables.find(variable->getName()) != variables.end()) {
        throw std::invalid_argument("Operation: " + name + " already contains variable named: " + variable->getName());
    }

    variables[variable->getName()] = variable;
}

void MetaOperation::removeVariable(const std::string& key){
    variables.erase(key);
}

const std::map<std::string, std::shared_ptr<PrePostClause>>& MetaOperation::getPreConditions() const{
    return preConditions;
}

const PrePostClause* MetaOperation::getPreCondition(const std::string& key) const{
    auto iterator = preConditions.find(key);
    if(iterator != preConditions.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaOperation::addPreCondition(const std::shared_ptr<PrePostClause>& preCondition){
    if (!preCondition) {
        throw std::invalid_argument("Null PreCondition");
    }

    if (isPrePostConditionDefined(preCondition->getName())) {
        throw std::invalid_argument("Operation: " + name + " already contains Pre/Post condition named: " + preCondition->getName());
    }

    preConditions[preCondition->getName()] = preCondition;
}

void MetaOperation::removePreCondition(const std::string& key){
    preConditions.erase(key);
}

const std::map<std::string, std::shared_ptr<PrePostClause>>& MetaOperation::getPostConditions() const{
    return postConditions;
}

const PrePostClause* MetaOperation::getPostCondition(const std::string& key) const{
    auto iterator = postConditions.find(key);
    if(iterator != postConditions.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaOperation::addPostCondition(const std::shared_ptr<PrePostClause>& postCondition){
    if (!postCondition) {
        throw std::invalid_argument("Null PostCondition");
    }

    if (isPrePostConditionDefined(postCondition->getName())) {
        throw std::invalid_argument("Operation: " + name + " already contains Pre/Post condition named: " + postCondition->getName());
    }

    postConditions[postCondition->getName()] = postCondition;
}

void MetaOperation::removePostCondition(const std::string& key){
    postConditions.erase(key);
}

bool MetaOperation::isPrePostConditionDefined(const std::string& key){
    return (preConditions.find(key) != preConditions.end()) ||
           (postConditions.find(key) != postConditions.end());
}

bool MetaOperation::isValidOverrideOf(const MetaOperation& operation) const{
    if(this->getName() != operation.getName()) return false;

    if(!this->getReturnType().equals(operation.getReturnType())) return false;

    auto otherVariables = operation.getVariables();
    if(this->variables.size() != otherVariables.size()) return false;

    auto it1 = variables.begin();
    auto it2 = otherVariables.begin();

    for (; it1 != variables.end(); ++it1, ++it2) {
        if (!it1->second->getType().equals(it2->second->getType())) return false;
    }

    return true;
}

std::string MetaOperation::variablesToString() const{
    std::string variableList = "(";

    if(variables.size()>0){

        auto variableIterator = variables.begin();

        variableList += variableIterator->second->toString();

        variableIterator++;

        for(; variableIterator != variables.end(); variableIterator++){
            variableList += ", " + variableIterator->second->toString();
        }
    }

    variableList += ")";

    return variableList;
}

std::string MetaOperation::toString() const{

    return this->getName() + this->variablesToString() + " : " + this->getReturnType().toString();
}

}
