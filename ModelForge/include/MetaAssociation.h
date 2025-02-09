#ifndef METAASSOCIATION_H
#define METAASSOCIATION_H

#include <QList>
#include <string>
namespace USE{
class MetaMultiplicityRange{
private:
    int lowerBound;
    int upperBound;
};
class MetaMultiplicity{
private:
    QList<MetaMultiplicityRange> ranges;
};

class MetaAssociationEnd{
private:
    std::string role;
    int type;
    bool isNavigable;
    bool isOrdered;
    bool isUnique;
    bool isUnion;
    QList<MetaAssociationEnd> redefines;
    QList<MetaAssociationEnd> subsets;
    MetaMultiplicity* multiplicity;
};

class MetaAssociation{
private:
    std::string name;
    int type;
    QList<MetaAssociationEnd> associationEnds;
};
}

#endif // METAASSOCIATION_H
