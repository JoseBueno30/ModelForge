#ifndef EQUALITYEXPR_H
#define EQUALITYEXPR_H

#include "BinaryExpr.h"

namespace MetaModel{

class EqualityExpr : public BinaryExpr{
public:
    EqualityExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class EqualExpr : public EqualityExpr{
    EqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class NotEqualExpr : public EqualityExpr{
    NotEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

}

#endif // EQUALITYEXPR_H
