#include <OCL/LogicalExpr.h>
#include <stdexcept>

namespace MetaModel{

LogicalExpr::LogicalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : BinaryExpr(expression, isComplex, type, expr1, expr2){
    if(!std::dynamic_pointer_cast<MetaModel::Boolean>(expr1->getType()) || !std::dynamic_pointer_cast<MetaModel::Boolean>(expr2->getType())){
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
    this->operation = "implies";
}

XOrExpr::XOrExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    : LogicalExpr(expression, isComplex, type, expr1, expr2){
    this->operation = "xor";
}

}
