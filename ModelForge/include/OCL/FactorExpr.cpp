#include "FactorExpr.h"

namespace MetaModel{

FactorExpr::FactorExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : BinaryExpr(expression, isComplex, type, expr1, expr2){}

MultiplicationExpr::MultiplicationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : FactorExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "*";
}

DivisionExpr::DivisionExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : FactorExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "/";
}

}
