#ifndef FACTOREXPR_H
#define FACTOREXPR_H

#include "BinaryExpr.h"

namespace MetaModel{

class FactorExpr : public BinaryExpr{
public:
    FactorExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);

};

class MultiplicationExpr : public FactorExpr{
    MultiplicationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class DivisionExpr : public FactorExpr{
    DivisionExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

}

#endif // FACTOREXPR_H
