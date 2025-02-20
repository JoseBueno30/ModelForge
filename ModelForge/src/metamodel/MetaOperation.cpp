#include <metamodel/MetaOperation.h>

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

const std::vector<std::unique_ptr<MetaVariable>>& MetaOperation::getVariables() const{
    return variables;
}

void MetaOperation::addVariable(std::unique_ptr<MetaVariable> variable){
    if(variable){
        variables.push_back(std::move(variable));
    }
}
void MetaOperation::removeVariable(int pos){
    if(pos>=0 && pos <  static_cast<int>(variables.size())){
        variables.erase(variables.begin() + pos);

        if(variables.size() < variables.capacity()/2){
            variables.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<PrePostClause>>& MetaOperation::getPreConditions() const{
    return preConditions;
}
void MetaOperation::addPreCondition(std::unique_ptr<PrePostClause> preCondition){
    if(preCondition){
        preConditions.push_back(std::move(preCondition));
    }
}
void MetaOperation::removePreCondition(int pos){
    if(pos>=0 && pos <  static_cast<int>(preConditions.size())){
        preConditions.erase(preConditions.begin() + pos);

        if(preConditions.size() < preConditions.capacity()/2){
            preConditions.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<PrePostClause>>& MetaOperation::getPostConditions() const{
    return postConditions;
}
void MetaOperation::addPostCondition(std::unique_ptr<PrePostClause> postCondition){
    if(postCondition){
        postConditions.push_back(std::move(postCondition));
    }
}
void MetaOperation::removePostCondition(int pos){
    if(pos>=0 && pos <  static_cast<int>(postConditions.size())){
        postConditions.erase(postConditions.begin() + pos);

        if(postConditions.size() < postConditions.capacity()/2){
            postConditions.shrink_to_fit();
        }
    }
}


}
