#ifndef TYPEEXPR_H
#define TYPEEXPR_H

#include "PropertyCallExpr.h"

namespace MetaModel {

class TypeExpr : public PropertyCallExpr{
protected:
    std::shared_ptr<MetaType> expressionType;
public:
    TypeExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType);
};

class OCLIsTypeOfExpr : public TypeExpr{
public:
    OCLIsTypeOfExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType);
};

class OCLIsKindOfExpr : public TypeExpr{
public:
    OCLIsKindOfExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType);
};

class OCLAsTypeExpr : public TypeExpr{
public:
    OCLAsTypeExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType);
};

class SelectByTypeExpr : public TypeExpr{
public:
    SelectByTypeExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType);
};

class SelectByKindExpr : public TypeExpr{
public:
    SelectByKindExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaType>& expressionType);
};

}
#endif // TYPEEXPR_H
