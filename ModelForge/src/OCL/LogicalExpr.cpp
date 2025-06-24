#include <OCL/LogicalExpr.h>
#include <stdexcept>

namespace MetaModel{

LogicalExpr::LogicalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : BinaryExpr(expression, isComplex, type, expr1, expr2){
    if(expr1->getType() != MetaModel::Boolean::instance() || expr2->getType() != MetaModel::Boolean::instance()){
        throw std::invalid_argument("Logical Expression expects a Boolean expressions");
    }
}

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
