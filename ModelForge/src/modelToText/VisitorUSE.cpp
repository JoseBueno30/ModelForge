#include <modelToText/VisitorUSE.h>
#include <stdexcept>

namespace ModelToText {

std::string visibilityToString(MetaModel::Visibility vis) {
    switch (vis) {
    case MetaModel::Visibility::Public:    return "--+";
    case MetaModel::Visibility::Private:   return "--—";
    case MetaModel::Visibility::Protected: return "--#";
    case MetaModel::Visibility::Package:   return "--~";
    }
    return "";
}

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

std::any VisitorUSE::visit(MetaModel::MetaModel metaModel){
    outFile << "model " << metaModel.getName() <<"\n\n";

    for(const auto &metaEnumPair : metaModel.getEnums()){
        metaEnumPair.second->accept(*this);
    }

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

    return nullptr;
}

std::any VisitorUSE::visit(MetaModel::MetaAttribute metaAttribute){
    std::string metaAttributeString = "";
    metaAttributeString += metaAttribute.toString() + " " + visibilityToString(metaAttribute.getVisibility()) + "\n";

    if (metaAttribute.getInitExpr()) {
        metaAttributeString += " init = " + metaAttribute.getInitExpr()->toString();
    } else if (metaAttribute.getDeriveExpr()) {
        metaAttributeString += " derive = " + metaAttribute.getDeriveExpr()->toString();
    }

    if(metaAttributeString.back() != '\n'){
        metaAttributeString += "\n";
    }
    return metaAttributeString;
}

std::any VisitorUSE::visit(MetaModel::MetaOperation metaOperation){
    std::string metaOperationString = "";
    metaOperationString += metaOperation.toString() + " " + visibilityToString(metaOperation.getVisibility()) + "\n\t";

    metaOperationString += metaOperation.getOperationDefinition() + "\n";

    for(const auto &preConditionPair : metaOperation.getPreConditions()){
        auto preCondition = preConditionPair.second;
        metaOperationString += "pre " + preCondition->getName() + ": " + preCondition->getExpression().toString() + "\n";
    }

    for(const auto &postConditionPair : metaOperation.getPostConditions()){
        auto postCondition = postConditionPair.second;
        metaOperationString += "post " + postCondition->getName() + ": " + postCondition->getExpression().toString() + "\n";
    }
    return metaOperationString;
}

std::any VisitorUSE::visit(MetaModel::MetaConstraint metaConstraint){
    std::string metaConstraintString = "";
    if(metaConstraint.getVariables().size() > 1){
        metaConstraintString += "context ";

        auto variablesIterator = metaConstraint.getVariables().begin();
        auto variable = variablesIterator->second;

        metaConstraintString += variable->getName();

        variablesIterator++;

        for(; variablesIterator != metaConstraint.getVariables().end(); variablesIterator++){
            variable = variablesIterator->second;

            metaConstraintString += ", " + variable->getName();
        }

        metaConstraintString += ": " + metaConstraint.getClass().getName() + " inv " + metaConstraint.getName() + ":\n\t" + metaConstraint.getExpression().toString();

        globalConstraints += metaConstraintString + "\n\n";

        return 0;
    }else{
        if(metaConstraint.getIsExistential()){
            metaConstraintString += "existential inv " + metaConstraint.getName() + ":\n\t" + metaConstraint.getExpression().toString() + "\n";
        }else{
            metaConstraintString += "inv " + metaConstraint.getName() + ":\n\t" + metaConstraint.getExpression().toString() + "\n";
        }
    }
    return metaConstraintString;
}

std::any VisitorUSE::visit(MetaModel::MetaAssociationEnd metaAssociationEnd){
    std::string metaAssociationEndString = "";
    metaAssociationEndString += metaAssociationEnd.getClass().getName();

    metaAssociationEndString += " [" + metaAssociationEnd.getMultiplicity().toString() + "] ";

    metaAssociationEndString += "role " + metaAssociationEnd.getRole();

    if(!metaAssociationEnd.getIsNavigable()){
        metaAssociationEndString += " --X";
    }

    metaAssociationEndString += " " + visibilityToString(metaAssociationEnd.getVisibility()) + "\n";

    if(metaAssociationEnd.getIsOrdered()){
        metaAssociationEndString += " ordered";
    }

    if(metaAssociationEnd.getIsUnion()){
        metaAssociationEndString += " union";
    }

    for(auto &subsettedEndPair : metaAssociationEnd.getSubsettedEnds()){
        auto subsettedEnd = subsettedEndPair.second;

        metaAssociationEndString += " subsets " + subsettedEnd->getClass().getName();
    }

    for(auto &redefinedEndPair : metaAssociationEnd.getRedefinedEnds()){
        auto redefinedEnd = redefinedEndPair.second;

        metaAssociationEndString += " redefines " + redefinedEnd->getClass().getName();
    }

    //derive Expression and qualifiers ignored for now

    if(metaAssociationEndString.back() != '\n'){
        metaAssociationEndString += "\n";
    }

    return metaAssociationEndString;
}

std::any VisitorUSE::visit(MetaModel::MetaEnum metaEnum){
    std::string metaEnumString = "enum " + metaEnum.getName() + " {";

    auto metaEnumElements = metaEnum.getElements();
    auto elementsIterator = metaEnumElements.begin();

    metaEnumString += elementsIterator->second->getName();

    elementsIterator++;

    for(; elementsIterator != metaEnumElements.end(); elementsIterator++){
        metaEnumString += ", " + elementsIterator->second->getName();
    }

    metaEnumString += "}";

    outFile << metaEnumString << "\n\n";

    return 0;
}

std::any VisitorUSE::visit(MetaModel::MetaClass metaClass){
    //If class has already been visited, do nothing
    if(visitedClasses.find(metaClass.getName()) != visitedClasses.end()){
        return 0;
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
            metaClassString += std::any_cast<std::string>(attributePair.second->accept(*this));
        }
    }

