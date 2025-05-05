#include <OCL/ObjectOperationExpr.h>

namespace MetaModel {

ObjectOperationExpr::ObjectOperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type,
                                                 const bool arrow, const std::shared_ptr<Expr>& source, const std::shared_ptr<MetaClass>& srcClass)
    :OperationExpr(expression, isComplex, type, arrow, source), srcClass(srcClass){}

}
