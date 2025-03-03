#include <metamodel/MetaAssociationClass.h>

#include <stdexcept>

namespace MetaModel{

MetaAssociationClass::MetaAssociationClass(const std::string& name, bool isAbstract, int type)
    : MetaClass(name, isAbstract), MetaAssociation(name, type){}

MetaAssociationClass::MetaAssociationClass(const std::string& name, bool isAbstract, int type, std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds)
    : MetaClass(name, isAbstract), MetaAssociation(name, type, std::move(associationEnds)){}

std::string MetaAssociationClass::getName() const{
    return MetaClass::getName();
}

void MetaAssociationClass::setName(const std::string& name){
    MetaClass::setName(name);
    MetaAssociation::setName(name);
}

void MetaAssociationClass::addSuperClass(std::shared_ptr<MetaClass> metaClass){
    if (!std::dynamic_pointer_cast<MetaAssociationClass>(metaClass)) {
        throw std::invalid_argument("MetaAssociationClass can only inherit from another MetaAssociationClass");
    }
    MetaClass::addSuperClass(metaClass);
}

}
