#ifndef OPERATIONEXPR_H
#define OPERATIONEXPR_H

#include "PropertyCallExpr.h"

namespace MetaModel {

class OperationExpr : public PropertyCallExpr{
public:
    OperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class TupleSelectOperationExpr : public OperationExpr{
public:
    TupleSelectOperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class ObjectAsSetExpr : public OperationExpr{
public:
    ObjectAsSetExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class StandardOperationExpr : public OperationExpr{
public:
    StandardOperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

}

#endif // OPERATIONEXPR_H
