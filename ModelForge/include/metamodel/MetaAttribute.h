#ifndef METAATTRIBUTE_H
#define METAATTRIBUTE_H



#include "MetaType.h"
#include "OCLExpression.h"

#include<string>

namespace MetaModel{

class MetaAttribute{
private:
    std::string name;
    std::shared_ptr<MetaType> type;
    std::unique_ptr<OCLExpr> initExpr;
    std::unique_ptr<OCLExpr> deriveExpr;

public:
    MetaAttribute(std::string name);

    std::string getName() const;
    void setName(std::string name);

    std::shared_ptr<MetaType> getType() const;
    void setType(const std::shared_ptr<MetaType> type);

    std::unique_ptr<OCLExpr> getInitExpr() const;
    void setInitExpr(const std::unique_ptr<OCLExpr> initExpr);

    std::unique_ptr<OCLExpr> getDeriveExpr() const;
    void setDeriveExpr(const std::unique_ptr<OCLExpr> deriveExpr);
};

}

#endif // METAATTRIBUTE_H
