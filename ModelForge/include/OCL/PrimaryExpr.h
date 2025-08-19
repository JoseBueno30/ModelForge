#ifndef PRIMARYEXPR_H
#define PRIMARYEXPR_H

#include "OCLExpr.h"

#include <any>

namespace MetaModel {
class PrimaryExpr : public Expr{
public:
    PrimaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type);
};

class ParenthesisExpr : public PrimaryExpr{
protected:
    std::shared_ptr<Expr> expr;
    std::string buildExprString() const override;
public:
    ParenthesisExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr);

    std::vector<std::shared_ptr<Expr>> getChildren() const override;
};

class ObjectReferenceExpr : public PrimaryExpr{
protected:
    std::string reference;
public:
    ObjectReferenceExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::string& reference);
};

class LiteralExpr : public PrimaryExpr{
protected:
    std::any value;
    std::string buildExprString() const override;
public:
    LiteralExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::any& value);
};

class AllInstancesExpr : public PrimaryExpr{
public:
    AllInstancesExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type);
};

class ByUseIdExpr : public PrimaryExpr{
public:
    ByUseIdExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type);
};


}

#endif // PRIMARYEXPR_H
