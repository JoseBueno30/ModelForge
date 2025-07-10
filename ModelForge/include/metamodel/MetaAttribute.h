#ifndef METAATTRIBUTE_H
#define METAATTRIBUTE_H



#include "MetaElement.h"
#include "MetaType.h"
#include "Visibility.h"
#include "OCL/OCLExpr.h"

#include<string>

namespace MetaModel{

class MetaAttribute: public MetaElement{
private:
    std::string name;
    std::shared_ptr<MetaType> type;
    MetaModel::Visibility visibility;
    std::shared_ptr<Expr> initExpr;
    std::shared_ptr<Expr> deriveExpr;

public:
    MetaAttribute(const std::string& name, const std::shared_ptr<MetaType>& type, Visibility visibility = Visibility::Public);

    std::string getName() const;
    void setName(const std::string& name);

    const MetaType& getType() const;
    const std::shared_ptr<MetaType>& getTypePtr() const;
    void setType(const std::shared_ptr<MetaType>& type);

    const Expr* getInitExpr() const;
    void setInitExpr(const std::shared_ptr<Expr>& initExpr);

    const Expr* getDeriveExpr() const;
    void setDeriveExpr(const std::shared_ptr<Expr>& deriveExpr);

    Visibility getVisibility() const;
    void setVisibility(Visibility vis);

    std::string toString() const;

    std::any accept(ModelToText::VisitorInterface& visitor) const override;
};

}

#endif // METAATTRIBUTE_H
