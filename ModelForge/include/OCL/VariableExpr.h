#ifndef VARIABLEEXPR_H
#define VARIABLEEXPR_H

#include "OperationExpr.h"

namespace MetaModel {

class VariableExpr : public OperationExpr{
protected:
    std::string varName;
    std::string buildExprString() const override;
public:
    VariableExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::string& varName);
};
}

#endif // VARIABLEEXPR_H
