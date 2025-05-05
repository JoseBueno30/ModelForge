#ifndef OBJECTOPERATIONEXPR_H
#define OBJECTOPERATIONEXPR_H

#include "OperationExpr.h"

#include <metamodel/MetaClass.h>

namespace MetaModel {

class ObjectOperationExpr : public OperationExpr{
protected:
    std::shared_ptr<MetaClass> srcClass;
public:
    ObjectOperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow,
                            const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaClass>& srcClass);
};

}

#endif // OBJECTOPERATIONEXPR_H
