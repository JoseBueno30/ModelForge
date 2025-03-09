#include <metamodel/MetaAssociationEnd.h>

#include <stdexcept>

namespace MetaModel{

MetaMultiplicityRange::MetaMultiplicityRange(int lowerBound, int upperBound)
    : lowerBound(lowerBound), upperBound(upperBound){
}

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
    this->addRange(lowerBound, upperBound);
}

const std::vector<std::shared_ptr<MetaMultiplicityRange>>& MetaMultiplicity::getRanges() const{
    return ranges;
}

void MetaMultiplicity::addRange(int lowerBound, int upperBound){
    if(lowerBound < 0 && lowerBound != -1 || upperBound < 0 && upperBound != -1){
        throw std::invalid_argument("Bounds can't be lower than 0.");
    }
    if(lowerBound > upperBound && upperBound != -1){
        throw std::invalid_argument("LowerBound can't be greater than upperBound. " + std::to_string(lowerBound) + " > " + std::to_string(upperBound));
    }

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

std::shared_ptr<MetaClass> MetaAssociationEnd::getClassSharedPtr() const{
    return this->endClass;
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

const std::map<std::string, std::shared_ptr<MetaAssociationEnd>>& MetaAssociationEnd::getRedefinedEnds() const{
    return redefinedEnds;
}

const MetaAssociationEnd* MetaAssociationEnd::getRedefinedEnd(const std::string& key) const{
    auto iterator = redefinedEnds.find(key);
    if(iterator != redefinedEnds.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaAssociationEnd::addRedefinedEnd(const std::shared_ptr<MetaAssociationEnd>& redefinedEnd){
    if (!redefinedEnd) {
        throw std::invalid_argument("Null redefined end");
    }

    if (redefinedEnds.find(redefinedEnd->getRole()) != redefinedEnds.end()) {//More generalization restrictions needed
        throw std::runtime_error("RedefinedEnd already declared: " + redefinedEnd->getRole());
    }

    redefinedEnds[redefinedEnd->getRole()] = redefinedEnd;
}

void MetaAssociationEnd::removeRedefinedEnd(const std::string& key){
    redefinedEnds.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaAssociationEnd>>& MetaAssociationEnd::getSubsettedEnds() const{
    return subsettedEnds;
}

void MetaAssociationEnd::addSubsettedEnd(const std::shared_ptr<MetaAssociationEnd>& subsettedEnd){
    if (!subsettedEnd) {
        throw std::invalid_argument("Null subsetted end");
    }

    if (subsettedEnds.find(subsettedEnd->getRole()) != subsettedEnds.end()) {//More generalization restrictions needed
        throw std::runtime_error("SubsettedEnd already declared: " + subsettedEnd->getRole());
    }

    subsettedEnds[subsettedEnd->getRole()] = subsettedEnd;
}

void MetaAssociationEnd::removeSubsettedEnd(const std::string& key){
    subsettedEnds.erase(key);
}

const std::map<std::string, std::shared_ptr<MetaVariable>>& MetaAssociationEnd::getQualifiers() const{
    return qualifiers;
}

const MetaAssociationEnd* MetaAssociationEnd::getSubsettedEnd(const std::string& key) const{
    auto iterator = subsettedEnds.find(key);
    if(iterator != subsettedEnds.end()){
        return (iterator->second).get();
    }
    return nullptr;
}


void MetaAssociationEnd::addQualifier(const std::shared_ptr<MetaVariable>& qualifier){
    if (!qualifier) {
        throw std::invalid_argument("Null qualifier");
    }

    if (qualifiers.find(qualifier->getName()) != qualifiers.end()) {//More generalization restrictions needed
        throw std::runtime_error("Qualifier already declared: " + qualifier->getName());
    }

    qualifiers[qualifier->getName()] = qualifier;
}

void MetaAssociationEnd::removeQualifier(const std::string& key){
    qualifiers.erase(key);
}

const MetaVariable* MetaAssociationEnd::getQualifier(const std::string& key) const{
    auto iterator = qualifiers.find(key);
    if(iterator != qualifiers.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

const OCLExpr* MetaAssociationEnd::getDeriveExpr() const{
    return deriveExpr.get();
}
void MetaAssociationEnd::setDeriveExpr(const std::shared_ptr<OCLExpr>& deriveExpr){
    this->deriveExpr = deriveExpr;
}


}
