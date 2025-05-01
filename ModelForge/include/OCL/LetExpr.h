#ifndef LETEXPR_H
#define LETEXPR_H

#include "OCLExpr.h"

namespace MetaModel {
class LetExpr : public Expr{
protected:
    std::string name;
    std::shared_ptr<MetaType> varType;
    std::shared_ptr<Expr> varExpr;
    std::shared_ptr<Expr> inExpr;

public:
    LetExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::string& name, const std::shared_ptr<MetaType>& varType,  const std::shared_ptr<Expr>& varExpr,  const std::shared_ptr<Expr>& inExpr);
};
}

#endif // LETEXPR_H
