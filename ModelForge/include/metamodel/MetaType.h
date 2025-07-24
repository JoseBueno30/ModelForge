#ifndef METATYPE_H
#define METATYPE_H

#include "MetaElement.h"

#include <string>
#include <memory>
#include <map>

namespace MetaModel{

class MetaType : public virtual MetaElement{
public:
    virtual std::string toString() const;
    virtual bool equals(const MetaType& type) const = 0;
    virtual ~MetaType(){};
};

// Simple Types
class SimpleType : public MetaType{
public:
    virtual std::string toString() const override;
    virtual ~SimpleType(){};

    virtual bool equals(const MetaType& type) const override {return false;};

    std::any accept(ModelToText::VisitorInterface& visitor) const override;
};

class Real : public SimpleType{
private:
    Real(){};
public:
    virtual bool equals(const MetaType& type) const override;
    std::string toString() const override;
    static std::shared_ptr<Real> instance(){
        static std::shared_ptr<Real> inst(new Real());
        return inst;
    }
};
class Integer : public SimpleType{
private:
    Integer(){};
public:
    virtual bool equals(const MetaType& type) const override;
    std::string toString() const override;
    static std::shared_ptr<Integer> instance(){
        static std::shared_ptr<Integer> inst(new Integer());
        return inst;
    }
};
class String : public SimpleType{
private:
    String(){};
public:
    virtual bool equals(const MetaType& type) const override;
    std::string toString() const override;
    static std::shared_ptr<String> instance(){
        static std::shared_ptr<String> inst(new String());
        return inst;
    }
};
class Boolean : public SimpleType{
private:
    Boolean(){};
public:
    virtual bool equals(const MetaType& type) const override;
    std::string toString() const override;
    static std::shared_ptr<Boolean> instance(){
        static std::shared_ptr<Boolean> inst(new Boolean());
        return inst;
    }
};
class Void: public SimpleType{
private:
    Void(){};
public:
    virtual bool equals(const MetaType& type) const override;
    std::string toString() const override;
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

    virtual bool equals(const MetaType& type) const override;
    std::string toString() const override;

    std::any accept(ModelToText::VisitorInterface& visitor) const override;
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
    const std::shared_ptr<MetaType>& getTypePtr() const;
    void setType(const std::shared_ptr<MetaType>& type);
};

class TupleType : public MetaType{
private:
    std::map<std::string, std::shared_ptr<TuplePart>> elements;

public:
    TupleType(const std::shared_ptr<TuplePart>& element);

    const std::map<std::string, std::shared_ptr<TuplePart>>& getElements() const;
    const TuplePart* getElement(const std::string& key) const;
    void addElement(const std::shared_ptr<TuplePart>& newElement);
    void removeElement(const std::string& key);

    std::string toString() const override;
    virtual bool equals(const MetaType& type) const override;

    std::any accept(ModelToText::VisitorInterface& visitor) const override;
};

}
#endif // METATYPE_H
