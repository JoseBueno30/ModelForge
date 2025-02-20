#ifndef METAOPERATION_H
#define METAOPERATION_H

#include "OCLExpression.h"
#include "MetaType.h"
#include "MetaVariable.h"

#include <memory>
#include <string>
#include <vector>


namespace MetaModel{

class PrePostClause{

private:
    std::string name;
    std::unique_ptr<OCLExpr> expression;

public:
    PrePostClause(const std::string& name, std::unique_ptr<OCLExpr> expression);

    std::string getName() const;
    void setName(const std::string& name);

    const OCLExpr& getExpression() const;
    void setExpression(std::unique_ptr<OCLExpr> expression);
};

class MetaOperation{

private:
    std::string name;
    std::string operationDefinition;
    std::shared_ptr<MetaType> returnType;
    std::vector<std::unique_ptr<MetaVariable>> variables;
    std::vector<std::unique_ptr<PrePostClause>> preConditions;
    std::vector<std::unique_ptr<PrePostClause>> postConditions;

public:
    MetaOperation(std::string& name, std::string& operationDefinition, const std::shared_ptr<MetaType>& returnType);

    std::string getName() const;
    void setName(const std::string& name);

    std::string getOperationDefinition() const;
    void setOperationDefinition(const std::string& operationDefinition);

    const MetaType& getReturnType() const;
    void setReturnType(const std::shared_ptr<MetaType>& returnType);

    const std::vector<std::unique_ptr<MetaVariable>>& getVariables() const;
    void addVariable(std::unique_ptr<MetaVariable> variable);
    void removeVariable(int pos);

    const std::vector<std::unique_ptr<PrePostClause>>& getPreConditions() const;
    void addPreCondition(std::unique_ptr<PrePostClause> preCondition);
    void removePreCondition(int pos);

    const std::vector<std::unique_ptr<PrePostClause>>& getPostConditions() const;
    void addPostCondition(std::unique_ptr<PrePostClause> postCondition);
    void removePostCondition(int pos);
};

}


#endif // METAOPERATION_H
