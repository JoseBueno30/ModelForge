#ifndef PROPERTYCALL_H
#define PROPERTYCALL_H

#include "OCLExpr.h"

namespace MetaModel{
class PropertyCallExpr : public Expr{
protected:
    bool arrow;
    std::shared_ptr<Expr> source;

    std::string buildExprString() const override;
public:
    PropertyCallExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);

    std::vector<std::shared_ptr<Expr>> getChildren() const override;
};

class IterateExpr : public PropertyCallExpr{
public:
    IterateExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

class InStateExpr : public PropertyCallExpr{
public:
    InStateExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source);
};

}

#endif // PROPERTYCALL_H
