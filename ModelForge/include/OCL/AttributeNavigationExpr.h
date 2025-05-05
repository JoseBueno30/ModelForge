#ifndef ATTRIBUTENAVIGATIONEXPR_H
#define ATTRIBUTENAVIGATIONEXPR_H

#include "OperationExpr.h"

#include <metamodel/MetaAttribute.h>

namespace MetaModel {

class AttributeNavigationExpr : public OperationExpr{
protected:
    std::shared_ptr<MetaAttribute> attribute;
public:
    AttributeNavigationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow,
                            const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaAttribute>& attribute);
};

}

#endif // ATTRIBUTENAVIGATIONEXPR_H
