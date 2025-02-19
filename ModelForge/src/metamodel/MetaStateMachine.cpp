#include <metamodel/MetaStateMachine.h>


namespace MetaModel{


MetaStateMachine::MetaStateMachine(const std::string& stateMachineDefinition)
    : stateMachineDefinition(stateMachineDefinition){}

std::string MetaStateMachine::getStateMachineDefinition() const{
    return stateMachineDefinition;
}

void MetaStateMachine::setStateMachineDefinition(const std::string& stateMachineDefinition){
    this->stateMachineDefinition = stateMachineDefinition;
}


}
