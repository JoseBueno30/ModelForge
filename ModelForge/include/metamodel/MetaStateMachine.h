#ifndef METASTATEMACHINE_H
#define METASTATEMACHINE_H

#include <string>

namespace MetaModel{

class MetaStateMachine{
private:
    std::string name;
    std::string stateMachineDefinition;

public:
    MetaStateMachine(const std::string& name, const std::string& stateMachineDefinition);

    std::string getName() const;
    void setName(const std::string& name);

    std::string getStateMachineDefinition() const;
    void setStateMachineDefinition(const std::string& stateMachineDefinition);

    std::string toString() const;
};

}

#endif // METASTATEMACHINE_H
