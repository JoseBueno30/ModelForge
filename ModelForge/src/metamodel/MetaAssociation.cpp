#include <metamodel/MetaAssociation.h>

namespace MetaModel{


MetaAssociation::MetaAssociation(const std::string& name, int type)
    : name(name), type(type){}

MetaAssociation::MetaAssociation(const std::string& name, int type, std::vector<std::unique_ptr<MetaAssociationEnd>> associationEnds)
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

const std::vector<std::unique_ptr<MetaAssociationEnd>>& MetaAssociation::getAssociationEnds() const{
    return associationEnds;
}

void MetaAssociation::addAssociationEnd(std::unique_ptr<MetaAssociationEnd> associationEnd){
    if(associationEnd){
        associationEnds.push_back(std::move(associationEnd));
    }
}
void MetaAssociation::removeAssociationEnd(int pos){
    if(pos>=0 && pos <  static_cast<int>(associationEnds.size())){
        associationEnds.erase(associationEnds.begin() + pos);

        if(associationEnds.size() < associationEnds.capacity()/2){
            associationEnds.shrink_to_fit();
        }
    }
}

}
