#include <metamodel/MetaAssociation.h>

#include <stdexcept>

namespace MetaModel{


MetaAssociation::MetaAssociation(const std::string& name, int type)
    : name(name), type(type){}

MetaAssociation::MetaAssociation(const std::string& name, int type, std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds)
    : name(name), type(type), associationEnds(std::move(associationEnds)){}

std::string MetaAssociation::getName() const{
    return name;
}

void MetaAssociation::setName(const std::string& name){
    this->name = name;
}

int MetaAssociation::getType() const{
    return type;
}

void MetaAssociation::setType(int type){
    this->type = type;
}

const std::map<std::string, std::shared_ptr<MetaAssociationEnd>>& MetaAssociation::getAssociationEnds() const{
    return associationEnds;
}

const MetaAssociationEnd* MetaAssociation::getAssociationEnd(const std::string& key) const{
    auto iterator = associationEnds.find(key);
    if(iterator != associationEnds.end()){
        return (iterator->second).get();
    }
    return nullptr;
}


void MetaAssociation::addAssociationEnd(std::shared_ptr<MetaAssociationEnd> associationEnd){
    if (!associationEnd) {
        throw std::invalid_argument("Null super class");
    }

    if (associationEnds.find(associationEnd->getRole()) != associationEnds.end()) {//More generalization restrictions needed
        throw std::runtime_error("Generalization already declared: " + associationEnd->getRole());
    }

    associationEnds[associationEnd->getRole()] = associationEnd;
}
void MetaAssociation::removeAssociationEnd(const std::string& key){
    associationEnds.erase(key);
}

}
