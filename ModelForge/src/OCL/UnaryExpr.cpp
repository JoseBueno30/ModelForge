#include <OCL/UnaryExpr.h>

namespace MetaModel {
UnaryExpr::UnaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    :Expr(expression, isComplex, type), expr(expr){}

std::string UnaryExpr::buildExprString() const {
    return this->symbol + this->expr->toString();
}

NotExpr::NotExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    : UnaryExpr(expression, isComplex, type, expr){
    this->symbol = "not";
}

std::string NotExpr::buildExprString() const {
    return this->symbol + " " + this->expr->toString();
}

MinusExpr::MinusExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    : UnaryExpr(expression, isComplex, type, expr){
    this->symbol = "-";
}

PlusExpr::PlusExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    : UnaryExpr(expression, isComplex, type, expr){
    this->symbol = "+";
}

}
