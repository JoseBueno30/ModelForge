#include "AdditiveExpr.h"

namespace MetaModel{

AdditiveExpr::AdditiveExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : BinaryExpr(expression, isComplex, type, expr1, expr2){}

AdditionExpr::AdditionExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : AdditiveExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "+";
}

SubstractionExpr::SubstractionExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : AdditiveExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "-";
}

}
