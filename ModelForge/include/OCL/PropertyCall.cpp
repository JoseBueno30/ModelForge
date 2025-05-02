#include "PropertyCall.h"

namespace MetaModel {
PropertyCall::PropertyCall(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<PrimaryExpr>& source)
    :PrimaryExpr(expression, isComplex, type), arrow(arrow), source(source){}
}