    //Operations
    auto operations = metaClass.getOperations();

    if(operations.size() > 0){
        metaClassString += "operations\n";

        for(const auto &operationPair : operations){
            metaClassString += std::any_cast<std::string>(operationPair.second->accept(*this));
        }
    }

    //Constraints
    auto constraints = metaClass.getConstraints();

    if(constraints.size() > 0){
        metaClassString += "constraints\n";

        for(const auto &constraintPair : constraints){
            std::any constraintResult = constraintPair.second->accept(*this);
            if(auto contraintStringPtr = std::any_cast<std::string>(&constraintResult)){
                metaClassString += *contraintStringPtr;
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

    return 0;
}

std::any VisitorUSE::visit(MetaModel::MetaAssociation metaAssociation){
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
        metaAssociationString += std::any_cast<std::string>(assocEndPair.second->accept(*this));
    }

    metaAssociationString += "end\n\n";

    outFile << metaAssociationString;

    return 0;
}

std::any VisitorUSE::visit(MetaModel::MetaAssociationClass metaAssociationClass){
    //If association class has already been visited, do nothing
    if(visitedClasses.find(metaAssociationClass.getName()) != visitedClasses.end()){
        return 0;
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
        metaAssociationClassString += std::any_cast<std::string>(assocEndPair.second->accept(*this));
    }

    //Attributes
    auto attributes = metaAssociationClass.getAttributes();

    if(attributes.size() > 0){
        metaAssociationClassString += "attributes\n";

        for(const auto &attributePair : attributes){
            metaAssociationClassString += std::any_cast<std::string>(attributePair.second->accept(*this));
        }
    }

    //Operations
    auto operations = metaAssociationClass.getOperations();

    if(operations.size() > 0){
        metaAssociationClassString += "operations\n";
        for(const auto &operationPair : operations){
            metaAssociationClassString += std::any_cast<std::string>(operationPair.second->accept(*this));
        }
    }

    //Constraints
    auto constraints = metaAssociationClass.getConstraints();

    if(constraints.size() > 0){
        metaAssociationClassString += "constraints\n";

        for(const auto &constraintPair : constraints){
            std::any constraintResult = constraintPair.second->accept(*this);
            if(auto contraintStringPtr = std::any_cast<std::string>(&constraintResult)){
                metaAssociationClassString += *contraintStringPtr;
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

    return 0;
}

void VisitorUSE::save() {
    if (outFile.is_open()) {
        outFile.flush();
    }
}

}
