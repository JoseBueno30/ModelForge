#ifndef METAASSOCIATION_H
#define METAASSOCIATION_H

#include "MetaAssociationEnd.h"
#include "MetaElement.h"

#include <string>

namespace MetaModel{

class MetaAssociation : public MetaElement{
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

    ~MetaAssociation();

    std::string getName() const;
    void setName(const std::string& name);

    int getType() const;
    void setType(int type);

    const std::map<std::string, std::shared_ptr<MetaAssociationEnd>>& getAssociationEnds() const;
    std::shared_ptr<MetaAssociationEnd> getAssociationEnd(const std::string& key);
    void addAssociationEnd(std::shared_ptr<MetaAssociationEnd> associationEnd);
    void removeAssociationEnd(const std::string& key);

    std::vector<std::string> getAssociationEndsClassesNames();

    std::any accept(ModelToText::VisitorInterface& visitor) const override;
};
}

#endif // METAASSOCIATION_H
