#include <OCL/TypeExpr.h>

namespace MetaModel {
TypeExpr::TypeExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType)
    :PropertyCallExpr(expression, isComplex, type, arrow, source), expressionType(expressionType){}

OCLIsTypeOfExpr::OCLIsTypeOfExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType)
    :TypeExpr(expression, isComplex, type, arrow, source, expressionType){}

OCLIsKindOfExpr::OCLIsKindOfExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType)
    :TypeExpr(expression, isComplex, type, arrow, source, expressionType){}

OCLAsTypeExpr::OCLAsTypeExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType)
    :TypeExpr(expression, isComplex, type, arrow, source, expressionType){}

SelectByTypeExpr::SelectByTypeExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType)
    :TypeExpr(expression, isComplex, type, arrow, source, expressionType){}

SelectByKindExpr::SelectByKindExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType)
    :TypeExpr(expression, isComplex, type, arrow, source, expressionType){}

}
