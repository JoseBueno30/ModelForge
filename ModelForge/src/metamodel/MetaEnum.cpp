#include <metamodel/MetaEnum.h>

#include <stdexcept>

namespace MetaModel {


MetaEnumElement::MetaEnumElement(const std::string& name)
    : name(name){}

std::string MetaEnumElement::getName() const{
    return name;
}

void MetaEnumElement::setName(const std::string& name){
    this->name = name;
}



MetaEnum::MetaEnum(const std::string& name, std::unique_ptr<MetaEnumElement> element)
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

const std::map<std::string, std::unique_ptr<MetaEnumElement>>& MetaEnum::getElements() const{
    return elements;
}

const MetaEnumElement* MetaEnum::getElement(const std::string& key) const{
    auto iterator = elements.find(key);
    if(iterator != elements.end()){
        return (iterator->second).get();
    }
    return nullptr;
}

void MetaEnum::addElement(const std::string& key, std::unique_ptr<MetaEnumElement> element){
    if (!element) {
        throw std::invalid_argument("Null enum");
    }

    if (elements.find(key) != elements.end()) {
        throw std::runtime_error("Enum: " + name + " already contains element named: " + key);
    }

    elements[key] = std::move(element);
}

void MetaEnum::removeElement(const std::string& key){
    elements.erase(key);
}

}
