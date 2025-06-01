#include <OCL/AttributeNavigationExpr.h>

namespace MetaModel {

AttributeNavigationExpr::AttributeNavigationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type,
                                                 const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaAttribute>& attribute)
    :OperationExpr(expression, isComplex, type, arrow, source), attribute(attribute){}

std::string AttributeNavigationExpr::buildExprString() const {
    return this->source->toString() + "." + this->attribute->getName();
}
}
