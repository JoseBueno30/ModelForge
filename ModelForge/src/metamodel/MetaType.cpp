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

bool Real::equals(const MetaType& type) const{
    const Real* realType = dynamic_cast<const Real*>(&type);
    return realType != nullptr;
}

std::string Integer::toString() const{
    return "Integer";
}

bool Integer::equals(const MetaType& type) const{
    const Integer* integerType = dynamic_cast<const Integer*>(&type);
    return integerType != nullptr;
}

std::string Boolean::toString() const{
    return "Boolean";
}

bool Boolean::equals(const MetaType& type) const{
    const Boolean* boolType = dynamic_cast<const Boolean*>(&type);
    return boolType  != nullptr;
}

std::string String::toString() const{
    return "String";
}

bool String::equals(const MetaType& type) const{
    const String* stringType = dynamic_cast<const String*>(&type);
    return stringType != nullptr;
}

std::string Void::toString() const{
    return "OclVoid";
}

bool Void::equals(const MetaType& type) const{
    const Void* voidType = dynamic_cast<const Void*>(&type);
    return voidType != nullptr;
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
    std::string res = "";

    if(this->isOrdered && this->isUnique){
        res = "SortedSet";
    }else if(!this->isOrdered && this->isUnique){
        res = "Set";
    }else if(this->isOrdered && !this->isUnique){
        res = "Sequence";
    }else if(!this->isOrdered && !this->isUnique){
        res = "Bag";
    }

    return res + "<" + this->getType().toString() + ">";
}

bool CollectionType::equals(const MetaType& type) const{
    const CollectionType* collectionType = dynamic_cast<const CollectionType*>(&type);

    if(collectionType == nullptr){
        return false;
    }

    return (this->isOrdered == collectionType->isOrdered) &&
           (this->isUnique == collectionType->isUnique) &&
           (this->multiplicity == collectionType->multiplicity) &&
           (this->type->equals(collectionType->getType()));
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

const std::shared_ptr<MetaType>& TuplePart::getTypePtr() const {
    return type;
}

void TuplePart::setType(const std::shared_ptr<MetaType>& type) {
    this->type = type;
}

TupleType::TupleType(const std::shared_ptr<TuplePart>& element) {
    if (!element) {
        throw std::invalid_argument("Null TuplePart");
    }

    if (elements.find(element->getName()) != elements.end()) {
        throw std::runtime_error("TuplePart already declared: " + element->getName());
    }

    elements[element->getName()] = element;
}

const std::map<std::string, std::shared_ptr<TuplePart>>& TupleType::getElements() const{
    return elements;
}

const TuplePart* TupleType::getElement(const std::string& key) const{
    auto iterator = elements.find(key);
    if(iterator != elements.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void TupleType::addElement(const std::shared_ptr<TuplePart>& newElement){
    if (!newElement) {
        throw std::invalid_argument("Null TuplePart");
    }

    if (elements.find(newElement->getName()) != elements.end()) {
        throw std::invalid_argument("TuplePart already declared: " + newElement->getName());
    }

    elements[newElement->getName()] = newElement;
}

void TupleType::removeElement(const std::string& key){
    elements.erase(key);
}

std::string TupleType::toString() const{
    return "Tuple";
}

bool TupleType::equals(const MetaType& type) const {
    const TupleType* tupleType = dynamic_cast<const TupleType*>(&type);
    if (!tupleType) {
        return false;
    }

    if (elements.size() != tupleType->elements.size()) {
        return false;
    }

    for (const auto& pair : elements) {
        const std::string& key = pair.first;
        const TuplePart* tuplePart = pair.second.get();

        auto it = tupleType->elements.find(key);

        if (it == tupleType->elements.end()) {
            return false;
        }

        const TuplePart* otherTuplePart = it->second.get();

        if (tuplePart->getName() != otherTuplePart->getName() || !tuplePart->getType().equals(otherTuplePart->getType())) {
            return false;
        }
    }

    return true;
}

}
