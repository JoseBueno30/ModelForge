#ifndef METATYPE_H
#define METATYPE_H

#include <string>
#include <memory>
#include <vector>

namespace MetaModel{

class MetaType{};

// Simple Types
class SimpleType : public MetaType{};

class Real : public SimpleType{};
class Integer : public SimpleType{};
class String : public SimpleType{};
class Boolean : public SimpleType{};
class Void: public SimpleType{};



// Collection Type
class CollectionType : public MetaType{
private:
    bool isOrdered;
    bool isUnique;
    int multiplicity;
    std::shared_ptr<MetaType> type;

public:
    CollectionType(bool ordered, bool unique, int multiplicity, const std::shared_ptr<MetaType>& type);

    bool getIsOrdered() const;
    void setIsOrdered(bool isOrdered);

    bool getIsUnique() const;
    void setIsUnique(bool isUnique);

    int getMultiplicity() const;
    void setMultiplicity(int multiplicity);

    std::shared_ptr<MetaType> getType() const;
    void setType(const std::shared_ptr<MetaType>& type);
};

// Tuple Type
class TuplePart{
private:
    std::string name;
    std::shared_ptr<MetaType> type;

public:
    TuplePart(const std::string& name, const std::shared_ptr<MetaType>& type);

    std::string getName() const;
    void setName(const std::string& name);

    std::shared_ptr<MetaType> getType() const;
    void setType(const std::shared_ptr<MetaType>& type);
};

class TupleType : public MetaType{
private:
    std::vector<std::unique_ptr<TuplePart>> elements;

public:
    TupleType(std::unique_ptr<TuplePart> element);

    std::vector<std::unique_ptr<TuplePart>>& getElements() const;
    void addElement(std::unique_ptr<TuplePart> newElement);
    void removeElement(int pos);
};

}
#endif // METATYPE_H
