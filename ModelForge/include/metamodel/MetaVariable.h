#ifndef METAVARIABLE_H
#define METAVARIABLE_H

#include "MetaType.h"

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

    const MetaType& getType() const;
    const std::shared_ptr<MetaType>& getTypePtr() const;
    void setType(const std::shared_ptr<MetaType>& type);

    std::string toString() const;
};

}

#endif // METAVARIABLE_H
