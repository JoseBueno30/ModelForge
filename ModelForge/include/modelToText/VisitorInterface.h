#ifndef VISITORINTERFACE_H
#define VISITORINTERFACE_H

#include <metamodel/MetaModel.h>

namespace ModelToText {

class VisitorInterface{
private:


public:
    virtual void visit(MetaModel::MetaModel metaModel) = 0;

    virtual void visit(MetaModel::MetaEnum metaEnum) = 0;

    virtual void visit(MetaModel::MetaClass metaClass) = 0;

    virtual void visit(MetaModel::MetaAssociation metaAssociation) = 0;

    virtual void visit(MetaModel::MetaAssociationClass metaAssociationClass) = 0;
};

}

#endif // VISITORINTERFACE_H
