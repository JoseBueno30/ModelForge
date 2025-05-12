#ifndef CONDITIONALEXPR_H
#define CONDITIONALEXPR_H

#include "OCLExpr.h"

namespace MetaModel {
class ConditionalExpr : public Expr{
protected:
    std::shared_ptr<Expr> ifExpr;
    std::shared_ptr<Expr> thenExpr;
    std::shared_ptr<Expr> elseExpr;
    std::string buildExprString() const override;
public:
    ConditionalExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type,
                    const std::shared_ptr<Expr>& ifExpr, const std::shared_ptr<Expr>& thenExpr, const std::shared_ptr<Expr>& elseExpr);
};
}

#endif // CONDITIONALEXPR_H
