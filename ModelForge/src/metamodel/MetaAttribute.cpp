#include <metamodel/MetaAttribute.h>


namespace MetaModel{


MetaAttribute::MetaAttribute(const std::string& name, const std::shared_ptr<MetaType>& type)
    : name(name), type(type){}

std::string MetaAttribute::getName() const{
    return name;
}

void MetaAttribute::setName(const std::string& name){
    this->name = name;
}

const MetaType& MetaAttribute::getType() const{
    return *type;
}
void MetaAttribute::setType(const std::shared_ptr<MetaType>& type){
    this->type = type;
}

const OCLExpr* MetaAttribute::getInitExpr() const{
    return initExpr.get();
}
void MetaAttribute::setInitExpr(std::unique_ptr<OCLExpr> initExpr){
    this->initExpr = std::move(initExpr);
}

const OCLExpr* MetaAttribute::getDeriveExpr() const{
    return deriveExpr.get();
}
void MetaAttribute::setDeriveExpr(std::unique_ptr<OCLExpr> deriveExpr){

    this->deriveExpr = std::move(deriveExpr);
}


}
