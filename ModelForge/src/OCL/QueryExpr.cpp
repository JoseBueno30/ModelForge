#include <OCL/QueryExpr.h>

namespace MetaModel {
QueryExpr::QueryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :PropertyCallExpr(expression, isComplex, type, arrow, source){}

CollectExpr::CollectExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :QueryExpr(expression, isComplex, type, arrow, source){}

RejectExpr::RejectExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :QueryExpr(expression, isComplex, type, arrow, source){}

SelectExpr::SelectExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :QueryExpr(expression, isComplex, type, arrow, source){}

ExistsExpr::ExistsExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :QueryExpr(expression, isComplex, type, arrow, source){}

ForAllExpr::ForAllExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :QueryExpr(expression, isComplex, type, arrow, source){}

IsUniqueExpr::IsUniqueExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :QueryExpr(expression, isComplex, type, arrow, source){}

SortedByExpr::SortedByExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :QueryExpr(expression, isComplex, type, arrow, source){}

}
