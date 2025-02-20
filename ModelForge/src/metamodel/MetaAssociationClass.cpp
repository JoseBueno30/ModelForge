#include <metamodel/MetaAssociationClass.h>

namespace MetaModel{

MetaAssociationClass::MetaAssociationClass(const std::string& name, bool isAbstract, int type)
    : MetaClass(name, isAbstract), MetaAssociation(name, type){}

MetaAssociationClass::MetaAssociationClass(const std::string& name, bool isAbstract, int type, std::vector<std::unique_ptr<MetaAssociationEnd>> associationEnds)
    : MetaClass(name, isAbstract), MetaAssociation(name, type, std::move(associationEnds)){}

std::string MetaAssociationClass::getName() const{
    return MetaClass::getName();
}

void MetaAssociationClass::setName(const std::string& name){
    MetaClass::setName(name);
    MetaAssociation::setName(name);
}

}
