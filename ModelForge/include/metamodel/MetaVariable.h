#ifndef METAVARIABLE_H
#define METAVARIABLE_H

#include "MetaType.h"
#include "OCLExpression.h"

#include<string>

namespace MetaModel{

class MetaVariable{
private:
    std::string name;
    std::shared_ptr<MetaType> type;

public:
    MetaVariable(const std::string& name, const std::shared_ptr<MetaType>& type);

    std::string getName() const;
    void setName(const std::string& name);

    std::shared_ptr<MetaType> getType() const;
    void setType(const std::shared_ptr<MetaType>& type);
};

}

#endif // METAVARIABLE_H
