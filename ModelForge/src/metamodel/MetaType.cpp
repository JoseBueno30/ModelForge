#include <metamodel/MetaType.h>

#include <stdexcept>

namespace MetaModel {

std::string MetaType::toString() const{
    return "MetaType";
}

std::string SimpleType::toString() const{
    return "SimpleType";
}

std::string Real::toString() const{
    return "Real";
}

std::string Integer::toString() const{
    return "Integer";
}

std::string Boolean::toString() const{
    return "Boolean";
}

std::string String::toString() const{
    return "String";
}

std::string Void::toString() const{
    return "Void";
}

CollectionType::CollectionType(bool ordered, bool unique, int multiplicity, const std::shared_ptr<MetaType>& type)
    : isOrdered(ordered), isUnique(unique), multiplicity(multiplicity), type(type)
{
    // posibles validaciones, por ejemplo:
    // if (multiplicity < 0) {
    //     throw std::invalid_argument("Multiplicity must be non-negative (or -1 for MANY).");
    // }
}

bool CollectionType::getIsOrdered() const {
    return isOrdered;
}

void CollectionType::setIsOrdered(bool isOrdered) {
    this->isOrdered = isOrdered;
}

bool CollectionType::getIsUnique() const {
    return isUnique;
}

void CollectionType::setIsUnique(bool isUnique) {
    this->isUnique = isUnique;
}

int CollectionType::getMultiplicity() const {
    return multiplicity;
}

void CollectionType::setMultiplicity(int multiplicity) {
    // Puedes agregar comprobaciones si es necesario
    this->multiplicity = multiplicity;
}

const MetaType& CollectionType::getType() const {
    return *type;
}

void CollectionType::setType(const std::shared_ptr<MetaType>& type) {
    this->type = type;
}

std::string CollectionType::toString() const{
    return "Collection<" + this->getType().toString() + ">";
}


TuplePart::TuplePart(const std::string& name, const std::shared_ptr<MetaType>& type)
    : name(name), type(type)
{
}

std::string TuplePart::getName() const {
    return name;
}

void TuplePart::setName(const std::string& name) {
    this->name = name;
}

const MetaType& TuplePart::getType() const {
    return *type;
}

void TuplePart::setType(const std::shared_ptr<MetaType>& type) {
    this->type = type;
}

TupleType::TupleType(std::unique_ptr<TuplePart> element) {
    if (!element) {
        throw std::invalid_argument("Null TuplePart");
    }

    if (elements.find(element->getName()) != elements.end()) {
        throw std::runtime_error("TuplePart already declared: " + element->getName());
    }

    elements[element->getName()] = std::move(element);
}

const std::map<std::string, std::unique_ptr<TuplePart>>& TupleType::getElements() const{
    return elements;
}

const TuplePart* TupleType::getElement(const std::string& key) const{
    auto iterator = elements.find(key);
    if(iterator != elements.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void TupleType::addElement(std::unique_ptr<TuplePart> newElement){
    if (!newElement) {
        throw std::invalid_argument("Null TuplePart");
    }

    if (elements.find(newElement->getName()) != elements.end()) {
        throw std::runtime_error("TuplePart already declared: " + newElement->getName());
    }

    elements[newElement->getName()] = std::move(newElement);
}

void TupleType::removeElement(const std::string& key){
    elements.erase(key);
}

std::string TupleType::toString() const{
    return "Tuple";
}

}
