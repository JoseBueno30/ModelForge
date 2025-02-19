#ifndef METATYPE_H
#define METATYPE_H

#include <string>
#include <memory>
#include <vector>

namespace MetaModel{

class MetaType{};

// Simple Types
class SimpleType : public MetaType{};

class Real : public SimpleType{
private:
    Real();
public:
    static std::shared_ptr<Real> instance(){
        static std::shared_ptr<Real> inst(new Real());
        return inst;
    }
};
class Integer : public SimpleType{
private:
    Integer();
public:
    static std::shared_ptr<Integer> instance(){
        static std::shared_ptr<Integer> inst(new Integer());
        return inst;
    }
};
class String : public SimpleType{
private:
    String();
public:
    static std::shared_ptr<String> instance(){
        static std::shared_ptr<String> inst(new String());
        return inst;
    }
};
class Boolean : public SimpleType{
private:
    Boolean();
public:
    static std::shared_ptr<Boolean> instance(){
        static std::shared_ptr<Boolean> inst(new Boolean());
        return inst;
    }
};
class Void: public SimpleType{
private:
    Void();
public:
    static std::shared_ptr<Void> instance(){
        static std::shared_ptr<Void> inst(new Void());
        return inst;
    }
};



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

    const MetaType& getType() const;
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

    const MetaType& getType() const;
    void setType(const std::shared_ptr<MetaType>& type);
};

class TupleType : public MetaType{
private:
    std::vector<std::unique_ptr<TuplePart>> elements;

public:
    TupleType(std::unique_ptr<TuplePart> element);

    const std::vector<std::unique_ptr<TuplePart>>& getElements() const;
    void addElement(std::unique_ptr<TuplePart> newElement);
    void removeElement(int pos);
};

}
#endif // METATYPE_H
