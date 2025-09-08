#include <OCL/NavigationExpr.h>

namespace MetaModel {

NavigationExpr::NavigationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source,
                               const std::shared_ptr<MetaAssociationEnd>& src, const std::shared_ptr<MetaAssociationEnd>& dst)
    :OperationExpr(expression, isComplex, type, arrow, source), src(src), dst(dst){}

std::string NavigationExpr::buildExprString() const {
    return this->source->toString() + "." + (this->dst ? this->dst->getRole() : this->getExpression());
}

}
