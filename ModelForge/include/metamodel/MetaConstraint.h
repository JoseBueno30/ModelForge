#ifndef METACONSTRAINT_H
#define METACONSTRAINT_H


#include "MetaVariable.h"
#include "OCL/OCLExpr.h"

#include<string>
#include<memory>
#include <vector>


namespace MetaModel{

class MetaClass;

class MetaConstraint{

private:
    std::string name;
    bool isExistential;
    std::shared_ptr<MetaClass> metaClass;
    std::shared_ptr<Expr> expression;
    std::map<std::string, std::shared_ptr<MetaVariable>> variables;

public:
    MetaConstraint(const std::shared_ptr<MetaClass>& metaClass, const std::shared_ptr<Expr>& expression, const std::string& name="", bool isExistential=false);
    MetaConstraint(const std::shared_ptr<MetaClass>& metaClass, const std::vector<std::string>& variableNames, const std::shared_ptr<Expr>& expression, const std::string& name="", bool isExistential=false);

    std::string getName() const;
    void setName(const std::string& name);

    const MetaClass& getClass() const;
    void setClass(const std::shared_ptr<MetaClass>& metaClass);

    bool getIsExistential() const;
    void setIsExistential(const bool isExistential);

    const Expr& getExpression() const;
    void setExpression(const std::shared_ptr<Expr>& expression);

    const std::map<std::string, std::shared_ptr<MetaVariable>>& getVariables() const;
    const MetaVariable* getVariable(const std::string& key) const;
    void addVariable(const std::string& variableName);
    void removeVariable(const std::string& key);
};

}

#endif // METACONSTRAINT_H
