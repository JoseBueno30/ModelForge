#include <OCL/RelationalExpr.h>

namespace MetaModel{

RelationalExpr::RelationalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : BinaryExpr(expression, isComplex, type, expr1, expr2){}

LessThanExpr::LessThanExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : RelationalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "<";
}

GreaterThanExpr::GreaterThanExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : RelationalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = ">";
}

LessThanOrEqualExpr::LessThanOrEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : RelationalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "<=";
}

GreaterThanOrEqualExpr::GreaterThanOrEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : RelationalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = ">=";
}

}
