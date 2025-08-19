#ifndef BINARYEXPR_H
#define BINARYEXPR_H

#include "OCLExpr.h"

namespace MetaModel {
class BinaryExpr : public Expr{
protected:
    std::shared_ptr<Expr> expr1;
    std::shared_ptr<Expr> expr2;
    std::string operation;
    std::string buildExprString() const override;
public:
    BinaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr1, const std::shared_ptr<Expr>& expr2);

    std::vector<std::shared_ptr<Expr>> getChildren() const override;
};
}

#endif // BINARYEXPR_H
