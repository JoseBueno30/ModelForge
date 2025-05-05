#include <OCL/UnaryExpr.h>

namespace MetaModel {
UnaryExpr::UnaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    :Expr(expression, isComplex, type), expr(expr){}

NotExpr::NotExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    : UnaryExpr(expression, isComplex, type, expr){
    this->symbol = "not";
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
