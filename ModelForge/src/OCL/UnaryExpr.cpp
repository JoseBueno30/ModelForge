#include <OCL/UnaryExpr.h>
#include <stdexcept>

namespace MetaModel {
UnaryExpr::UnaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    :Expr(expression, isComplex, type), expr(expr){}

std::string UnaryExpr::buildExprString() const {
    return this->symbol + this->expr->toString();
}

std::vector<std::shared_ptr<Expr>> UnaryExpr::getChildren() const {
    return {this->expr};
}

NotExpr::NotExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    : UnaryExpr(expression, isComplex, type, expr){
    if(!expr->isComplexExpr() && !std::dynamic_pointer_cast<MetaModel::Boolean>(expr->getType())){
        throw std::invalid_argument("NotExpr expects a Boolean expression");
    }
    this->symbol = "not";
}

std::string NotExpr::buildExprString() const {
    return this->symbol + " " + this->expr->toString();
}

MinusExpr::MinusExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    : UnaryExpr(expression, isComplex, type, expr){
    if(!expr->isComplexExpr() && !std::dynamic_pointer_cast<MetaModel::Integer>(expr->getType()) && !std::dynamic_pointer_cast<MetaModel::Real>(expr->getType())){
        throw std::invalid_argument("MinusExpr expects a numeric expression");
    }
    this->symbol = "-";
}

PlusExpr::PlusExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr> expr)
    : UnaryExpr(expression, isComplex, type, expr){
    if(!expr->isComplexExpr() && !std::dynamic_pointer_cast<MetaModel::Integer>(expr->getType()) && !std::dynamic_pointer_cast<MetaModel::Real>(expr->getType())){
        throw std::invalid_argument("PlusExpr expects a numeric expression");
    }
    this->symbol = "+";
}

}
