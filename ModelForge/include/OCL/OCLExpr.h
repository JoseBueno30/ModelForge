#ifndef OCLEXPR_H
#define OCLEXPR_H
#include <memory>
#include <string>

#include <metamodel/MetaType.h>

namespace MetaModel{
class Expr{
private:
    std::string expression;
    bool isComplex;
    std::shared_ptr<MetaType> type;

public:
    Expr();
    Expr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type);
    Expr(const std::string& expression);

    std::string getExpression() const;
    void setExpression(const std::string& expression);

    bool isComplexExpr();
};

}


#endif // OCLEXPR_H
