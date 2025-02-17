#ifndef METATYPE_H
#define METATYPE_H

#include <string>
#include <memory>
#include <vector>

namespace MetaModel{

class MetaType{};

// Simple Types
class SimpleType : MetaType{};

class Real : SimpleType{};
class Integer : SimpleType{};
class String : SimpleType{};
class Boolean : SimpleType{};



// Collection Type
class CollectionType : MetaType{
private:
    bool isOrdered;
    bool isUnique;
    int multiplicity;
    std::shared_ptr<MetaType> type;

public:
    CollectionType(bool ordered, bool unique, int multiplicity, std::shared_ptr<MetaType> type);

    bool getIsOrdered() const;
    void setIsOrdered(bool isOrdered);

    bool getIsUnique() const;
    void setIsUnique(bool isUnique);

    int getMultiplicity() const;
    void setMultiplicity(int multiplicity);

    std::shared_ptr<MetaType> getType() const;
    void setType(const std::shared_ptr<MetaType> &type);
};

// Tuple Type
class TuplePart{
private:
    std::string name;
    std::shared_ptr<MetaType> type;

public:
    TuplePart(std::string name, std::shared_ptr<MetaType> type);

    std::string getName() const;
    void setName(std::string name);

    std::shared_ptr<MetaType> getType() const;
    void setType(const std::shared_ptr<MetaType> &type);
};

class TupleType : MetaType{
private:
    std::vector<std::unique_ptr<TuplePart>> elements;

public:
    TupleType(std::unique_ptr<TuplePart> element);

    std::vector<std::unique_ptr<TuplePart> > getElements() const;
    void addElement(const std::unique_ptr<TuplePart> &newElement);
};

}
#endif // METATYPE_H
