#include <metamodel/MetaAssociationEnd.h>

namespace MetaModel{

MetaMultiplicityRange::MetaMultiplicityRange(int lowerBound, int upperBound)
    : lowerBound(lowerBound), upperBound(upperBound){}

int MetaMultiplicityRange::getLowerBound() const{
    return lowerBound;
}

void MetaMultiplicityRange::setLowerBound(int lowerBound){
    this->lowerBound = lowerBound;
}

int MetaMultiplicityRange::getUpperBound() const{
    return upperBound;
}
void MetaMultiplicityRange::setUpperBound(int upperBound){
    this->upperBound = upperBound;
}



MetaMultiplicity::MetaMultiplicity(int lowerBound, int upperBound){
    ranges.push_back(std::make_unique<MetaMultiplicityRange>(lowerBound, upperBound));
}

const std::vector<std::unique_ptr<MetaMultiplicityRange>>& MetaMultiplicity::getRanges() const{
    return ranges;
}

void MetaMultiplicity::addRange(int lowerBound, int upperBound){
    ranges.push_back(std::make_unique<MetaMultiplicityRange>(lowerBound, upperBound));
}

void MetaMultiplicity::deleteRange(int pos){
    if(pos>=0 && pos <  static_cast<int>(ranges.size())){
        ranges.erase(ranges.begin() + pos);

        if(ranges.size() < ranges.capacity()/2){
            ranges.shrink_to_fit();
        }
    }
}



MetaAssociationEnd::MetaAssociationEnd(const std::shared_ptr<MetaClass>& endClass, const std::string& role, int type, bool isNavigable, bool isOrdered, bool isUnique, bool isUnion, const std::shared_ptr<MetaMultiplicity>& multiplicity)
    : endClass(endClass), role(role), type(type), isNavigable(isNavigable), isOrdered(isOrdered), isUnique(isUnique), isUnion(isUnion), multiplicity(multiplicity){}

const MetaClass& MetaAssociationEnd::getClass() const{
    return *endClass;
}

void MetaAssociationEnd::setClass(const std::shared_ptr<MetaClass>& endClass){
    this->endClass = endClass;
}

std::string MetaAssociationEnd::getRole() const{
    return role;
}

void MetaAssociationEnd::setRole(const std::string& role){
    this->role = role;
}

int MetaAssociationEnd::getType() const{
    return type;
}

void MetaAssociationEnd::setType(int type){
    this->type = type;
}

bool MetaAssociationEnd::getIsNavigable() const{
    return isNavigable;
}

void MetaAssociationEnd::setIsNavigable(bool isNavigable){
    this->isNavigable = isNavigable;
}

bool MetaAssociationEnd::getIsOrdered() const{
    return isOrdered;
}

void MetaAssociationEnd::setIsOrdered(bool isOrdered){
    this->isOrdered = isOrdered;
}

bool MetaAssociationEnd::getIsUnique() const{
    return isUnique;
}

void MetaAssociationEnd::setIsUnique(bool isUnique){
    this->isUnique = isUnique;
}

bool MetaAssociationEnd::getIsUnion() const{
    return isUnion;
}

void MetaAssociationEnd::setIsUnion(bool isUnion){
    this->isUnion = isUnion;
}

const MetaMultiplicity& MetaAssociationEnd::getMultiplicity() const{
    return *multiplicity;
}

void MetaAssociationEnd::setMultiplicity(const std::shared_ptr<MetaMultiplicity>& multiplicity){
    this->multiplicity = multiplicity;
}

const std::vector<std::shared_ptr<MetaAssociationEnd>>& MetaAssociationEnd::getRedefinedEnds() const{
    return redefinedEnds;
}

void MetaAssociationEnd::addRedefinedEnd(const std::shared_ptr<MetaAssociationEnd>& redefinedEnd){
    if(redefinedEnd){
        redefinedEnds.push_back(redefinedEnd);
    }
}

void MetaAssociationEnd::removeRedefinedEnd(int pos){
    if(pos>=0 && pos <  static_cast<int>(redefinedEnds.size())){
        redefinedEnds.erase(redefinedEnds.begin() + pos);

        if(redefinedEnds.size() < redefinedEnds.capacity()/2){
            redefinedEnds.shrink_to_fit();
        }
    }
}

const std::vector<std::shared_ptr<MetaAssociationEnd>>& MetaAssociationEnd::getSubsettedEnds() const{
    return subsettedEnds;
}

void MetaAssociationEnd::addSubsettedEnd(const std::shared_ptr<MetaAssociationEnd>& subsettedEnd){
    if(subsettedEnd){
        subsettedEnds.push_back(subsettedEnd);
    }
}

void MetaAssociationEnd::removeSubsettedEnd(int pos){
    if(pos>=0 && pos <  static_cast<int>(subsettedEnds.size())){
        subsettedEnds.erase(subsettedEnds.begin() + pos);

        if(subsettedEnds.size() < subsettedEnds.capacity()/2){
            subsettedEnds.shrink_to_fit();
        }
    }
}

const std::vector<std::unique_ptr<MetaVariable>>& MetaAssociationEnd::getQualifiers() const{
    return qualifiers;
}

void MetaAssociationEnd::addQualifier(std::unique_ptr<MetaVariable> qualifier){
    if(qualifier){
        qualifiers.push_back(std::move(qualifier));
    }
}

void MetaAssociationEnd::removeQualifier(int pos){
    if(pos>=0 && pos <  static_cast<int>(qualifiers.size())){
        qualifiers.erase(qualifiers.begin() + pos);

        if(qualifiers.size() < qualifiers.capacity()/2){
            qualifiers.shrink_to_fit();
        }
    }
}

const OCLExpr* MetaAssociationEnd::getDeriveExpr() const{
    return deriveExpr.get();
}
void MetaAssociationEnd::setDeriveExpr(std::unique_ptr<OCLExpr> deriveExpr){
    this->deriveExpr = std::move(deriveExpr);
}


}
