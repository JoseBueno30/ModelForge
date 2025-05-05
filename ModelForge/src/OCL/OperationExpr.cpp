#include <OCL/OperationExpr.h>

namespace MetaModel {
OperationExpr::OperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :PropertyCallExpr(expression, isComplex, type, arrow, source){}

TupleSelectOperationExpr::TupleSelectOperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :OperationExpr(expression, isComplex, type, arrow, source){}

ObjectAsSetExpr::ObjectAsSetExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :OperationExpr(expression, isComplex, type, arrow, source){}

StandardOperationExpr::StandardOperationExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<Expr>& source)
    :OperationExpr(expression, isComplex, type, arrow, source){}

}
