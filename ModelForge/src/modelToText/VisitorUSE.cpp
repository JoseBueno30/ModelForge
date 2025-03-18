#include <iostream>
#include <modelToText/VisitorUSE.h>
#include <stdexcept>

namespace ModelToText {

VisitorUSE::VisitorUSE(const std::string& filename) {
    outFile.open(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }
}

VisitorUSE::~VisitorUSE() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

void VisitorUSE::visit(MetaModel::MetaModel metaModel){
    outFile << "model " << metaModel.getName() <<"\n\n";

    for(const auto &metaEnumPair : metaModel.getEnums()){
        metaEnumPair.second->accept(*this);
    }

    metaClasses = &metaModel.getClasses();

    for(const auto &metaClassPair : metaModel.getClasses()){
        metaClassPair.second->accept(*this);
    }

    for(const auto &metaAssociationPair : metaModel.getAssociations()){
        metaAssociationPair.second->accept(*this);
    }

    for(const auto &metaAssociationClassPair : metaModel.getAssociationClasses()){
        metaAssociationClassPair.second->accept(*this);
    }

    if(globalConstraints != ""){
        outFile << "constraints\n";
        outFile << globalConstraints;
    }
}

void VisitorUSE::visit(MetaModel::MetaEnum metaEnum){
    outFile << "enum " << metaEnum.getName() << " {";

    auto metaEnumElements = metaEnum.getElements();
    auto elementsIterator = metaEnumElements.begin();

    outFile << elementsIterator->second->getName();

    elementsIterator++;

    for(; elementsIterator != metaEnumElements.end(); elementsIterator++){
        outFile << ", " << elementsIterator->second->getName();
    }

    outFile <<"}" << "\n\n";

}

void VisitorUSE::visit(MetaModel::MetaClass metaClass){
    //If class has already been visited, do nothing
    if(visitedClasses.find(metaClass.getName()) != visitedClasses.end()){
        return;
    }

    std::string metaClassString = "";

    if(metaClass.getIsAbstract()){
        metaClassString += "abstract ";
    }

    metaClassString += "class " + metaClass.getName();

    //Generalization
    auto superClasses = metaClass.getSuperClasses();

    if(superClasses.size() > 0){


        auto superClassesIterator = superClasses.begin();
        auto& superClass = superClassesIterator->second;

        if(visitedClasses.find(superClass->getName()) == visitedClasses.end()){
            superClass->accept(*this);
        }

        metaClassString += " < " + superClass->getName();

        superClassesIterator++;

        for(; superClassesIterator != superClasses.end(); superClassesIterator++){
            superClass = superClassesIterator->second;
            if(visitedClasses.find(superClass->getName()) == visitedClasses.end()){
                superClass->accept(*this);
            }

            metaClassString += ", " + superClass->getName();
        }

    }

    metaClassString += "\n";

    //Attributes
    auto attributes = metaClass.getAttributes();

    if(attributes.size() > 0){
        metaClassString += "attributes\n";

        for(const auto &attributePair : attributes){
            auto attribute = attributePair.second;
            metaClassString += attribute->toString() + "\n";
        }
    }

    //Operations
    auto operations = metaClass.getOperations();

    if(operations.size() > 0){
        metaClassString += "operations\n";

        for(const auto &operationPair : operations){
            auto operation = operationPair.second;
            metaClassString += operation->toString();
            metaClassString += " " + operation->getOperationDefinition() + "\n";

            for(const auto &preConditionPair : operation->getPreConditions()){
                auto preCondition = preConditionPair.second;
                metaClassString += "pre " + preCondition->getName() + ": " + preCondition->getExpression().getExpression();
            }

            for(const auto &postConditionPair : operation->getPostConditions()){
                auto postCondition = postConditionPair.second;
                metaClassString += "post " + postCondition->getName() + ": " + postCondition->getExpression().getExpression();
            }
        }
    }

    //Constraints
    auto constraints = metaClass.getConstraints();

    if(constraints.size() > 0){
        metaClassString += "constraints\n";

        for(const auto &constraintPair : constraints){
            auto constraint = constraintPair.second;

            if(constraint->getVariables().size() > 1){
                globalConstraints += "context ";

                auto variablesIterator = constraint->getVariables().begin();
                auto variable = variablesIterator->second;

                globalConstraints += variable->getName();

                variablesIterator++;

                for(; variablesIterator != constraint->getVariables().end(); variablesIterator++){
                    variable = variablesIterator->second;

                    globalConstraints += ", " + variable->getName();
                }


                globalConstraints += ": " + constraint->getClass().getName() + " inv " + constraint->getName() + ":\n\t" + constraint->getExpression().getExpression() + "\n\n";
            }else{
                if(constraint->getIsExistential()){
                    metaClassString += "existential inv " + constraint->getName() + ":\n\t" + constraint->getExpression().getExpression() + "\n";
                }else{
                    metaClassString += "inv " + constraint->getName() + ":\n\t" + constraint->getExpression().getExpression() + "\n";
                }
            }
        }
    }

    //StateMachines
    auto stateMachines = metaClass.getStateMachines();

    if(stateMachines.size() > 0){
        metaClassString += "statemachines\n";

        for(const auto &stateMachinePair : stateMachines){
            auto stateMachine = stateMachinePair.second;
            metaClassString += stateMachine->getStateMachineDefinition() + "\n";
        }
    }

    visitedClasses.insert(metaClass.getName());

    metaClassString += "end\n\n";

    outFile << metaClassString;

}

void VisitorUSE::visit(MetaModel::MetaAssociation metaAssociation){
    std::string metaAssociationString = "";

    if(metaAssociation.getType() == MetaModel::MetaAssociation::AGGREGATION){
        metaAssociationString += "aggregation ";
    }else if(metaAssociation.getType() == MetaModel::MetaAssociation::COMPOSITION){
        metaAssociationString += "composition ";
    }else{
        metaAssociationString += "association ";
    }

    metaAssociationString += metaAssociation.getName() + " between\n";

    for(auto &assocEndPair : metaAssociation.getAssociationEnds()){
        auto assocEnd = assocEndPair.second;

        metaAssociationString += assocEnd->getClass().getName();

        metaAssociationString += " [" + assocEnd->getMultiplicity().toString() + "] ";

        metaAssociationString += "role " + assocEnd->getRole();

        if(assocEnd->getIsOrdered()){
            metaAssociationString += " ordered";
        }

        if(assocEnd->getIsUnion()){
            metaAssociationString += " union";
        }

        for(auto &subsettedEndPair : assocEnd->getSubsettedEnds()){
            auto subsettedEnd = subsettedEndPair.second;

            metaAssociationString += " subsets " + subsettedEnd->getClass().getName();
        }

        for(auto &redefinedEndPair : assocEnd->getRedefinedEnds()){
            auto redefinedEnd = redefinedEndPair.second;

            metaAssociationString += " redefines " + redefinedEnd->getClass().getName();
        }

        //derive Expression and qualifiers ignored for now

        metaAssociationString += "\n";
    }



    metaAssociationString += "end\n\n";

    outFile << metaAssociationString;
}

void VisitorUSE::visit(MetaModel::MetaAssociationClass metaAssociationClass){
    //If association class has already been visited, do nothing
    if(visitedClasses.find(metaAssociationClass.getName()) != visitedClasses.end()){
        return;
    }

    std::string metaAssociationClassString = "";

    if(metaAssociationClass.getIsAbstract()){
        metaAssociationClassString += "abstract ";
    }

    metaAssociationClassString += "associationclass " + metaAssociationClass.getName();

    //Generalization
    auto superAssociationClasses = metaAssociationClass.getSuperClasses();

    if(superAssociationClasses.size() > 0){


        auto superAssociationClassesIterator = superAssociationClasses.begin();
        auto& superAssociationClass = superAssociationClassesIterator->second;

        if(visitedClasses.find(superAssociationClass->getName()) == visitedClasses.end()){
            superAssociationClass->accept(*this);
        }

        metaAssociationClassString += " < " + superAssociationClass->getName();

        superAssociationClassesIterator++;

        for(; superAssociationClassesIterator != superAssociationClasses.end(); superAssociationClassesIterator++){
            superAssociationClass = superAssociationClassesIterator->second;
            if(visitedClasses.find(superAssociationClass->getName()) == visitedClasses.end()){
                superAssociationClass->accept(*this);
            }

            metaAssociationClassString += ", " + superAssociationClass->getName();
        }

    }

    //AssociationEnds
    metaAssociationClassString += " between\n";

    for(auto &assocEndPair : metaAssociationClass.MetaAssociation::getAssociationEnds()){
        auto assocEnd = assocEndPair.second;

        metaAssociationClassString += assocEnd->getClass().getName();

        metaAssociationClassString += " [" + assocEnd->getMultiplicity().toString() + "] ";

        metaAssociationClassString += "role " + assocEnd->getRole();

        if(assocEnd->getIsOrdered()){
            metaAssociationClassString += " ordered";
        }

        if(assocEnd->getIsUnion()){
            metaAssociationClassString += " union";
        }

        for(auto &subsettedEndPair : assocEnd->getSubsettedEnds()){
            auto subsettedEnd = subsettedEndPair.second;

            metaAssociationClassString += " subsets " + subsettedEnd->getClass().getName();
        }

        for(auto &redefinedEndPair : assocEnd->getRedefinedEnds()){
            auto redefinedEnd = redefinedEndPair.second;

            metaAssociationClassString += " redefines " + redefinedEnd->getClass().getName();
        }

        //derive Expression and qualifiers ignored for now

        metaAssociationClassString += "\n";
    }



    //Attributes
    auto attributes = metaAssociationClass.getAttributes();

    if(attributes.size() > 0){
        metaAssociationClassString += "attributes\n";

        for(const auto &attributePair : attributes){
            auto attribute = attributePair.second;
            metaAssociationClassString += attribute->toString() + "\n";
        }
    }

    //Operations
    auto operations = metaAssociationClass.getOperations();

    if(operations.size() > 0){
        metaAssociationClassString += "operations\n";

        for(const auto &operationPair : operations){
            auto operation = operationPair.second;
            metaAssociationClassString += operation->toString();
            metaAssociationClassString += " " + operation->getOperationDefinition() + "\n";

            for(const auto &preConditionPair : operation->getPreConditions()){
                auto preCondition = preConditionPair.second;
                metaAssociationClassString += "pre " + preCondition->getName() + ": " + preCondition->getExpression().getExpression();
            }

            for(const auto &postConditionPair : operation->getPostConditions()){
                auto postCondition = postConditionPair.second;
                metaAssociationClassString += "post " + postCondition->getName() + ": " + postCondition->getExpression().getExpression();
            }
        }
    }

    //Constraints
    auto constraints = metaAssociationClass.getConstraints();

    if(constraints.size() > 0){
        metaAssociationClassString += "constraints\n";

        for(const auto &constraintPair : constraints){
            auto constraint = constraintPair.second;

            if(constraint->getVariables().size() > 1){
                globalConstraints += "context ";

                auto variablesIterator = constraint->getVariables().begin();
                auto variable = variablesIterator->second;

                globalConstraints += variable->getName();

                variablesIterator++;

                for(; variablesIterator != constraint->getVariables().end(); variablesIterator++){
                    variable = variablesIterator->second;

                    globalConstraints += ", " + variable->getName();
                }


                globalConstraints += ": " + constraint->getClass().getName() + " inv " + constraint->getName() + ":\n\t" + constraint->getExpression().getExpression() + "\n\n";
            }else{
                if(constraint->getIsExistential()){
                    metaAssociationClassString += "existential inv " + constraint->getName() + ":\n\t" + constraint->getExpression().getExpression() + "\n";
                }else{
                    metaAssociationClassString += "inv " + constraint->getName() + ":\n\t" + constraint->getExpression().getExpression() + "\n";
                }
            }
        }
    }

    //StateMachines
    auto stateMachines = metaAssociationClass.getStateMachines();

    if(stateMachines.size() > 0){
        metaAssociationClassString += "statemachines\n";

        for(const auto &stateMachinePair : stateMachines){
            auto stateMachine = stateMachinePair.second;
            metaAssociationClassString += stateMachine->getStateMachineDefinition() + "\n";
        }
    }

    //Association type
    if(metaAssociationClass.getType() == MetaModel::MetaAssociation::AGGREGATION){
        metaAssociationClassString += "aggregation\n";
    }else if(metaAssociationClass.getType() == MetaModel::MetaAssociation::COMPOSITION){
        metaAssociationClassString += "composition\n";
    }

    visitedClasses.insert(metaAssociationClass.getName());

    metaAssociationClassString += "end\n\n";

    outFile << metaAssociationClassString;
}

void VisitorUSE::save() {
    if (outFile.is_open()) {
        outFile.flush();
    }
}

}
