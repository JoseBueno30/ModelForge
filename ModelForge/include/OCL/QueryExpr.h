#ifndef QUERYEXPR_H
#define QUERYEXPR_H

#include "PropertyCallExpr.h"

#include <metamodel/MetaVariable.h>

namespace MetaModel {

class QueryExpr : public PropertyCallExpr{
protected:
    std::map<std::string, std::shared_ptr<MetaVariable>> varsDeclaration;
public:
    QueryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class CollectExpr : public QueryExpr{
public:
    CollectExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class RejectExpr : public QueryExpr{
public:
    RejectExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class SelectExpr : public QueryExpr{
public:
    SelectExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class ExistsExpr : public QueryExpr{
public:
    ExistsExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class ForAllExpr : public QueryExpr{
public:
    ForAllExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class IsUniqueExpr : public QueryExpr{
public:
    IsUniqueExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class SortedByExpr : public QueryExpr{
public:
    SortedByExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

}

#endif // QUERYEXPR_H
