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
    std::shared_ptr<OCLExpr> initExpr;
    std::shared_ptr<OCLExpr> deriveExpr;

public:
    MetaAttribute(const std::string& name, const std::shared_ptr<MetaType>& type);

    std::string getName() const;
    void setName(const std::string& name);

    const MetaType& getType() const;
    void setType(const std::shared_ptr<MetaType>& type);

    const OCLExpr* getInitExpr() const;
    void setInitExpr(const std::shared_ptr<OCLExpr>& initExpr);

    const OCLExpr* getDeriveExpr() const;
    void setDeriveExpr(const std::shared_ptr<OCLExpr>& deriveExpr);
};

}

#endif // METAATTRIBUTE_H
