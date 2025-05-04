#ifndef METAENUM_H
#define METAENUM_H

#include "MetaElement.h"
#include "MetaType.h"

#include<string>
#include<map>
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

class MetaEnum : public SimpleType, public MetaElement{
private:
    std::string name;
    std::map<std::string, std::shared_ptr<MetaEnumElement>> elements;
public:
    MetaEnum(const std::string& name, std::shared_ptr<MetaEnumElement> element=nullptr);

    std::string getName() const;
    void setName(const std::string& name);

    const std::map<std::string, std::shared_ptr<MetaEnumElement>>& getElements() const;
    std::shared_ptr<MetaEnumElement> getElement(const std::string& key);
    void addElement(std::shared_ptr<MetaEnumElement> element);
    void removeElement(const std::string& key);

    virtual bool equals(const MetaType& type) const override;

    std::string toString() const override;

    void accept(ModelToText::VisitorInterface& visitor) const override;
};

}

#endif // METAENUM_H
