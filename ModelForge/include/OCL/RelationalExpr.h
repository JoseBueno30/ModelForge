#ifndef RELATIONALEXPR_H
#define RELATIONALEXPR_H

#include "BinaryExpr.h"

namespace MetaModel{

class RelationalExpr : public BinaryExpr{
public:
    RelationalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);

};

class LessThanExpr : public RelationalExpr{
    LessThanExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class GreaterThanExpr : public RelationalExpr{
    GreaterThanExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class LessThanOrEqualExpr : public RelationalExpr{
    LessThanOrEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class GreaterThanOrEqualExpr : public RelationalExpr{
    GreaterThanOrEqualExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

}

#endif // RELATIONALEXPR_H
