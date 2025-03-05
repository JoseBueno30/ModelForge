#include "generated/USEBaseVisitor.h"
#include "metamodel/MetaModel.h"
#include <QDebug>
#include <any>

class CustomUSEVisitor : public USEBaseVisitor{
public:
    std::shared_ptr<MetaModel::MetaModel> model;
    int preConditionCounter = 0;
    int postConditionCounter = 0;
    int invariantCounter = 0;

    antlrcpp::Any visitModel(USEParser::ModelContext *ctx) override {

        // Create model
        if (ctx->ID()) {
            model = std::make_shared<MetaModel::MetaModel>(ctx->ID()->getText());
        }

        // Lists for each ModelElement
        std::vector<USEParser::EnumContext*> enumElements;
        std::vector<USEParser::ClassContext*> classElements;
        std::vector<USEParser::AssociationContext*> associationElements;
        std::vector<USEParser::AssociationClassContext*> associationClassElements;
        std::vector<USEParser::ConstraintsContext*> constraintElements;

        for (auto element : ctx->modelElement()) {
            if (auto enumElem = dynamic_cast<USEParser::EnumContext*>(element)) {
                enumElements.push_back(enumElem);
            } else if (auto classElem = dynamic_cast<USEParser::ClassContext*>(element)) {
                classElements.push_back(classElem);
            } else if (auto assocElem = dynamic_cast<USEParser::AssociationContext*>(element)) {
                associationElements.push_back(assocElem);
            } else if (auto assocClassElem = dynamic_cast<USEParser::AssociationClassContext*>(element)) {
                associationClassElements.push_back(assocClassElem);
            } else if (auto consElem = dynamic_cast<USEParser::ConstraintsContext*>(element)) {
                constraintElements.push_back(consElem);
            }
        }

        // Add user-defined types to model (enums)
        for (auto enumElem : enumElements) {
            visit(enumElem);
        }

        // Add empty classes to model
        for (auto classElem : classElements) {
            const std::string className = classElem->classDefinition()->ID()->getText();
            bool isAbstract = classElem->classDefinition()->ABSTRACT()? true : false;
            model->addClass(std::make_shared<MetaModel::MetaClass>(className, isAbstract));
        }

        // Add empty association classes to model
        for (auto assocClassElem: associationClassElements){
            const std::string className = assocClassElem->associationClassDefinition()->ID()->getText();
            bool isAbstract = assocClassElem->associationClassDefinition()->ABSTRACT()? true : false;
            int type = MetaModel::MetaAssociation::ASSOCIATION;
            if(assocClassElem->associationClassDefinition()->AGGREGATION()){
                type = MetaModel::MetaAssociation::AGGREGATION;
            }else if(assocClassElem->associationClassDefinition()->COMPOSITION()){
                type = MetaModel::MetaAssociation::COMPOSITION;
            }

            model->addAssociationClass(std::make_shared<MetaModel::MetaAssociationClass>(className, isAbstract, type));
        }

        // Add attributes and set generalization relationships. The names of all classes are known at this point
        for (auto classElem : classElements) {
            visit(classElem);
        }

        // Add attributes and set generalization relationships of the association classes. The names of all classes are known at this point
        for (auto associationClassElem : associationClassElements) {
            visit(associationClassElem);
        }

        // Add associations. Classes are known and can be referenced by role names


        // Generalization of association classes might leave out new rolenames. Add them from parent


        // Add associationEnd specific constraints, e. g. subsets. Role names are known and can be subset


        // Add associationEnd specific constraints for association classes, e. g. subsets. Role names are known and can be subset


        // Generate bodies of association and non-association classes All class interfaces are known and association features are available for expressions


        // Generate constraints of association and non-association classes All class interfaces are known and association features are available for expressions
        for (auto classElem : classElements) {
            addClassConstraints(classElem->classDefinition());
        }

        for (auto associationClassElem : associationClassElements) {
            addAssociationClassConstraints(associationClassElem->associationClassDefinition());
        }


        // Generate global constraints. All class interfaces are known and association features are available for expressions
        // Generate pre-/postconditions

        for (auto constraint: constraintElements){
            visit(constraint);
        }


        return model;
    }

    std::any visitEnum(USEParser::EnumContext *ctx) override {
        return visit(ctx->enumTypeDefinition());
    }

