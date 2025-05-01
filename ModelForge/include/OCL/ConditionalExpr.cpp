#include "ConditionalExpr.h"

namespace MetaModel{

ConditionalExpr::ConditionalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type,
                                 const std::shared_ptr<Expr>& ifExpr, const std::shared_ptr<Expr>& thenExpr, const std::shared_ptr<Expr>& elseExpr)
    :Expr(expression, isComplex, type), ifExpr(ifExpr), thenExpr(thenExpr), elseExpr(elseExpr){}

}
