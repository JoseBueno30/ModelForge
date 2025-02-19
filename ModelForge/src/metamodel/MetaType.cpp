#include <metamodel/MetaType.h>

namespace MetaModel {

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
    if (element) {
        elements.push_back(std::move(element));
    }
}

const std::vector<std::unique_ptr<TuplePart>>& TupleType::getElements() const {
    return elements;
}

void TupleType::addElement(std::unique_ptr<TuplePart> newElement) {
    if (newElement) {
        elements.push_back(std::move(newElement));
    }
}

void TupleType::removeElement(int pos) {
    if (pos >= 0 && pos < static_cast<int>(elements.size())) {
        elements.erase(elements.begin() + pos);
    }
}

}
