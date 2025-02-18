#ifndef METAASSOCIATION_H
#define METAASSOCIATION_H

#include "MetaAssociationEnd.h"

#include <string>

namespace MetaModel{

class MetaAssociation{
private:
    std::string name;
    int type;
    std::vector<std::unique_ptr<MetaAssociationEnd>> associationEnds;

public:
    static const int ASSOCIATION = 0;
    static const int AGGREGATION = 1;
    static const int COMPOSITION = 2;

    MetaAssociation(const std::string& name, int type);

    MetaAssociation(const std::string& name, int type, std::vector<std::unique_ptr<MetaAssociationEnd>> associationEnds);

    std::string getName() const;
    void setName(const std::string& name);

    int getType() const;
    void setType(int type);

    std::vector<std::unique_ptr<MetaAssociationEnd>>& getAssociationEnds() const;
    void addAssociationEnd(std::unique_ptr<MetaAssociationEnd> associationEnd);
    void removeAssociationEnd(int pos);
};
}

#endif // METAASSOCIATION_H
