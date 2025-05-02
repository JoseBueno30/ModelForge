#ifndef PROPERTYCALL_H
#define PROPERTYCALL_H

#include "PrimaryExpr.h"

namespace MetaModel{
class PropertyCall : public PrimaryExpr{
protected:
    bool arrow;
    std::shared_ptr<PrimaryExpr> source;
public:
    PropertyCall(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const bool arrow, const std::shared_ptr<PrimaryExpr>& source);
};
}

#endif // PROPERTYCALL_H
