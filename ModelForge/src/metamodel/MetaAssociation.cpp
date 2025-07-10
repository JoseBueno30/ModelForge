#include <metamodel/MetaAssociation.h>

#include <stdexcept>
#include <metamodel/MetaClass.h>
#include <modelToText/VisitorInterface.h>

namespace MetaModel{


MetaAssociation::MetaAssociation(const std::string& name, int type)
    : name(name), type(type){}

MetaAssociation::MetaAssociation(const std::string& name, int type, std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds)
    : name(name), type(type), associationEnds(std::move(associationEnds)){}

MetaAssociation::~MetaAssociation(){
    for(const auto &associationEndPair : this->getAssociationEnds()){
        associationEndPair.second->setAssociation(nullptr);
    }
}

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

std::shared_ptr<MetaAssociationEnd> MetaAssociation::getAssociationEnd(const std::string& key) {
    auto iterator = associationEnds.find(key);
    if(iterator != associationEnds.end()){
        return (iterator->second);
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

    associationEnds[associationEnd->getRole()] = std::move(associationEnd);
}
void MetaAssociation::removeAssociationEnd(const std::string& key){
    associationEnds.erase(key);
}

std::vector<std::string> MetaAssociation::getAssociationEndsClassesNames(){
    std::vector<std::string> names;
    for(auto& pair : this->associationEnds){
        names.push_back(pair.second->getClass().getName());
    }
    return names;
}

std::any MetaAssociation::accept(ModelToText::VisitorInterface& visitor) const{
    return visitor.visit(*this);
}

}
