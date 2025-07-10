#include <iostream>
#include <modelToText/VisitorInterface.h>
#include <metamodel/MetaAssociationEnd.h>

#include <stdexcept>

std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> resultado;
    size_t inicio = 0;
    size_t fin = str.find(delimiter);

    while (fin != std::string::npos) {
        resultado.push_back(str.substr(inicio, fin - inicio));
        inicio = fin + delimiter.length();
        fin = str.find(delimiter, inicio);
    }

    // Agrega la última parte
    resultado.push_back(str.substr(inicio));

    return resultado;
}

namespace MetaModel{

MetaMultiplicityRange::MetaMultiplicityRange(int lowerBound, int upperBound)
    : lowerBound(lowerBound), upperBound(upperBound){
    if(lowerBound < 0 && lowerBound != -1 || upperBound < 0 && upperBound != -1){
        throw std::invalid_argument("Bounds can't be lower than 0.");
    }
    if(lowerBound > upperBound && upperBound != -1){
        throw std::invalid_argument("LowerBound can't be greater than upperBound. " + std::to_string(lowerBound) + " > " + std::to_string(upperBound));
    }
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

std::string MetaMultiplicityRange::toString() const{
    std::string range = "";

    if(lowerBound < 0 && upperBound < 0){
        range = "*";
    }else if(lowerBound==upperBound){
        range = std::to_string(lowerBound);
    }else if(upperBound < 0){
        range = std::to_string(lowerBound) + "..*";
    }else{
        range = std::to_string(lowerBound) + ".." + std::to_string(upperBound);
    }

    return range;
}

int getMultiplicityValueFromString(std::string stringValue){
    if(stringValue == "*"){
        return -1;
    }else{
        return std::stoi(stringValue);
    }
}


MetaMultiplicity::MetaMultiplicity(int lowerBound, int upperBound){
    this->addRange(lowerBound, upperBound);
}

const std::vector<std::shared_ptr<MetaMultiplicityRange>>& MetaMultiplicity::getRanges() const{
    return ranges;
}

void MetaMultiplicity::addRange(int lowerBound, int upperBound){
    if(lowerBound < 0 && upperBound > -1){
        throw std::invalid_argument("Multiplicity many to <number> not allowed");
    }

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

std::string MetaMultiplicity::toString() const{
    std::string multiplicity = "";

    auto rangeIterator = ranges.begin();

    multiplicity += (*rangeIterator)->toString();

    rangeIterator++;

    for(; rangeIterator != ranges.end(); rangeIterator++){
        multiplicity += ", " + (*rangeIterator)->toString();
    }

    return multiplicity;
}

void MetaMultiplicity::setMultiplicictyFromString(std::string multiplicityString){
    auto rangesStrings = split(multiplicityString, ", ");
    this->ranges = std::vector<std::shared_ptr<MetaMultiplicityRange>>();
    for(auto rangeString : rangesStrings){
         std::cout << "x";
        auto bounds = split(rangeString, "..");
         std::cout << "x";
        if(bounds.size() == 1){
            int value = getMultiplicityValueFromString(bounds[0]);
             std::cout << "xx";
            this->addRange(value, value);
        }else{
            int lowerValue = getMultiplicityValueFromString(bounds[0]);
            int upperValue = getMultiplicityValueFromString(bounds[1]);
             std::cout << "xxx";
            this->addRange(lowerValue, upperValue);
        }
    }
}



MetaAssociationEnd::MetaAssociationEnd(const std::shared_ptr<MetaAssociation>& association, int type, Visibility visibility)
    : association(association), type(type), role(""), isNavigable(false), isOrdered(false), isUnique(false), isUnion(false), visibility(visibility){}

MetaAssociationEnd::MetaAssociationEnd(const std::shared_ptr<MetaClass>& endClass, const std::shared_ptr<MetaAssociation>& association,
                                       const std::string& role, int type, bool isNavigable, bool isOrdered, bool isUnique, bool isUnion,
                                       const std::shared_ptr<MetaMultiplicity>& multiplicity, Visibility visibility)
    : endClass(endClass), association(association), role(role), type(type), isNavigable(isNavigable), isOrdered(isOrdered),
    isUnique(isUnique), isUnion(isUnion), multiplicity(multiplicity), visibility(visibility){}

const MetaClass& MetaAssociationEnd::getClass() const{
    return *endClass;
}

std::shared_ptr<MetaClass> MetaAssociationEnd::getClassSharedPtr() const{
    return this->endClass;
}

void MetaAssociationEnd::setClass(const std::shared_ptr<MetaClass>& endClass){
    this->endClass = endClass;
}

const MetaAssociation& MetaAssociationEnd::getAssociation() const{
    return *association;
}

std::shared_ptr<MetaAssociation> MetaAssociationEnd::getAssociationSharedPtr() const{
    return this->association;
}

void MetaAssociationEnd::setAssociation(const std::shared_ptr<MetaAssociation>& association){
    this->association = association;
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

Visibility MetaAssociationEnd::getVisibility() const {
    return visibility;
}
void MetaAssociationEnd::setVisibility(Visibility vis) {
    visibility = vis;
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

const Expr* MetaAssociationEnd::getDeriveExpr() const{
    return deriveExpr.get();
}
void MetaAssociationEnd::setDeriveExpr(const std::shared_ptr<Expr>& deriveExpr){
    this->deriveExpr = deriveExpr;
}

std::any MetaAssociationEnd::accept(ModelToText::VisitorInterface& visitor) const{
    return visitor.visit(*this);
}

}
