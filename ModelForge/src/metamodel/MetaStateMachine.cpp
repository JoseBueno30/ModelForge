#include <metamodel/MetaStateMachine.h>


namespace MetaModel{


MetaStateMachine::MetaStateMachine(const std::string& name, const std::string& stateMachineDefinition)
    : name(name), stateMachineDefinition(stateMachineDefinition){}


std::string MetaStateMachine::getName() const{
    return name;
}

void MetaStateMachine::setName(const std::string& name){
    this->name= name;
}

std::string MetaStateMachine::getStateMachineDefinition() const{
    return stateMachineDefinition;
}

void MetaStateMachine::setStateMachineDefinition(const std::string& stateMachineDefinition){
    this->stateMachineDefinition = stateMachineDefinition;
}

std::string MetaStateMachine::toString() const{
    return this->getStateMachineDefinition();
}

}
