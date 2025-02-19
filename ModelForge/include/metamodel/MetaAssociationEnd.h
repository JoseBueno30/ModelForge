#ifndef METAASSOCIATIONEND_H
#define METAASSOCIATIONEND_H



#include "MetaVariable.h"
#include "MetaClass.h"

#include <memory>
#include <string>
#include <vector>
namespace MetaModel{

class MetaMultiplicityRange{
private:
    int lowerBound;
    int upperBound;

public:
    static const int MANY = -1;

    MetaMultiplicityRange(int lowerBound, int upperBound);

    int getLowerBound() const;
    void setLowerBound(int lowerBound);

    int getUpperBound() const;
    void setUpperBound(int upperBound);
};
class MetaMultiplicity{
private:
    std::vector<std::unique_ptr<MetaMultiplicityRange>> ranges;

public:
    MetaMultiplicity(int lowerBound, int upperBound);

    const std::vector<std::unique_ptr<MetaMultiplicityRange>> getRanges() const;
    void addRange(int lowerBound, int upperBound);
    void deleteRange(int pos);

};

class MetaAssociationEnd{
private:
    std::shared_ptr<MetaClass> endClass;
    std::string role;
    int type;
    bool isNavigable;
    bool isOrdered;
    bool isUnique;
    bool isUnion;
    std::shared_ptr<MetaMultiplicity> multiplicity;
    std::vector<std::shared_ptr<MetaAssociationEnd>> redefinedEnds;
    std::vector<std::shared_ptr<MetaAssociationEnd>> subsettedEnds;
    std::vector<std::unique_ptr<MetaVariable>> qualifiers;
    std::unique_ptr<OCLExpr> deriveExpr;

public:
    MetaAssociationEnd(const std::shared_ptr<MetaClass>& endClass, const std::string& role, int type, bool isNavigable, bool isOrdered, bool isUnique, bool isUnion, const std::shared_ptr<MetaMultiplicity>& multiplicity);

    const MetaClass& getClass() const;
    void setClass(const std::shared_ptr<MetaClass>& endClass);

    std::string getRole() const;
    void setRole(const std::string& role);

    int getType() const;
    void setType(int type);

    bool getIsNavigable() const;
    void setIsNavigable(bool isNavigable);

    bool getIsOrdered() const;
    void setIsOrdered(bool isOrdered);

    bool getIsUnique() const;
    void setIsUnique(bool isUnique);

    bool getIsUnion() const;
    void setIsUnion(bool isUnion);

    const MetaMultiplicity& getMultiplicity() const;
    void setMultiplicity(const std::shared_ptr<MetaMultiplicity>& multiplicity);

    const std::vector<std::shared_ptr<MetaAssociationEnd>>& getRedefinedEnds() const;
    void addRedefinedEnd(const std::shared_ptr<MetaAssociationEnd>& redefinedEnd);
    void removeRedefinedEnd(int pos);

    const std::vector<std::shared_ptr<MetaAssociationEnd>>& getSubsettedEnds() const;
    void addSubsettedEnd(const std::shared_ptr<MetaAssociationEnd>& subsettedEnd);
    void removeSubsettedEnd(int pos);

    const std::vector<std::unique_ptr<MetaVariable>>& getQualifiers() const;
    void addQualifier(std::unique_ptr<MetaVariable> qualifier);
    void removeQualifier(int pos);

    const OCLExpr* getDeriveExpr() const;
    void setDeriveExpr(std::unique_ptr<OCLExpr> deriveExpr);
};

}

#endif // METAASSOCIATIONEND_H
