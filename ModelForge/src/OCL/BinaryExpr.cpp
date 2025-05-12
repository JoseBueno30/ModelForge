#include <OCL/BinaryExpr.h>

namespace MetaModel {
BinaryExpr::BinaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2)
    :Expr(expression, isComplex, type), expr1(expr1), expr2(expr2){}

std::string BinaryExpr::buildExprString() const {
    return this->expr1->toString() + " " + this->operation + " " + this->expr2->toString();
}

}

