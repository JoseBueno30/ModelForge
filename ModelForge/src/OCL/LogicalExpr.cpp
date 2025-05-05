#include "LogicalExpr.h"

namespace MetaModel{

LogicalExpr::LogicalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : BinaryExpr(expression, isComplex, type, expr1, expr2){}

AndExpr::AndExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : LogicalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "and";
}

OrExpr::OrExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : LogicalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "or";
}

ImpliesExpr::ImpliesExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : LogicalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "xor";
}

XOrExpr::XOrExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : LogicalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "implies";
}

}
