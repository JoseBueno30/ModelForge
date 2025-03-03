#ifndef METAOPERATION_H
#define METAOPERATION_H

#include "OCLExpression.h"
#include "MetaType.h"
#include "MetaVariable.h"

#include <memory>
#include <string>
#include <map>


namespace MetaModel{

class PrePostClause{

private:
    std::string name;
    std::shared_ptr<OCLExpr> expression;

public:
    PrePostClause(const std::string& name, const std::shared_ptr<OCLExpr>& expression);

    std::string getName() const;
    void setName(const std::string& name);

    const OCLExpr& getExpression() const;
    void setExpression(const std::shared_ptr<OCLExpr>& expression);
};

class MetaOperation{

private:
    std::string name;
    std::string operationDefinition;
    std::shared_ptr<MetaType> returnType;
    std::map<std::string, std::shared_ptr<MetaVariable>> variables;
    std::map<std::string, std::shared_ptr<PrePostClause>> preConditions;
    std::map<std::string, std::shared_ptr<PrePostClause>> postConditions;;

public:
    MetaOperation(const std::string& name, const std::string& operationDefinition, const std::shared_ptr<MetaType>& returnType);

    std::string getName() const;
    void setName(const std::string& name);

    std::string getOperationDefinition() const;
    void setOperationDefinition(const std::string& operationDefinition);

    const MetaType& getReturnType() const;
    void setReturnType(const std::shared_ptr<MetaType>& returnType);

    const std::map<std::string, std::shared_ptr<MetaVariable>>& getVariables() const;
    const MetaVariable* getVariable(const std::string& key) const;
    void addVariable(const std::shared_ptr<MetaVariable>& variable);
    void removeVariable(const std::string& key);

    const std::map<std::string, std::shared_ptr<PrePostClause>>& getPreConditions() const;
    const PrePostClause* getPreCondition(const std::string& key) const;
    void addPreCondition(const std::shared_ptr<PrePostClause>& preCondition);
    void removePreCondition(const std::string& key);

    const std::map<std::string, std::shared_ptr<PrePostClause>>& getPostConditions() const;
    const PrePostClause* getPostCondition(const std::string& key) const;
    void addPostCondition(const std::shared_ptr<PrePostClause>& postCondition);
    void removePostCondition(const std::string& key);

    bool isPrePostConditionDefined(const std::string& key);
};

}


#endif // METAOPERATION_H
