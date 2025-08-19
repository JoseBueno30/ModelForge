#include <OCL/ConditionalExpr.h>

namespace MetaModel{

ConditionalExpr::ConditionalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type,
                                 const std::shared_ptr<Expr>& ifExpr, const std::shared_ptr<Expr>& thenExpr, const std::shared_ptr<Expr>& elseExpr)
    :Expr(expression, isComplex, type), ifExpr(ifExpr), thenExpr(thenExpr), elseExpr(elseExpr){}

std::string ConditionalExpr::buildExprString() const {
    return "if " + this->ifExpr->toString() + " then " + this->thenExpr->toString() + " else " + this->elseExpr->toString() + " endif";
}

std::vector<std::shared_ptr<Expr>> ConditionalExpr::getChildren() const {
    return {this->ifExpr, this->thenExpr, this->elseExpr};
}

}
