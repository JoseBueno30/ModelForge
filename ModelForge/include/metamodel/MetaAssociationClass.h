#ifndef METAASSOCIATIONCLASS_H
#define METAASSOCIATIONCLASS_H

#include "MetaAssociation.h"
#include "MetaClass.h"

namespace MetaModel{

class MetaAssociationClass : public MetaAssociation, public MetaClass{
public:
    MetaAssociationClass(const std::string& name, bool isAbstract, int type);

    MetaAssociationClass(const std::string& name, bool isAbstract, int type, std::vector<std::unique_ptr<MetaAssociationEnd>> associationEnds);
};

}

#endif // METAASSOCIATIONCLASS_H
