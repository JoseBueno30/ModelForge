#ifndef METATYPE_H
#define METATYPE_H

#include <QList>
#include <string>

namespace USE{
class MetaType{};

// Simple Types
class SimpleType : MetaType{};

class Real : SimpleType{};
class Integer : SimpleType{};
class String : SimpleType{};
class Boolean : SimpleType{};

class MetaEnumElement{
private:
    std::string name;
};
class MetaEnum : SimpleType{
private:
    std::string name;
};

// Collection Type
class CollectionType : MetaType{
private:
    bool isOrdered;
    bool isUnique;
    int multiplicity;
    USE::MetaType* type;
};

// Tuple Type
class TuplePart{
private:
    MetaType* type;
    std::string name;
};

class TupleType : MetaType{
private:
    QList<TuplePart> elements;
};
}
#endif // METATYPE_H
