#ifndef UNARYEXPR_H
#define UNARYEXPR_H

#include "OCLExpr.h"

namespace MetaModel {
class UnaryExpr : public Expr{
protected:
    std::shared_ptr<Expr> expr;
    std::string symbol;
    std::string buildExprString() const override;
public:
    UnaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr);

    std::vector<std::shared_ptr<Expr>> getChildren() const override;
};

class NotExpr : public UnaryExpr{
protected:
    std::string buildExprString() const override;
public:
    NotExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr);
};

class MinusExpr : public UnaryExpr{
public:
    MinusExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr);
};

class PlusExpr : public UnaryExpr{
public:
    PlusExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr);
};
}


#endif // UNARYEXPR_H
