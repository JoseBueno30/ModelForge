#ifndef RELATIONALEXPR_H
#define RELATIONALEXPR_H

#include "BinaryExpr.h"

namespace MetaModel{

class RelationalExpr : public BinaryExpr{
public:
    RelationalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);

};

class LessThanExpr : public RelationalExpr{
public:
    LessThanExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class GreaterThanExpr : public RelationalExpr{
public:
    GreaterThanExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class LessThanOrEqualExpr : public RelationalExpr{
public:
    LessThanOrEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class GreaterThanOrEqualExpr : public RelationalExpr{
public:
    GreaterThanOrEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

}

#endif // RELATIONALEXPR_H