    std::any visitEnumTypeDefinition(USEParser::EnumTypeDefinitionContext *ctx) override {

        std::shared_ptr<MetaModel::MetaEnum> metaEnum = nullptr;

        for(auto element : ctx->idList()->ID()){
            std::shared_ptr<MetaModel::MetaEnumElement> enumElement = std::make_shared<MetaModel::MetaEnumElement>(element->getText());
            if(metaEnum == nullptr){
                metaEnum = std::make_shared<MetaModel::MetaEnum>(ctx->ID()->getText(), enumElement);
            }else{
                metaEnum->addElement(enumElement);
            }
        }

        model->addEnum(metaEnum);

        return nullptr;
    }

    std::any visitClass(USEParser::ClassContext *ctx) override {
        return visit(ctx->classDefinition());
    }

    std::any visitClassDefinition(USEParser::ClassDefinitionContext *ctx) override {
        auto metaClass = model->getClass(ctx->ID()->getText());

        //Add super classes
        if(ctx->idList()){
            for(auto superClassElem : ctx->idList()->ID()){
                auto superClass = model->getClass(superClassElem->getText());
                if(!superClass){
                    throw std::runtime_error("Undefined Super Class: " + superClassElem->getText() + ". Declare Super Classes before Child Classes");
                }

                metaClass->addSuperClass(superClass);
            }
        }

        //Add attributes
        for(auto attributeDefinition : ctx->attributeDefinition()){
            std::shared_ptr<MetaModel::MetaAttribute> attribute = std::any_cast<std::shared_ptr<MetaModel::MetaAttribute>>(visit(attributeDefinition));

            metaClass->addAttribute(attribute);
        }

        //Add operations
        for(auto operationDefinition : ctx->operationDefinition()){
            std::shared_ptr<MetaModel::MetaOperation> operation = std::any_cast<std::shared_ptr<MetaModel::MetaOperation>>(visit(operationDefinition));

            metaClass->addOperation(operation);
        }

        //Add state machines
        for(auto stateMachiDefinition : ctx->stateMachine()){
            std::shared_ptr<MetaModel::MetaStateMachine> stateMachine = std::make_shared<MetaModel::MetaStateMachine>(stateMachiDefinition->ID()->getText(), stateMachiDefinition->getText());

            metaClass->addStateMachine(stateMachine);
        }

        return nullptr;
    }

    std::any addClassConstraints(USEParser::ClassDefinitionContext *ctx){
        auto metaClass = model->getClass(ctx->ID()->getText());

        for(auto invariantClause : ctx->invariantClause()){
            visitInvariantClause(invariantClause, metaClass);
        }
        return nullptr;
    }


    std::any visitConstraints(USEParser::ConstraintsContext *ctx) override {
        for(auto constraintDefinition : ctx->constraintDefinition()){
            visit(constraintDefinition);
        }
        return nullptr;
    }

    virtual std::any visitInvariantDefinition(USEParser::InvariantDefinitionContext *ctx) override {
        return visit(ctx->invariant());
    }


    virtual std::any visitInvariant(USEParser::InvariantContext *ctx) override {
        std::vector<std::string> variableNames = {};
        for(auto variable : ctx->ID()){
            variableNames.push_back(variable->getText());
        }

        std::string className = ctx->simpleType()->ID()->getText();
        std::shared_ptr<MetaModel::MetaClass> scopeClass = model->getClass(className);
        if(!scopeClass) scopeClass = model->getAssociationClass(className);

        if(!scopeClass){
            throw std::invalid_argument("Expected valid class name, found '"+ className + "'.");
        }

        for(auto invariantClause : ctx->invariantClause()){
            visitInvariantClause(invariantClause, scopeClass, variableNames);
        }

        return nullptr;
    }

    std::any visitInvariantClause(USEParser::InvariantClauseContext *ctx, std::shared_ptr<MetaModel::MetaClass> scopeClass, const std::vector<std::string>& variableNames = {}){
        std::shared_ptr<MetaModel::MetaConstraint> constraint = nullptr;
        std::string name = "";
        if(ctx->ID()){
            name = ctx->ID()->getText();
        }else{
            name = "inv" + std::to_string(invariantCounter);
            invariantCounter++;
        }
        std::shared_ptr<MetaModel::OCLExpr> expression= std::any_cast<std::shared_ptr<MetaModel::OCLExpr>>(visit(ctx->expression()));
        bool isExistential = ctx->EXISTENTIAL()? true : false;

        if(variableNames.empty()){
            constraint = std::make_shared<MetaModel::MetaConstraint>(scopeClass, expression, name, isExistential);
        }else{
            constraint = std::make_shared<MetaModel::MetaConstraint>(scopeClass, variableNames, expression, name, isExistential);
        }

        scopeClass->addConstraint(constraint);

        return nullptr;
    }

