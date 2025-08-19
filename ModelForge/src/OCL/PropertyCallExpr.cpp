#include <OCL/PropertyCallExpr.h>

namespace MetaModel {
PropertyCallExpr::PropertyCallExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :Expr(expression, isComplex, type), arrow(arrow), source(source){}

std::vector<std::shared_ptr<Expr>> PropertyCallExpr::getChildren() const {
    return {this->source};
}

IterateExpr::IterateExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :PropertyCallExpr(expression, isComplex, type, arrow, source){}

InStateExpr::InStateExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :PropertyCallExpr(expression, isComplex, type, arrow, source){}
}
