#include <metamodel/MetaEnum.h>

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
        elements.push_back(std::move(element));
    }
}

std::string MetaEnum::getName() const{
    return name;
}
void MetaEnum::setName(const std::string& name){
    this->name = name;
}


const std::vector<std::unique_ptr<MetaEnumElement>>& MetaEnum::getElements() const{
    return elements;
}

void MetaEnum::addElement(std::unique_ptr<MetaEnumElement> element){
    if(element){
        elements.push_back(std::move(element));
    }
}

void MetaEnum::removeElement(int pos){
    if(pos>=0 && pos <  static_cast<int>(elements.size())){
        elements.erase(elements.begin() + pos);

        if(elements.size() < elements.capacity()/2){
            elements.shrink_to_fit();
        }
    }
}

}
