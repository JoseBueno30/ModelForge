#ifndef METAASSOCIATION_H
#define METAASSOCIATION_H

#include "MetaAssociationEnd.h"

#include <string>

namespace MetaModel{

class MetaAssociation{
private:
    std::string name;
    int type;
    std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds;

public:
    static const int ASSOCIATION = 0;
    static const int AGGREGATION = 1;
    static const int COMPOSITION = 2;

    MetaAssociation(const std::string& name, int type);

    MetaAssociation(const std::string& name, int type, std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds);

    std::string getName() const;
    void setName(const std::string& name);

    int getType() const;
    void setType(int type);

    const std::map<std::string, std::shared_ptr<MetaAssociationEnd>>& getAssociationEnds() const;
    std::shared_ptr<MetaAssociationEnd> getAssociationEnd(const std::string& key);
    void addAssociationEnd(std::shared_ptr<MetaAssociationEnd> associationEnd);
    void removeAssociationEnd(const std::string& key);

    std::vector<std::string> getAssociationEndsClassesNames();
};
}

#endif // METAASSOCIATION_H
