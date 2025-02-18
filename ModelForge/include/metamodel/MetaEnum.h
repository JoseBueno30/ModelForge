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
    MetaEnumElement(const std::string& name);

    std::string getName() const;
    void setName(const std::string& name);
};

class MetaEnum : public SimpleType{
private:
    std::string name;
    std::vector<std::unique_ptr<MetaEnumElement>> elements;
public:
    MetaEnum(const std::string& name, std::unique_ptr<MetaEnumElement> element);

    std::string getName() const;
    void setName(const std::string& name);

    std::vector<std::unique_ptr<MetaEnumElement>>& getElements() const;
    void addElement(std::unique_ptr<MetaEnumElement> element);
    void removeElement(int pos);
};

}

#endif // METAENUM_H
