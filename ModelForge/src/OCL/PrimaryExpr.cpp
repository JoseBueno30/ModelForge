#include <OCL/PrimaryExpr.h>

namespace MetaModel {
PrimaryExpr::PrimaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :Expr(expression, isComplex, type){}

ParenthesisExpr::ParenthesisExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr)
    :PrimaryExpr(expression, isComplex, type), expr(expr){}

ObjectReferenceExpr::ObjectReferenceExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::string& reference)
    :PrimaryExpr(expression, isComplex, type), reference(reference){}

LiteralExpr::LiteralExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :PrimaryExpr(expression, isComplex, type){}

AllInstancesExpr::AllInstancesExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :PrimaryExpr(expression, isComplex, type){}

ByUseIdExpr::ByUseIdExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :PrimaryExpr(expression, isComplex, type){}
}
