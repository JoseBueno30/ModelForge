#ifndef METAENUM_H
#define METAENUM_H

#include "MetaType.h"

#include<string>
#include<vector>
#include<memory>

namespace MetaModel {

class MetaEnumElement{
private:
    std::string name;

public:
    MetaEnumElement(std::string name);

    std::string getName() const;
    void setName(std::string name);
};

class MetaEnum : SimpleType{
private:
    std::string name;
    std::vector<std::unique_ptr<MetaEnumElement>> elements;
public:
    MetaEnum(std::unique_ptr<MetaEnumElement> element);

    std::string getName() const;
    void setName(std::string name);

    std::vector<std::unique_ptr<MetaEnumElement>> getElements() const;
    void addElement(std::unique_ptr<MetaEnumElement>);
};

}

#endif // METAENUM_H