    std::any visitAttributeDefinition(USEParser::AttributeDefinitionContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        std::shared_ptr<MetaModel::MetaAttribute> attribute = std::make_shared<MetaModel::MetaAttribute>(name, type);

        if(ctx->initDefinition()){
            std::shared_ptr<MetaModel::OCLExpr> initExpression= std::any_cast<std::shared_ptr<MetaModel::OCLExpr>>(visit(ctx->initDefinition()));

            attribute->setInitExpr(initExpression);
        }else if(ctx->derivedDefinition()){
            std::shared_ptr<MetaModel::OCLExpr> deriveExpression= std::any_cast<std::shared_ptr<MetaModel::OCLExpr>>(visit(ctx->derivedDefinition()));

            attribute->setDeriveExpr(deriveExpression);
        }

        return attribute;
    }

    std::any visitOperationDefinition(USEParser::OperationDefinitionContext *ctx) override {
        std::string name = ctx->ID()->getText();

        std::shared_ptr<MetaModel::MetaType> returnType = MetaModel::Void::instance();
        if(ctx->type()){
            returnType = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));
        }

        std::string operationDefinition = "";
        if(ctx->expression()){
            operationDefinition = ctx->expression()->getText();
        }else if(ctx->SOIL_OPERATION()){
            operationDefinition = ctx->SOIL_OPERATION()->getText();
        }

        std::shared_ptr<MetaModel::MetaOperation> operation = std::make_shared<MetaModel::MetaOperation>(name, operationDefinition, returnType);

        for(auto variableDeclaration : ctx->paramList()->variableDeclaration()){
            std::shared_ptr<MetaModel::MetaVariable> variable = std::any_cast<std::shared_ptr<MetaModel::MetaVariable>>(visit(variableDeclaration));

            operation->addVariable(variable);
        }

        for(auto prePostClauseDefinition : ctx->prePostClause()){
            std::shared_ptr<MetaModel::PrePostClause> prePostClause = std::any_cast<std::shared_ptr<MetaModel::PrePostClause>>(visit(prePostClauseDefinition));

            if(prePostClause->getIsPre()){
                operation->addPreCondition(prePostClause);
            }else if(prePostClause->getIsPost()){
                operation->addPostCondition(prePostClause);
            }
        }

        return operation;
    }

    std::any visitVariableDeclaration(USEParser::VariableDeclarationContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        return std::make_shared<MetaModel::MetaVariable>(name, type);
    }

    std::any visitPreCondition(USEParser::PreConditionContext *ctx) override {
        std::string name = "";
        if(ctx->ID()){
            name = ctx->ID()->getText();
        }else{
            name = "PreCondition" + std::to_string(preConditionCounter);
            preConditionCounter++;
        }

        std::shared_ptr<MetaModel::OCLExpr> expression= std::any_cast<std::shared_ptr<MetaModel::OCLExpr>>(visit(ctx->expression()));



        return std::make_shared<MetaModel::PrePostClause>(name, expression, true, false);
    }

    std::any visitPostCondition(USEParser::PostConditionContext *ctx) override {
        std::string name = "";
        if(ctx->ID()){
            name = ctx->ID()->getText();
        }else{
            name = "PostCondition" + std::to_string(postConditionCounter);
            postConditionCounter++;
        }

        std::shared_ptr<MetaModel::OCLExpr> expression= std::any_cast<std::shared_ptr<MetaModel::OCLExpr>>(visit(ctx->expression()));

        return std::make_shared<MetaModel::PrePostClause>(name, expression, false, true);
    }

    std::any visitPrePostDefinition(USEParser::PrePostDefinitionContext *ctx) override {
        return visit(ctx->prePost());
    }

    std::any visitPrePost(USEParser::PrePostContext *ctx) override {
        // Check that the class in the context exists
        std::string className = ctx->ID()[0]->getText();
        std::shared_ptr<MetaModel::MetaClass> scopeClass = model->getClass(className);

        if(!scopeClass){
            throw std::invalid_argument("Expected valid class name, found '"+ className + "'.");
        }


        // Check that the class has the operation declared in the context
        std::string opName = ctx->ID()[1]->getText();
        std::shared_ptr<MetaModel::MetaOperation> scopeOperation = scopeClass->getOperation(opName);

        if(!scopeOperation){
            throw std::invalid_argument("Class '" + className + "' has no operation '"+ opName + "'.");
        }


        // Check that the especified return type match the definition of the operation
        std::shared_ptr<MetaModel::MetaType> returnType = MetaModel::Void::instance();

        if(ctx->type()){
            returnType = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));
        }

        if(!returnType->equals(scopeOperation->getReturnType())){
            throw std::invalid_argument("Expected result type '" + scopeOperation->getReturnType().toString() + "' instead of '"+ returnType->toString() + "'.");
        }


        // Check that the especified parameters (size, name and type) match the definition of the operation
        std::map<std::string, std::shared_ptr<MetaModel::MetaVariable>> variables;
        std::map<std::string, std::shared_ptr<MetaModel::MetaVariable>> opVariables = scopeOperation->getVariables();

        for(auto variableDeclaration : ctx->paramList()->variableDeclaration()){
            std::shared_ptr<MetaModel::MetaVariable> variable = std::any_cast<std::shared_ptr<MetaModel::MetaVariable>>(visit(variableDeclaration));

            if (variables.find(variable->getName()) != variables.end()) {
                throw std::runtime_error("Redefinition of variable: '" + variable->getName() + "' in global constraint declaration.");
            }

            variables[variable->getName()] = variable;
        }

        if(variables.size() != opVariables.size()){
            throw std::runtime_error("This signature of operation: '" + opName + "' does not match its previous declaration in class: '" + className + "'.");
        }

        auto it1 = variables.begin();
        auto it2 = opVariables.begin();

        for (; it1 != variables.end(); ++it1, ++it2) {
            if (!(it1->second->getName() != it2->second->getName()) || !(it1->second->getType().equals(it2->second->getType()))){
                throw std::runtime_error("This signature of operation: '" + opName + "' does not match its previous declaration in class: '" + className + "'.");
            };
        }

        // Generate and add Pre and Post Conditions to the operation
        for(auto prePostClauseDefinition : ctx->prePostClause()){
            std::shared_ptr<MetaModel::PrePostClause> prePostClause = std::any_cast<std::shared_ptr<MetaModel::PrePostClause>>(visit(prePostClauseDefinition));

            if(prePostClause->getIsPre()){
                scopeOperation->addPreCondition(prePostClause);
            }else if(prePostClause->getIsPost()){
                scopeOperation->addPostCondition(prePostClause);
            }
        }

        return visitChildren(ctx);
    }


    // TYPE DEFINITION

    std::any visitTypeSimple(USEParser::TypeSimpleContext *ctx) override {
        return visitChildren(ctx->simpleType());
    }

    std::any visitTypeCollection(USEParser::TypeCollectionContext *ctx) override {
        return visit(ctx->collectionType());
    }

    std::any visitTypeTuple(USEParser::TypeTupleContext *ctx) override {
        return visit(ctx->tupleType());
    }

    std::any visitSimpleType(USEParser::SimpleTypeContext *ctx) override {
        std::string typeName = ctx->ID()->getText();

        if(typeName == "Real"){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::Real::instance());
        }else if(typeName == "Integer"){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::Integer::instance());
        }else if(typeName == "String"){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::String::instance());
        }else if(typeName == "Boolean"){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::Boolean::instance());
        }else if(typeName == "Void"){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::Void::instance());
        }

        if(auto enumType = model->getEnum(typeName)){
            return std::static_pointer_cast<MetaModel::MetaType>(enumType);
        }

        if(auto classType = model->getClass(typeName)){
            return std::static_pointer_cast<MetaModel::MetaType>(classType);
        }

        if(auto assocClassType = model->getAssociationClass(typeName)){
            return std::static_pointer_cast<MetaModel::MetaType>(assocClassType);
        }

        throw std::invalid_argument("Expexted valid type name, found '"+ typeName + "'.");

        return nullptr;
    }

    std::any visitTypeSimpleCollection(USEParser::TypeSimpleCollectionContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        std::shared_ptr<MetaModel::CollectionType> collectionType = std::make_shared<MetaModel::CollectionType>(false, false, 0, type);

        return std::static_pointer_cast<MetaModel::MetaType>(collectionType);
    }

    std::any visitTypeSet(USEParser::TypeSetContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        std::shared_ptr<MetaModel::CollectionType> setType = std::make_shared<MetaModel::CollectionType>(false, true, 0, type);

        return std::static_pointer_cast<MetaModel::MetaType>(setType);
    }

    std::any visitTypeSequence(USEParser::TypeSequenceContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        std::shared_ptr<MetaModel::CollectionType> sequenceType = std::make_shared<MetaModel::CollectionType>(true, false, 0, type);

        return std::static_pointer_cast<MetaModel::MetaType>(sequenceType);
    }

    std::any visitTypeBag(USEParser::TypeBagContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        std::shared_ptr<MetaModel::CollectionType> bagType = std::make_shared<MetaModel::CollectionType>(false, false, 0, type);

        return std::static_pointer_cast<MetaModel::MetaType>(bagType);
    }

    std::any visitTypeOrderedSet(USEParser::TypeOrderedSetContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        std::shared_ptr<MetaModel::CollectionType> orderedSetType = std::make_shared<MetaModel::CollectionType>(true, true, 0, type);

        return std::static_pointer_cast<MetaModel::MetaType>(orderedSetType);
    }

    std::any visitTupleType(USEParser::TupleTypeContext *ctx) override {
        std::shared_ptr<MetaModel::TupleType> tupleType = nullptr;

        for(auto tuplePartDefinition : ctx->tuplePart()){
            std::shared_ptr<MetaModel::TuplePart> tuplePart = std::any_cast<std::shared_ptr<MetaModel::TuplePart>>(visit(tuplePartDefinition));
            if(tupleType == nullptr){
                tupleType = std::make_shared<MetaModel::TupleType>(tuplePart);
            }else{
                tupleType->addElement(tuplePart);
            }
        }

        return std::static_pointer_cast<MetaModel::MetaType>(tupleType);
    }

    std::any visitTuplePart(USEParser::TuplePartContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        std::shared_ptr<MetaModel::TuplePart> tuplePart = std::make_shared<MetaModel::TuplePart>(name, type);

        return tuplePart;
    }

    std::any visitInitDefinition(USEParser::InitDefinitionContext *ctx) override {
        return visit(ctx->expression());
    }

    std::any visitDerivedDefinition(USEParser::DerivedDefinitionContext *ctx) override {
        return visit(ctx->expression());
    }

    std::any visitOclExpression(USEParser::OclExpressionContext *ctx) override {

        return std::make_shared<MetaModel::OCLExpr>(ctx->getText());
    }

    // ASSOCIAITON CLASS DEFINITION

    std::any visitAssociationClass(USEParser::AssociationClassContext *ctx) override {
        return visit(ctx->associationClassDefinition());
    }

    std::any visitAssociationClassDefinition(USEParser::AssociationClassDefinitionContext *ctx) override {
        auto metaAssociationClass = model->getAssociationClass(ctx->ID()->getText());

        //Add super classes
        if(ctx->idList()){
            for(auto superClassElem : ctx->idList()->ID()){
                auto superClass = model->getAssociationClass(superClassElem->getText());
                if(!superClass){
                    throw std::runtime_error("Undefined Super Class: " + superClassElem->getText() + ". Declare Super Classes before Child Classes");
                }

                metaAssociationClass->addSuperClass(superClass);
            }
        }

        //Add attributes
        for(auto attributeDefinition : ctx->attributeDefinition()){
            std::shared_ptr<MetaModel::MetaAttribute> attribute = std::any_cast<std::shared_ptr<MetaModel::MetaAttribute>>(visit(attributeDefinition));

            metaAssociationClass->addAttribute(attribute);
        }

        //Add operations
        for(auto operationDefinition : ctx->operationDefinition()){
            std::shared_ptr<MetaModel::MetaOperation> operation = std::any_cast<std::shared_ptr<MetaModel::MetaOperation>>(visit(operationDefinition));

            metaAssociationClass->addOperation(operation);
        }

        //Add state machines
        for(auto stateMachiDefinition : ctx->stateMachine()){
            std::shared_ptr<MetaModel::MetaStateMachine> stateMachine = std::make_shared<MetaModel::MetaStateMachine>(stateMachiDefinition->ID()->getText(), stateMachiDefinition->getText());

            metaAssociationClass->addStateMachine(stateMachine);
        }

        return nullptr;
    }

    std::any addAssociationClassConstraints(USEParser::AssociationClassDefinitionContext *ctx){
        auto metaAssociationClass = model->getAssociationClass(ctx->ID()->getText());

        for(auto invariantClause : ctx->invariantClause()){
            visitInvariantClause(invariantClause, metaAssociationClass);
        }

        return nullptr;
    }


    // ASSOCIATION DEFINITION

    std::any visitSimpleAssociation(USEParser::SimpleAssociationContext *ctx) override{
        std::shared_ptr<MetaModel::MetaAssociation> simpleAssociation = std::make_shared<MetaModel::MetaAssociation>(ctx->ID()->getText(), 0);
        std::map<std::string, std::shared_ptr<MetaModel::MetaAssociationEnd>> map;
        for(auto endCtx : ctx->associationEnd()){
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd = std::any_cast<std::shared_ptr<MetaModel::MetaAssociationEnd>>(visit(endCtx));
            simpleAssociation->addAssociationEnd(associationEnd);
        }

        return simpleAssociation;
    }

    std::any visitAggregation(USEParser::AggregationContext *ctx) override{
        std::map<std::string, std::shared_ptr<MetaModel::MetaAssociationEnd>> map;
        std::shared_ptr<MetaModel::MetaAssociation> aggregation = std::make_shared<MetaModel::MetaAssociation>(ctx->ID()->getText(), 1);
        for(auto endCtx : ctx->associationEnd()){
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd = std::any_cast<std::shared_ptr<MetaModel::MetaAssociationEnd>>(visit(endCtx));
            aggregation->addAssociationEnd(associationEnd);
        }
        return aggregation;
    }

    std::any visitComposition(USEParser::CompositionContext *ctx) override{
        std::map<std::string, std::shared_ptr<MetaModel::MetaAssociationEnd>> map;
        std::shared_ptr<MetaModel::MetaAssociation> composition = std::make_shared<MetaModel::MetaAssociation>(ctx->ID()->getText(), 2);
        for(auto endCtx : ctx->associationEnd()){
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd = std::any_cast<std::shared_ptr<MetaModel::MetaAssociationEnd>>(visit(endCtx));
            composition->addAssociationEnd(associationEnd);
        }
        return composition;
    }

    std::any visitAssociationEnd(USEParser::AssociationEndContext *ctx) override{

        std::shared_ptr<MetaModel::MetaMultiplicity> multiplicity = std::any_cast<std::shared_ptr<MetaModel::MetaMultiplicity>>(visit(ctx->multiplicity()));

        // TODO
        // check Ordered and union
        // Redefines and Subsets must be checked when all associations have been created
        // derive/derived: where vars declaration are saved

        std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd;
        return associationEnd;
    }

    std::any visitMultiplicity(USEParser::MultiplicityContext *ctx) override{
        std::shared_ptr<MetaModel::MetaMultiplicityRange> firstRange = std::any_cast<std::shared_ptr<MetaModel::MetaMultiplicityRange>>(visit(ctx->multiplicityRange().at(0)));
        std::shared_ptr<MetaModel::MetaMultiplicity> multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(firstRange->getLowerBound(), firstRange->getUpperBound());
        for(int i = 1; i < ctx->multiplicityRange().size(); i++){
            std::shared_ptr<MetaModel::MetaMultiplicityRange> range = std::any_cast<std::shared_ptr<MetaModel::MetaMultiplicityRange>>(visit(ctx->multiplicityRange().at(i)));
            multiplicity->addRange(range->getLowerBound(), range->getUpperBound());
        }

        return multiplicity;
    }

    std::any visitMultiplicityRange(USEParser::MultiplicityRangeContext *ctx) override{
        int lowerBound = std::any_cast<int>(visit(ctx->multiplicitySpec().at(0)));
        int upperBound = ctx->DOTDOT() ? std::any_cast<int>(visit(ctx->multiplicitySpec().at(1))) : lowerBound;

        std::shared_ptr<MetaModel::MetaMultiplicityRange> range = std::make_shared<MetaModel::MetaMultiplicityRange>(lowerBound, upperBound);
        return range;
    }

    std::any visitMultiplicitySpec(USEParser::MultiplicitySpecContext *ctx) override{
        return ctx->STAR() ? MetaModel::MetaMultiplicityRange::MANY : std::stoi(ctx->INT()->getText());
    }
};
