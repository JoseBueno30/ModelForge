#ifndef OCLEXPR_H
#define OCLEXPR_H
#include <memory>
#include <string>
#include <vector>

#include <metamodel/MetaType.h>

namespace MetaModel{
class Expr{
protected:
    std::string expression;
    bool isComplex;
    bool parenthesis = false;
    std::shared_ptr<MetaType> type;

    virtual std::string buildExprString() const;

    std::string wrapWithParentheses(const std::string& str, bool parenthesis) const;

public:
    Expr();
    Expr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type);
    Expr(const std::string& expression);

    std::string getExpression() const;
    void setExpression(const std::string& expression);

    const std::shared_ptr<MetaType> getType() const;

    bool isComplexExpr() const;

    bool hasParenthesis();
    void setHasParenthesis(bool parenthesis);

    virtual std::string toString() const;

    virtual std::vector<std::shared_ptr<Expr>> getChildren() const;
    virtual ~Expr() = default;
};

}


#endif // OCLEXPR_H
