#include <metamodel/MetaVariable.h>


namespace MetaModel{


MetaVariable::MetaVariable(const std::string& name, const std::shared_ptr<MetaType>& type)
    : name(name), type(type){}

std::string MetaVariable::getName() const{
    return name;
}

void MetaVariable::setName(const std::string& name){
    this->name = name;
}

const MetaType& MetaVariable::getType() const{
    return *type;
}

const std::shared_ptr<MetaType>& MetaVariable::getTypePtr() const{
    return type;
}

void MetaVariable::setType(const std::shared_ptr<MetaType>& type){
    this->type = type;
}

std::string MetaVariable::toString() const{
    return this->getName() + " : " + this->getType().toString();
}


}
