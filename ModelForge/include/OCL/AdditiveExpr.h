#ifndef ADDITIVEEXPR_H
#define ADDITIVEEXPR_H

#include "BinaryExpr.h"

namespace MetaModel{

class AdditiveExpr : public BinaryExpr{
public:
    AdditiveExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);

};

class AdditionExpr : public AdditiveExpr{
public:
    AdditionExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class SubtractionExpr : public AdditiveExpr{
public:
    SubtractionExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

}

#endif // ADDITIVEEXPR_H
