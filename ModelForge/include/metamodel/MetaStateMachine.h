#ifndef METASTATEMACHINE_H
#define METASTATEMACHINE_H

#include <string>

namespace MetaModel{

class MetaStateMachine{
private:
    std::string stateMachineDefinition;

public:
    MetaStateMachine(std::string stateMachineDefinition);

    std::string getStateMachineDefinition() const;
    void setStateMachineDefinition(const std::string stateMachineDefinition);
};

}

#endif // METASTATEMACHINE_H
