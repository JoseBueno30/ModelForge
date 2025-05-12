#include <OCL/LetExpr.h>

namespace MetaModel {
LetExpr::LetExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::string& name,
                 const std::shared_ptr<MetaType>& varType,  const std::shared_ptr<Expr>& varExpr,  const std::shared_ptr<Expr>& inExpr)
    :Expr(expression, isComplex, type), name(name), varType(varType), varExpr(varExpr), inExpr(inExpr){}

std::string LetExpr::buildExprString() const {
    return this->expression;
}
}
