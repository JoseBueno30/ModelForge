#include <OCL/EqualityExpr.h>

namespace MetaModel{

EqualityExpr::EqualityExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : BinaryExpr(expression, isComplex, type, expr1, expr2){}

EqualExpr::EqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : EqualityExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "=";
}

NotEqualExpr::NotEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : EqualityExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "<>";
}

}
