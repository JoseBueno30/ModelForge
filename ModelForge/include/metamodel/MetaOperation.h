#ifndef METAOPERATION_H
#define METAOPERATION_H

#include "OCL/OCLExpr.h"
#include "MetaElement.h"
#include "MetaType.h"
#include "MetaVariable.h"
#include "Visibility.h"

#include <memory>
#include <string>
#include <map>


namespace MetaModel{

class PrePostClause{

private:
    std::string name;
    std::shared_ptr<Expr> expression;
    bool isPre;
    bool isPost;

public:
    PrePostClause(const std::string& name, const std::shared_ptr<Expr>& expression, bool isPre, bool isPost);

    std::string getName() const;
    void setName(const std::string& name);

    const Expr& getExpression() const;
    void setExpression(const std::shared_ptr<Expr>& expression);

    bool getIsPre() const;
    void setIsPre(bool isPre);

    bool getIsPost() const;
    void setIsPost(bool isPost);
};

class MetaOperation: public MetaElement{

private:
    std::string name;
    std::string operationDefinition;
    std::shared_ptr<MetaType> returnType;
    MetaModel::Visibility visibility;
    std::map<std::string, std::shared_ptr<MetaVariable>> variables;
    std::map<std::string, std::shared_ptr<PrePostClause>> preConditions;
    std::map<std::string, std::shared_ptr<PrePostClause>> postConditions;

public:
    MetaOperation(const std::string& name, const std::string& operationDefinition,
                  const std::shared_ptr<MetaType>& returnType, Visibility visibility = Visibility::Public);

    std::string getName() const;
    void setName(const std::string& name);

    Visibility getVisibility() const;
    void setVisibility(Visibility vis);

    std::string getOperationDefinition() const;
    void setOperationDefinition(const std::string& operationDefinition);

    const MetaType& getReturnType() const;
    const std::shared_ptr<MetaType>& getReturnTypePtr() const;
    void setReturnType(const std::shared_ptr<MetaType>& returnType);

    const std::map<std::string, std::shared_ptr<MetaVariable>>& getVariables() const;
    const std::shared_ptr<MetaVariable> getVariable(const std::string& key) const;
    void addVariable(const std::shared_ptr<MetaVariable>& variable);
    void removeVariable(const std::string& key);

    const std::map<std::string, std::shared_ptr<PrePostClause>>& getPreConditions() const;
    const std::shared_ptr<PrePostClause> getPreCondition(const std::string& key) const;
    void addPreCondition(const std::shared_ptr<PrePostClause>& preCondition);
    void removePreCondition(const std::string& key);

    const std::map<std::string, std::shared_ptr<PrePostClause>>& getPostConditions() const;
    const std::shared_ptr<PrePostClause> getPostCondition(const std::string& key) const;
    void addPostCondition(const std::shared_ptr<PrePostClause>& postCondition);
    void removePostCondition(const std::string& key);

    bool isPrePostConditionDefined(const std::string& key);

    bool isValidOverrideOf(const MetaOperation& operation) const;

    std::string variablesToString() const;
    std::string toString() const;

    std::any accept(ModelToText::VisitorInterface& visitor) const override;
};

}


#endif // METAOPERATION_H
