#ifndef ATTRIBUTENAVIGATIONEXPR_H
#define ATTRIBUTENAVIGATIONEXPR_H

#include "OperationExpr.h"

#include <metamodel/MetaAttribute.h>

namespace MetaModel {

class AttributeNavigationExpr : public OperationExpr{
protected:
    std::shared_ptr<MetaAttribute> attribute;
    std::string buildExprString() const override;
public:
    AttributeNavigationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow,
                            const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaAttribute>& attribute);

    const MetaAttribute& getAttribute() const;
};
}

#endif // ATTRIBUTENAVIGATIONEXPR_H
