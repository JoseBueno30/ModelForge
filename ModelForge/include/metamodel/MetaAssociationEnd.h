#ifndef METAASSOCIATIONEND_H
#define METAASSOCIATIONEND_H


#include "MetaVariable.h"
#include "OCL/OCLExpr.h"

#include <memory>
#include <string>
#include <vector>

namespace MetaModel {
class MetaAssociation;  // Forward declaration
}

namespace MetaModel{
class MetaClass;

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

    std::string toString() const;
};

class MetaMultiplicity{
private:
    std::vector<std::shared_ptr<MetaMultiplicityRange>> ranges;

public:
    MetaMultiplicity(int lowerBound, int upperBound);

    const std::vector<std::shared_ptr<MetaMultiplicityRange>>& getRanges() const;
    void addRange(int lowerBound, int upperBound);
    void deleteRange(int pos);

    void setMultiplicictyFromString(std::string multiplicityString);

    std::string toString() const;
};

class MetaAssociationEnd{
private:
    std::shared_ptr<MetaClass> endClass;
    std::shared_ptr<MetaAssociation> association;
    std::string role;
    int type;
    bool isNavigable;
    bool isOrdered;
    bool isUnique;
    bool isUnion;
    std::shared_ptr<MetaMultiplicity> multiplicity;
    std::map<std::string, std::shared_ptr<MetaAssociationEnd>> redefinedEnds;
    std::map<std::string, std::shared_ptr<MetaAssociationEnd>> subsettedEnds;
    std::map<std::string, std::shared_ptr<MetaVariable>> qualifiers;
    std::shared_ptr<Expr> deriveExpr;

public:
    MetaAssociationEnd(const std::shared_ptr<MetaAssociation>& association, int type);
    MetaAssociationEnd(const std::shared_ptr<MetaClass>& endClass, const std::shared_ptr<MetaAssociation>& association, const std::string& role, int type, bool isNavigable, bool isOrdered, bool isUnique, bool isUnion, const std::shared_ptr<MetaMultiplicity>& multiplicity);

    const MetaClass& getClass() const;
    std::shared_ptr<MetaClass> getClassSharedPtr() const;
    void setClass(const std::shared_ptr<MetaClass>& endClass);

    const MetaAssociation& getAssociation() const;
    std::shared_ptr<MetaAssociation> getAssociationSharedPtr() const;
    void setAssociation(const std::shared_ptr<MetaAssociation>& association);

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

    const std::map<std::string,std::shared_ptr<MetaAssociationEnd>>& getRedefinedEnds() const;
    const MetaAssociationEnd* getRedefinedEnd(const std::string& key) const;
    void addRedefinedEnd(const std::shared_ptr<MetaAssociationEnd>& redefinedEnd);
    void removeRedefinedEnd(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaAssociationEnd>>& getSubsettedEnds() const;
    const MetaAssociationEnd* getSubsettedEnd(const std::string& key) const;
    void addSubsettedEnd(const std::shared_ptr<MetaAssociationEnd>& subsettedEnd);
    void removeSubsettedEnd(const std::string& key);

    const std::map<std::string,std::shared_ptr<MetaVariable>>& getQualifiers() const;
    const MetaVariable* getQualifier(const std::string& key) const;
    void addQualifier(const std::shared_ptr<MetaVariable>& qualifier);
    void removeQualifier(const std::string& key);

    const Expr* getDeriveExpr() const;
    void setDeriveExpr(const std::shared_ptr<Expr>& deriveExpr);
};

}

#endif // METAASSOCIATIONEND_H
