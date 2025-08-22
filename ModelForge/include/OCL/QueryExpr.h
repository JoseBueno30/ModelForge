#ifndef QUERYEXPR_H
#define QUERYEXPR_H

#include "PropertyCallExpr.h"

#include <metamodel/MetaVariable.h>

namespace MetaModel {

class QueryExpr : public PropertyCallExpr{
protected:
    std::map<std::string, std::shared_ptr<MetaVariable>> varsDeclaration;
    std::string varsDeclarationString;
    std::string queryType = "";
    std::shared_ptr<Expr> queryExpr;

    std::string buildExprString() const override;
public:
    QueryExpr(const std::string& expression,
              const bool isComplex,
              const std::shared_ptr<MetaType>& type,
              const bool arrow,
              const std::shared_ptr<Expr>& source,
              const std::string& varsDeclarationString,
              const std::shared_ptr<Expr>& queryExpr);

    const std::shared_ptr<Expr>& getSource() const;
};

class CollectExpr : public QueryExpr{
public:
    CollectExpr(const std::string& expression,
                const bool isComplex,
                const std::shared_ptr<MetaType>& type,
                const bool arrow,
                const std::shared_ptr<Expr>& source,
                const std::string& varsDeclarationString,
                const std::shared_ptr<Expr>& queryExpr);
};

class RejectExpr : public QueryExpr{
public:
    RejectExpr(const std::string& expression,
               const bool isComplex,
               const std::shared_ptr<MetaType>& type,
               const bool arrow,
               const std::shared_ptr<Expr>& source,
               const std::string& varsDeclarationString,
               const std::shared_ptr<Expr>& queryExpr);
};

class SelectExpr : public QueryExpr{
public:
    SelectExpr(const std::string& expression,
               const bool isComplex,
               const std::shared_ptr<MetaType>& type,
               const bool arrow,
               const std::shared_ptr<Expr>& source,
               const std::string& varsDeclarationString,
               const std::shared_ptr<Expr>& queryExpr);
};

class ExistsExpr : public QueryExpr{
public:
    ExistsExpr(const std::string& expression,
               const bool isComplex,
               const std::shared_ptr<MetaType>& type,
               const bool arrow,
               const std::shared_ptr<Expr>& source,
               const std::string& varsDeclarationString,
               const std::shared_ptr<Expr>& queryExpr);
};

class ForAllExpr : public QueryExpr{
public:
    ForAllExpr(const std::string& expression,
               const bool isComplex,
               const std::shared_ptr<MetaType>& type,
               const bool arrow,
               const std::shared_ptr<Expr>& source,
               const std::string& varsDeclarationString,
               const std::shared_ptr<Expr>& queryExpr);
};

class IsUniqueExpr : public QueryExpr{
public:
    IsUniqueExpr(const std::string& expression,
                 const bool isComplex,
                 const std::shared_ptr<MetaType>& type,
                 const bool arrow,
                 const std::shared_ptr<Expr>& source,
                 const std::string& varsDeclarationString,
                 const std::shared_ptr<Expr>& queryExpr);
};

class SortedByExpr : public QueryExpr{
public:
    SortedByExpr(const std::string& expression,
                 const bool isComplex,
                 const std::shared_ptr<MetaType>& type,
                 const bool arrow,
                 const std::shared_ptr<Expr>& source,
                 const std::string& varsDeclarationString,
                 const std::shared_ptr<Expr>& queryExpr);
};

}

#endif // QUERYEXPR_H
