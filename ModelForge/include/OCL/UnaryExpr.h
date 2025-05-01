#ifndef UNARYEXPR_H
#define UNARYEXPR_H

#include "OCLExpr.h"

namespace MetaModel {
class UnaryExpr : public Expr{
protected:
    std::shared_ptr<Expr> expr;
    std::string symbol;
public:
    UnaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr);
};

class NotExpr : public UnaryExpr{
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
