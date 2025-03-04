#include <metamodel/MetaAttribute.h>

#include <stdexcept>


namespace MetaModel{


MetaAttribute::MetaAttribute(const std::string& name, const std::shared_ptr<MetaType>& type)
    : name(name), type(type){
    if (std::dynamic_pointer_cast<MetaModel::Void>(type)) {
        throw std::invalid_argument("Attribute cannot be of type Void.");
    }
}

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
    if (std::dynamic_pointer_cast<MetaModel::Void>(type)) {
        throw std::invalid_argument("Attribute cannot be of type Void.");
    }
    this->type = type;
}

const OCLExpr* MetaAttribute::getInitExpr() const{
    return initExpr.get();
}
void MetaAttribute::setInitExpr(const std::shared_ptr<OCLExpr>& initExpr){
    this->initExpr = initExpr;
}

const OCLExpr* MetaAttribute::getDeriveExpr() const{
    return deriveExpr.get();
}
void MetaAttribute::setDeriveExpr(const std::shared_ptr<OCLExpr>& deriveExpr){

    this->deriveExpr = deriveExpr;
}


}
