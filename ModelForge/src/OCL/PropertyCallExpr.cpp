#include <OCL/PropertyCallExpr.h>
#include <iostream>

namespace MetaModel {
PropertyCallExpr::PropertyCallExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :Expr(expression, isComplex, type), arrow(arrow), source(source){}

std::string PropertyCallExpr::buildExprString() const {
    // std::cout << "BUILDING PROPERTY CALL EXPR STR" << std::endl;
    // std::cout << "EXPR: " << this->getExpression() << std::endl;
    // std::cout << "SRC EXPR: " << this->source << std::endl;
    // std::cout << "IS SRC COMPLEX: " << this->source->isComplexExpr() << std::endl;
    // std::cout << "SRC EXPR: " << this->source->getExpression() << std::endl;
    // std::cout << "SRC STR: " << this->source->toString() << std::endl;
    return this->source->toString() + (this->arrow ? " -> " : ".") + this->getExpression();
}

std::vector<std::shared_ptr<Expr>> PropertyCallExpr::getChildren() const {
    return {this->source};
}

IterateExpr::IterateExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :PropertyCallExpr(expression, isComplex, type, arrow, source){}

InStateExpr::InStateExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :PropertyCallExpr(expression, isComplex, type, arrow, source){}
}
