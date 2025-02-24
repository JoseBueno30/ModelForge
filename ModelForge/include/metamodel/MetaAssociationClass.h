#ifndef METAASSOCIATIONCLASS_H
#define METAASSOCIATIONCLASS_H

#include "MetaAssociation.h"
#include "MetaClass.h"

namespace MetaModel{

class MetaAssociationClass : public MetaAssociation, public MetaClass{
public:
    MetaAssociationClass(const std::string& name, bool isAbstract, int type);

    MetaAssociationClass(const std::string& name, bool isAbstract, int type, std::map<std::string, std::shared_ptr<MetaAssociationEnd>> associationEnds);

    std::string getName() const;
    void setName(const std::string& name);
};

}

#endif // METAASSOCIATIONCLASS_H
