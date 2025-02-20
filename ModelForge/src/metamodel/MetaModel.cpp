#include <metamodel/MetaModel.h>

namespace MetaModel{

MetaModel::MetaModel(const std::string& name)
    : name(name){}

std::string MetaModel::getName() const{
    return name;
}

void MetaModel::setName(const std::string& name){
    this->name = name;
}

const std::vector<std::unique_ptr<MetaEnum>>& MetaModel::getEnums() const{
    return enums;
}

void MetaModel::addEnum(std::unique_ptr<MetaEnum> modelEnum){
    if(modelEnum){
        enums.push_back(std::move(modelEnum));
    }
}

void MetaModel::removeEnum(int pos){
    if(pos>=0 && pos <  static_cast<int>(enums.size())){
        enums.erase(enums.begin() + pos);

        if(enums.size() < enums.capacity()/2){
            enums.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaClass>>& MetaModel::getClasses() const{
    return classes;
}

void MetaModel::addClass(std::unique_ptr<MetaClass> modelClass){
    if(modelClass){
        classes.push_back(std::move(modelClass));
    }
}

void MetaModel::removeClass(int pos){
    if(pos>=0 && pos <  static_cast<int>(classes.size())){
        classes.erase(classes.begin() + pos);

        if(classes.size() < classes.capacity()/2){
            classes.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaAssociation>>& MetaModel::getAssociations() const{
    return associations;
}

void MetaModel::addAssociation(std::unique_ptr<MetaAssociation> modelAssociation){
    if(modelAssociation){
        associations.push_back(std::move(modelAssociation));
    }
}

void MetaModel::removeAssociation(int pos){
    if(pos>=0 && pos <  static_cast<int>(associations.size())){
        associations.erase(associations.begin() + pos);

        if(associations.size() < associations.capacity()/2){
            associations.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaAssociationClass>>& MetaModel::getAssociationClasses() const{
    return associationClasses;
}

void MetaModel::addAssociationClass(std::unique_ptr<MetaAssociationClass> modelAssociationClass){
    if(modelAssociationClass){
        associationClasses.push_back(std::move(modelAssociationClass));
    }
}

void MetaModel::removeAssociationClass(int pos){
    if(pos>=0 && pos <  static_cast<int>(associationClasses.size())){
        associationClasses.erase(associationClasses.begin() + pos);

        if(associationClasses.size() < associationClasses.capacity()/2){
            associationClasses.shrink_to_fit();
        }
    }
}


}
