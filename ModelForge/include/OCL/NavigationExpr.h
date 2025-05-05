#ifndef NAVIGATIONEXPR_H
#define NAVIGATIONEXPR_H

#include "OperationExpr.h"

#include <metamodel/MetaAssociationEnd.h>

namespace MetaModel {

class NavigationExpr : public OperationExpr{
protected:
    std::shared_ptr<MetaAssociationEnd> src;
    std::shared_ptr<MetaAssociationEnd> dst;
public:
    NavigationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source,
                   const std::shared_ptr<MetaAssociationEnd>& src, const std::shared_ptr<MetaAssociationEnd>& dst);
};

}

#endif // NAVIGATIONEXPR_H
