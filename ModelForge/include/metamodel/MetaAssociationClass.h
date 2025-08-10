#ifndef METAASSOCIATIONCLASS_H
#define METAASSOCIATIONCLASS_H

#include "MetaAssociation.h"
#include "MetaClass.h"

namespace MetaModel{

class MetaAssociationClass : public MetaAssociation, public MetaClass{
private:

public:
    MetaAssociationClass(const std::string& name, bool isAbstract, int type);

    MetaAssociationClass(const std::string& name, bool isAbstract, int type, std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds);

    std::string getName() const;
    void setName(const std::string& name);

    void addSuperClass(std::shared_ptr<MetaClass> metaClass) override;

    void addAssociationEnd(std::shared_ptr<MetaAssociationEnd> associationEnd) override;
    void removeAssociationEnd(const std::string& key) override;

    std::any accept(ModelToText::VisitorInterface& visitor) const override;
};

}

#endif // METAASSOCIATIONCLASS_H
