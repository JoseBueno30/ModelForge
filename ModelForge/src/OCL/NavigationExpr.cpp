#include <OCL/NavigationExpr.h>
#include <iostream>

namespace MetaModel {

NavigationExpr::NavigationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source,
                               const std::shared_ptr<MetaAssociationEnd>& src, const std::shared_ptr<MetaAssociationEnd>& dst)
    :OperationExpr(expression, isComplex, type, arrow, source), src(src), dst(dst){}

std::string NavigationExpr::buildExprString() const {
    // std::cout << "BUILDING NAVIGATION EXPR STR" << std::endl;
    // std::cout << "EXPR: " << this->getExpression() << std::endl;
    // std::cout << "SRC EXPR: " << this->source << std::endl;
    // std::cout << "IS SRC COMPLEX: " << this->source->isComplexExpr() << std::endl;
    // std::cout << "SRC EXPR: " << this->source->getExpression() << std::endl;
    // std::cout << "SRC STR: " << this->source->toString() << std::endl;
    return this->source->toString() + "." + (this->dst ? this->dst->getRole() : this->getExpression());
}

}
