#include "VariableExpr.h"


namespace MetaModel {

VariableExpr::VariableExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source, const std::string& varName)
    :OperationExpr(expression, isComplex, type, arrow, source), varName(varName){}

}
