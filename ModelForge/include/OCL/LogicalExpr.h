#ifndef LOGICALEXPR_H
#define LOGICALEXPR_H

#include "BinaryExpr.h"

namespace MetaModel{

class LogicalExpr : public BinaryExpr{
public:
    LogicalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);

};

class AndExpr : public LogicalExpr{
public:
    AndExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class OrExpr : public LogicalExpr{
public:
    OrExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class ImpliesExpr : public LogicalExpr{
public:
    ImpliesExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

class XOrExpr : public LogicalExpr{
public:
    XOrExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);
};

}

#endif // LOGICALEXPR_H
