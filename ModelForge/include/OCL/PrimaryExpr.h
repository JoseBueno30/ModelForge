#ifndef PRIMARYEXPR_H
#define PRIMARYEXPR_H

#include "OCLExpr.h"

namespace MetaModel {
class PrimaryExpr : public Expr{
public:
    PrimaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type);
};

class ParenthesisExpr : public PrimaryExpr{
protected:
    std::shared_ptr<Expr> expr;
public:
    ParenthesisExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr);
};

class ObjectReferenceExpr : public PrimaryExpr{
protected:
    std::string reference;
public:
    ObjectReferenceExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::string& reference);
};

class LiteralExpr : public PrimaryExpr{
public:
    LiteralExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type);
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
