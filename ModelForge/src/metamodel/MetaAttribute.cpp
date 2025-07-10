#include <modelToText/VisitorInterface.h>
#include <metamodel/MetaAttribute.h>

#include <stdexcept>


namespace MetaModel{


MetaAttribute::MetaAttribute(const std::string& name, const std::shared_ptr<MetaType>& type, Visibility visibility)
    : name(name), type(type), visibility(visibility){
    if (std::dynamic_pointer_cast<Void>(type)) {
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

const std::shared_ptr<MetaType>& MetaAttribute::getTypePtr() const{
    return type;
}

void MetaAttribute::setType(const std::shared_ptr<MetaType>& type){
    if (std::dynamic_pointer_cast<Void>(type)) {
        throw std::invalid_argument("Attribute cannot be of type Void.");
    }
    this->type = type;
}

const Expr* MetaAttribute::getInitExpr() const{
    return initExpr.get();
}
void MetaAttribute::setInitExpr(const std::shared_ptr<Expr>& initExpr){
    this->initExpr = initExpr;
}

const Expr* MetaAttribute::getDeriveExpr() const{
    return deriveExpr.get();
}
void MetaAttribute::setDeriveExpr(const std::shared_ptr<Expr>& deriveExpr){

    this->deriveExpr = deriveExpr;
}

Visibility MetaAttribute::getVisibility() const {
    return visibility;
}
void MetaAttribute::setVisibility(Visibility vis) {
    visibility = vis;
}

std::string MetaAttribute::toString() const{
    return this->getName() + " : " + this->getType().toString();
}

std::any MetaAttribute::accept(ModelToText::VisitorInterface& visitor) const{
    return visitor.visit(*this);
}

}
