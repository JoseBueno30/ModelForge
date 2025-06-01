#ifndef METAATTRIBUTE_H
#define METAATTRIBUTE_H



#include "MetaType.h"
#include "OCL/OCLExpr.h"

#include<string>

namespace MetaModel{

class MetaAttribute{
private:
    std::string name;
    std::shared_ptr<MetaType> type;
    std::shared_ptr<Expr> initExpr;
    std::shared_ptr<Expr> deriveExpr;

public:
    MetaAttribute(const std::string& name, const std::shared_ptr<MetaType>& type);

    std::string getName() const;
    void setName(const std::string& name);

    const MetaType& getType() const;
    const std::shared_ptr<MetaType>& getTypePtr() const;
    void setType(const std::shared_ptr<MetaType>& type);

    const Expr* getInitExpr() const;
    void setInitExpr(const std::shared_ptr<Expr>& initExpr);

    const Expr* getDeriveExpr() const;
    void setDeriveExpr(const std::shared_ptr<Expr>& deriveExpr);

    std::string toString() const;
};

}

#endif // METAATTRIBUTE_H
