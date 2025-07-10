#include <metamodel/MetaEnum.h>

#include <stdexcept>

#include <modelToText/VisitorInterface.h>

namespace MetaModel {


MetaEnumElement::MetaEnumElement(const std::string& name)
    : name(name){}

std::string MetaEnumElement::getName() const{
    return name;
}

void MetaEnumElement::setName(const std::string& name){
    this->name = name;
}



MetaEnum::MetaEnum(const std::string& name, std::shared_ptr<MetaEnumElement> element)
    : name(name){
    if(element){
        elements[element->getName()] = std::move(element);
    }
}

std::string MetaEnum::getName() const{
    return name;
}
void MetaEnum::setName(const std::string& name){
    this->name = name;
}

const std::map<std::string, std::shared_ptr<MetaEnumElement>>& MetaEnum::getElements() const{
    return elements;
}

std::shared_ptr<MetaEnumElement> MetaEnum::getElement(const std::string& key){
    auto iterator = elements.find(key);
    if(iterator != elements.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MetaEnum::addElement(std::shared_ptr<MetaEnumElement> element){
    if (!element) {
        throw std::invalid_argument("Null EnumElement");
    }

    if (elements.find(element->getName()) != elements.end()) {
        throw std::invalid_argument("Enum: " + name + " already contains element named: " + element->getName());
    }

    elements[element->getName()] = std::move(element);
}

void MetaEnum::removeElement(const std::string& key){
    elements.erase(key);
}

bool MetaEnum::equals(const MetaType& type) const{
    const MetaEnum* metaEnum= dynamic_cast<const MetaEnum*>(&type);

    return metaEnum != nullptr && this->name == metaEnum->getName();
}

std::string MetaEnum::toString() const{
    return this->getName();
}

std::any MetaEnum::accept(ModelToText::VisitorInterface& visitor) const{
    return visitor.visit(*this);
}

}
