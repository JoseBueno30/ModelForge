#include "generated/USEBaseVisitor.h"
#include "metamodel/MetaModel.h"
#include <any>
#include <OCL/AdditiveExpr.h>
#include <OCL/AttributeNavigationExpr.h>
#include <OCL/ConditionalExpr.h>
#include <OCL/EqualityExpr.h>
#include <OCL/FactorExpr.h>
#include <OCL/LetExpr.h>
#include <OCL/LogicalExpr.h>
#include <OCL/NavigationExpr.h>
#include <OCL/ObjectOperationExpr.h>
#include <OCL/PrimaryExpr.h>
#include <OCL/QueryExpr.h>
#include <OCL/RelationalExpr.h>
#include <OCL/TypeExpr.h>
#include <OCL/UnaryExpr.h>
#include <OCL/VariableExpr.h>

class CustomUSEVisitor : public USEBaseVisitor{
public:

    std::shared_ptr<MetaModel::MetaModel> model;
    int preConditionCounter = 0;
    int postConditionCounter = 0;
    int invariantCounter = 0;

    struct DeferredExpr {
        std::shared_ptr<MetaModel::MetaAttribute> target;
        std::shared_ptr<MetaModel::MetaClass> classContext;
        USEParser::ExpressionContext* exprCtx;
        bool isInit;
    };
    std::vector<DeferredExpr> deferredAttributes;

    std::shared_ptr<MetaModel::Expr> currentExprSource;
    bool currentPropertyCallIsArrow;
    std::shared_ptr<MetaModel::MetaConstraint> currentConstraintContext;
    std::shared_ptr<MetaModel::MetaClass> currentClassContext;
    std::map<std::string, std::shared_ptr<MetaModel::MetaVariable>> currentQueryContext;

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
        for(auto assocElem : associationElements){
            visit(assocElem);
        }

        // Add associationEnd specific constraints, e. g. subsets. Role names are known and can be subset
        for(auto assocElem : associationElements){
            visit(assocElem);
        }

        // Add attributes init and derive expressions
        addAttributesInitAndDerive();

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
                    throw std::invalid_argument("Undefined Super Class: " + superClassElem->getText() + ". Declare Super Classes before Child Classes");
                }

                metaClass->addSuperClass(superClass);
            }
        }

        this->currentClassContext = metaClass;
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

    std::any addAttributesInitAndDerive(){
        std::cout << "ADDING ATTRIBUTES INIT AND DERIVE" << std::endl;
        for (auto& deferredAttribute : deferredAttributes) {
            this->currentExprSource = nullptr;
            this->currentPropertyCallIsArrow = false;
            this->currentClassContext = deferredAttribute.classContext;
            auto expr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(deferredAttribute.exprCtx));
            if (deferredAttribute.isInit) {
                deferredAttribute.target->setInitExpr(expr);
            } else {
                deferredAttribute.target->setDeriveExpr(expr);
            }
        }
        deferredAttributes.clear();
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
            name = "inv" + std::to_string(this->invariantCounter);
            this->invariantCounter++;
        }

        bool isExistential = ctx->EXISTENTIAL()? true : false;

        if(variableNames.empty()){
            constraint = std::make_shared<MetaModel::MetaConstraint>(scopeClass, name, isExistential);
        }else{
            constraint = std::make_shared<MetaModel::MetaConstraint>(scopeClass, variableNames, name, isExistential);
        }

        this->currentConstraintContext = constraint;

        std::shared_ptr<MetaModel::Expr> expression= std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));

        constraint->setExpression(expression);

        scopeClass->addConstraint(constraint);

        return nullptr;
    }

    std::any visitVisibilty(USEParser::VisibiltyContext *ctx) override {
        if(ctx->PUBLIC()){
            return MetaModel::Visibility::Public;
        }else if(ctx->PRIVATE()){
            return MetaModel::Visibility::Private;
        }else if(ctx->PROTECTED()){
            return MetaModel::Visibility::Protected;
        }else if(ctx->PACKAGE()){
            return MetaModel::Visibility::Package;
        }else{
            return nullptr;
        }
    }

    std::any visitAttributeDefinition(USEParser::AttributeDefinitionContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        MetaModel::Visibility visibility = MetaModel::Visibility::Public;

        std::cout << "VISIBILITY:" << std::endl;
        std::cout << ctx->getText() << std::endl;

        if(ctx->visibilty()){
            std::cout << ctx->visibilty()->getText() << std::endl;
            visibility = std::any_cast<MetaModel::Visibility>(visit(ctx->visibilty()));
        }

        std::shared_ptr<MetaModel::MetaAttribute> attribute = std::make_shared<MetaModel::MetaAttribute>(name, type, visibility);

        if(ctx->initDefinition()){
            this->deferredAttributes.push_back({attribute, this->currentClassContext, ctx->initDefinition()->expression(), true});
        }else if(ctx->derivedDefinition()){
            this->deferredAttributes.push_back({attribute, this->currentClassContext, ctx->derivedDefinition()->expression(), false});
        }
        return attribute;
    }

    std::any visitOperationDefinition(USEParser::OperationDefinitionContext *ctx) override {
        std::cout << "VISIT OPERATION DEFINITION: " << ctx->getText() << std::endl;
        std::string name = ctx->ID()->getText();

        std::shared_ptr<MetaModel::MetaType> returnType = MetaModel::Void::instance();
        if(ctx->type()){
            returnType = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));
        }

        MetaModel::Visibility visibility = MetaModel::Visibility::Public;
        if(ctx->visibilty()){
            visibility = std::any_cast<MetaModel::Visibility>(visit(ctx->visibilty()));
        }

        std::string operationDefinition = "";
        if(ctx->expression()){
            operationDefinition = "= " + ctx->expression()->getText();
        }else if(ctx->SOIL_OPERATION()){
            operationDefinition = ctx->SOIL_OPERATION()->getText();
        }

        std::shared_ptr<MetaModel::MetaOperation> operation = std::make_shared<MetaModel::MetaOperation>(name, operationDefinition, returnType, visibility);

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
            name = "PreCondition" + std::to_string(this->preConditionCounter);
            this->preConditionCounter++;
        }

        std::shared_ptr<MetaModel::Expr> expression= std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));



        return std::make_shared<MetaModel::PrePostClause>(name, expression, true, false);
    }

    std::any visitPostCondition(USEParser::PostConditionContext *ctx) override {
        std::string name = "";
        if(ctx->ID()){
            name = ctx->ID()->getText();
        }else{
            name = "PostCondition" + std::to_string(this->postConditionCounter);
            this->postConditionCounter++;
        }

        std::shared_ptr<MetaModel::Expr> expression= std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));

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
                throw std::invalid_argument("Redefinition of variable: '" + variable->getName() + "' in global constraint declaration.");
            }

            variables[variable->getName()] = variable;
        }

        if(variables.size() != opVariables.size()){
            throw std::invalid_argument("This signature of operation: '" + opName + "' does not match its previous declaration in class: '" + className + "'.");
        }

        auto it1 = variables.begin();
        auto it2 = opVariables.begin();

        for (; it1 != variables.end(); ++it1, ++it2) {
            if (it1->second->getName() != it2->second->getName() || !(it1->second->getType().equals(it2->second->getType()))){
                throw std::invalid_argument("This signature of operation: '" + opName + "' does not match its previous declaration in class: '" + className + "'.");
            };
        }

        this->currentClassContext = scopeClass;

        // Generate and add Pre and Post Conditions to the operation
        for(auto prePostClauseDefinition : ctx->prePostClause()){
            std::shared_ptr<MetaModel::PrePostClause> prePostClause = std::any_cast<std::shared_ptr<MetaModel::PrePostClause>>(visit(prePostClauseDefinition));

            if(prePostClause->getIsPre()){
                scopeOperation->addPreCondition(prePostClause);
            }else if(prePostClause->getIsPost()){
                scopeOperation->addPostCondition(prePostClause);

            }
        }

        return nullptr;
    }


    // TYPE DEFINITION

    std::any visitTypeSimple(USEParser::TypeSimpleContext *ctx) override {
        return visit(ctx->simpleType());
    }

    std::any visitTypeCollection(USEParser::TypeCollectionContext *ctx) override {
        return visit(ctx->collectionType());
    }

    std::any visitTypeTuple(USEParser::TypeTupleContext *ctx) override {
        return visit(ctx->tupleType());
    }

    std::any visitSimpleType(USEParser::SimpleTypeContext *ctx) override {
        std::string typeName = ctx->ID()->getText();

        if(typeName == MetaModel::Real::instance()->toString()){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::Real::instance());
        }else if(typeName == MetaModel::Integer::instance()->toString()){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::Integer::instance());
        }else if(typeName == MetaModel::String::instance()->toString()){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::String::instance());
        }else if(typeName == MetaModel::Boolean::instance()->toString()){
            return std::static_pointer_cast<MetaModel::MetaType>(MetaModel::Boolean::instance());
        }else if(typeName == MetaModel::Void::instance()->toString()){
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
                    throw std::invalid_argument("Undefined Super Class: " + superClassElem->getText() + ". Declare Super Classes before Child Classes");
                }

                metaAssociationClass->addSuperClass(superClass);
            }
        }

        this->currentClassContext = metaAssociationClass;
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

        for(auto associationEndsCtx : ctx->associationEnd()){
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd = std::any_cast<std::shared_ptr<MetaModel::MetaAssociationEnd>>(createAssociationEnd(associationEndsCtx, metaAssociationClass));
            std::cout << "ADDING ASSOC END: " << associationEnd->getRole() << " TO ASSOCIATION CLASS " << associationEnd->getAssociationSharedPtr()->getName() << std::endl;
            metaAssociationClass->addAssociationEnd(associationEnd);
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
        std::shared_ptr<MetaModel::MetaAssociation> association = model->getAssociation(ctx->ID()->getText());
        if(association == nullptr){
            addAssociationToModel(ctx->ID()->getText(), ctx->associationEnd(), MetaModel::MetaAssociation::ASSOCIATION);
        }else{
            addSubsetsAndRedefines(association ,ctx->associationEnd());
        }
        return nullptr;
    }

    std::any visitAggregation(USEParser::AggregationContext *ctx) override{
        std::shared_ptr<MetaModel::MetaAssociation> aggregation = model->getAssociation(ctx->ID()->getText());
        if(aggregation == nullptr){
            addAssociationToModel(ctx->ID()->getText(), ctx->associationEnd(), MetaModel::MetaAssociation::AGGREGATION);
        }else{
            addSubsetsAndRedefines(aggregation ,ctx->associationEnd());
        }
        return nullptr;
    }

    std::any visitComposition(USEParser::CompositionContext *ctx) override{
        std::shared_ptr<MetaModel::MetaAssociation> composition = model->getAssociation(ctx->ID()->getText());
        if(composition == nullptr){
            addAssociationToModel(ctx->ID()->getText(), ctx->associationEnd(), MetaModel::MetaAssociation::COMPOSITION);
        }else{
            addSubsetsAndRedefines(composition ,ctx->associationEnd());
        }
        return nullptr;
    }

    void addAssociationToModel(const std::string& id, const std::vector<USEParser::AssociationEndContext *>& associationEnds, int type){
        std::shared_ptr<MetaModel::MetaAssociation> association = std::make_shared<MetaModel::MetaAssociation>(id, type);
        for(auto endCtx : associationEnds){
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd = std::any_cast<std::shared_ptr<MetaModel::MetaAssociationEnd>>(createAssociationEnd(endCtx, association));
            association->addAssociationEnd(associationEnd);
        }

        model->addAssociation(association);
    }

    void addSubsetsAndRedefines(std::shared_ptr<MetaModel::MetaAssociation> metaAssociation, const std::vector<USEParser::AssociationEndContext *>& associationEnds){
        for(auto associationEnd : associationEnds){
            std::string role;
            if(associationEnd->role()){
                role = std::any_cast<std::string>(visit(associationEnd->role()));
            }else{
                role = associationEnd->ID()->getText();
            }
            std::shared_ptr<MetaModel::MetaAssociationEnd> metaAssociationEnd = metaAssociation->getAssociationEnd(role);
            if(!associationEnd->redefines().empty()){
                addRedefinesToAssociationEnd(metaAssociationEnd, associationEnd->redefines());
            }
            if(!associationEnd->subsets().empty()){
                addSubsetsToAssociationEnds(metaAssociationEnd, associationEnd->subsets());
            }
        }
    }

    void addRedefinesToAssociationEnd(std::shared_ptr<MetaModel::MetaAssociationEnd> metaAssociationEnd, const std::vector<USEParser::RedefinesContext *>& redefinitions){
        // TODO - Check duplicated names and USE code to find more restrictions.
        for(auto redefinition : redefinitions){
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEndToRedefine = metaAssociationEnd->getClassSharedPtr()->getAssociationEnd(redefinition->ID()->getText());
            if(!associationEndToRedefine){
                throw std::invalid_argument("AssociationEnd '" + redefinition->ID()->getText() + "' doesn't exist.");
            }
            metaAssociationEnd->addRedefinedEnd(associationEndToRedefine);
        }
    }
    void addSubsetsToAssociationEnds(std::shared_ptr<MetaModel::MetaAssociationEnd> metaAssociationEnd, const std::vector<USEParser::SubsetsContext *>& subsets){
        // TODO - Check duplicated names and USE code to find more restrictions.
        for(auto subset : subsets){
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEndSubsetted = metaAssociationEnd->getClassSharedPtr()->getAssociationEnd(subset->ID()->getText());
            if(!associationEndSubsetted){
                throw std::invalid_argument("AssociationEnd'" + subset->ID()->getText() + "' doesn't exist.");
            }
            metaAssociationEnd->addSubsettedEnd(associationEndSubsetted);
        }
    }

    std::any createAssociationEnd(USEParser::AssociationEndContext *ctx, std::shared_ptr<MetaModel::MetaAssociation> association) {
        std::shared_ptr<MetaModel::MetaClass> endClass = model->getClass(ctx->ID()->getText());
        if(endClass == nullptr){
            throw std::invalid_argument("Class '"+ ctx->ID()->getText() +"' is not defined.");
        }

        std::shared_ptr<MetaModel::MetaMultiplicity> multiplicity = std::any_cast<std::shared_ptr<MetaModel::MetaMultiplicity>>(visit(ctx->multiplicity()));
        std::string role = checkRole(ctx);

        MetaModel::Visibility visibility = MetaModel::Visibility::Public;
        if(ctx->visibilty()){
            visibility = std::any_cast<MetaModel::Visibility>(visit(ctx->visibilty()));
        }

        bool isNavigable = !ctx->NO_NAVIGABLE();

        // check Ordered and union
        bool isOrdered = !ctx->ORDERED().empty();
        bool isUnion = !ctx->UNION().empty();

        //TODO Check IsUnique and ¿type?
        std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd = std::make_shared<MetaModel::MetaAssociationEnd>(endClass, association, role,
                                                                                                                        0, isNavigable, isOrdered, false,
                                                                                                                        isUnion, multiplicity, visibility);

        return associationEnd;
    }

    std::string checkRole(USEParser::AssociationEndContext *ctx){
        if(ctx->role()){
            return std::any_cast<std::string>(visit(ctx->role()));
        }else{
            return ctx->ID()->getText();
        }
    }

    std::any visitRole(USEParser::RoleContext *ctx) override{
        return ctx->ID()->getText();
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

    //EXPRESSIONS

    //BINARY EXPRESSIONS

    std::any visitLogicalExpr(USEParser::LogicalExprContext *ctx) override {
        auto expr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()));

        return expr;
    }

    std::any visitAndExpr(USEParser::AndExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[0]));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[1]));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::AndExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitOrExpr(USEParser::OrExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[0]));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[1]));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::OrExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitImpliesExpr(USEParser::ImpliesExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[0]));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[1]));

        bool isComplex = true;

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::ImpliesExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitXorExpr(USEParser::XorExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[0]));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->logicalExpression()[1]));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::XOrExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitEqualityExpr(USEParser::EqualityExprContext *ctx) override {
        return visit(ctx->equalityExpression());
    }

    std::any visitEqualExpr(USEParser::EqualExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->equalityExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->relationalExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::EqualExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitNotEqualExpr(USEParser::NotEqualExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->equalityExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->relationalExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::NotEqualExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitRelationalExpr(USEParser::RelationalExprContext *ctx) override {
        // std::shared_ptr<MetaModel::Expr> expr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->relationalExpression()));

        return visit(ctx->relationalExpression());
    }

    std::any visitLessThanExpr(USEParser::LessThanExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->relationalExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->additiveExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::LessThanExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitGreaterThanExpr(USEParser::GreaterThanExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->relationalExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->additiveExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::GreaterThanExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitLessThanOrEqualExpr(USEParser::LessThanOrEqualExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->relationalExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->additiveExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::LessThanOrEqualExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitGreaterThanOrEqualExpr(USEParser::GreaterThanOrEqualExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->relationalExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->additiveExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::GreaterThanOrEqualExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr1, expr2));
    }

    std::any visitAdditiveExpr(USEParser::AdditiveExprContext *ctx) override {
        return visit(ctx->additiveExpression());
    }

    std::any visitAdditionExpr(USEParser::AdditionExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->additiveExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->factorExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::AdditionExpr>(ctx->getText(), isComplex, MetaModel::Integer::instance(), expr1, expr2));
    }

    std::any visitSubtractionExpr(USEParser::SubtractionExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->additiveExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->factorExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::SubtractionExpr>(ctx->getText(), isComplex, MetaModel::Integer::instance(), expr1, expr2));
    }

    std::any visitFactorExpr(USEParser::FactorExprContext *ctx) override {
        return visit(ctx->factorExpression());
    }

    std::any visitMultiplicationExpr(USEParser::MultiplicationExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->factorExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->unaryExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::MultiplicationExpr>(ctx->getText(), isComplex, MetaModel::Integer::instance(), expr1, expr2));
    }

    std::any visitDivisionExpr(USEParser::DivisionExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr1 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->factorExpression()));
        std::shared_ptr<MetaModel::Expr> expr2 = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->unaryExpression()));

        bool isComplex = (expr1->isComplexExpr() || expr2->isComplexExpr());

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::DivisionExpr>(ctx->getText(), isComplex, MetaModel::Integer::instance(), expr1, expr2));
    }

    //UNARY EXPRESSIONS

    std::any visitUnaryExpr(USEParser::UnaryExprContext *ctx) override {
        return visit(ctx->unaryExpression());
    }

    std::any visitNotExpr(USEParser::NotExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->unaryExpression()));

        bool isComplex = expr->isComplexExpr();

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::NotExpr>(ctx->getText(), isComplex, MetaModel::Boolean::instance(), expr));
    }

    std::any visitPlusExpr(USEParser::PlusExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->unaryExpression()));

        bool isComplex = expr->isComplexExpr();

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::PlusExpr>(ctx->getText(), isComplex, expr->getType(), expr));
    }

    std::any visitMinusExpr(USEParser::MinusExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> expr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->unaryExpression()));

        bool isComplex = expr->isComplexExpr();

        return std::dynamic_pointer_cast<MetaModel::Expr>(std::make_shared<MetaModel::MinusExpr>(ctx->getText(), isComplex, expr->getType(), expr));
    }

    //PROPERTY CALLS

    std::any visitPostfixExpr(USEParser::PostfixExprContext *ctx) override {
        // std::shared_ptr<MetaModel::Expr> expr = std::make_shared<MetaModel::Expr>(ctx->getText(), true, MetaModel::Boolean::instance());
        
        // return expr;

        return visit(ctx->postfixExpression());
    }

    std::any visitPropertyCallExpr(USEParser::PropertyCallExprContext *ctx) override {
        std::cout << "VISITING PROPERTY CALL: " << ctx->getText() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;
        this->currentPropertyCallIsArrow = false;
        this->currentExprSource = nullptr;

        this->currentExprSource = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->primaryExpression()));

        for(auto propertyChain : ctx->propertyChain()){
            this->currentPropertyCallIsArrow = propertyChain->ARROW() != nullptr;

            this->currentExprSource = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(propertyChain->propertyCall()));
        }

        // this->currentExprSource = nullptr;

        return std::dynamic_pointer_cast<MetaModel::Expr>(this->currentExprSource);
    }

    //ITERATE EXPRESSION

    std::any visitIterateExpr(USEParser::IterateExprContext *ctx) override {
        return visit(ctx->iterateExpression());
    }

    std::any visitIterateExpression(USEParser::IterateExpressionContext *ctx) override {
        //Iterate expressions type is the type of variableInitialization, we ignore it because its complex
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::IterateExpr>(ctx->getText(), true, MetaModel::Void::instance(), this->currentPropertyCallIsArrow, this->currentExprSource));
    }

    //IN STATE EXPRESSION

    std::any visitInStateExpr(USEParser::InStateExprContext *ctx) override {
        return visit(ctx->inStateExpression());
    }

    std::any visitInStateExpression(USEParser::InStateExpressionContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::InStateExpr>(ctx->getText(), true, MetaModel::Boolean::instance(), this->currentPropertyCallIsArrow, this->currentExprSource));
    }

    //QUERY EXPRESSIONS

    std::any visitElemVarsDeclaration(USEParser::ElemVarsDeclarationContext *ctx) override {
        std::cout << "VISITING ELEM VAR DECL: " << ctx->getText() << std::endl;
        // this->currentQueryContext.clear();
        for (size_t i = 0; i < ctx->children.size(); ) {
            auto idToken = ctx->children[i];
            std::string name = idToken->getText();
            i++;

            std::shared_ptr<MetaModel::MetaType> type = this->currentExprSource->getType();

            // Check if the next child is a colon
            if (i < ctx->children.size() && ctx->children[i]->getText() == ":") {
                i++; // skip ":"
                if (i < ctx->children.size()) {
                    // next should be a type
                    auto typeCtx = dynamic_cast<USEParser::TypeContext*>(ctx->children[i]);
                    if (typeCtx) {
                        type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(typeCtx));
                    }
                    i++;
                }
            }

            if (i < ctx->children.size() && ctx->children[i]->getText() == ",") {
                i++;
            }

            // Build MetaVariable
            std::cout << "BUILDING VAR DECL: " << name << " OF TYPE: " << type->toString() << std::endl;
            auto var = std::make_shared<MetaModel::MetaVariable>(name, type);
            this->currentQueryContext[name] = var;
        }
        if(this->currentQueryContext.find("self") == this->currentQueryContext.end()){
            auto var = std::make_shared<MetaModel::MetaVariable>("self", std::dynamic_pointer_cast<MetaModel::MetaType>(this->currentClassContext));
            this->currentQueryContext["self"] = var;
        }
        return ctx->getText();
    }

    std::any visitQueryExpr(USEParser::QueryExprContext *ctx) override {
        std::cout << "VISITING QUERY EXPR: " << ctx->getText() << std::endl;
        std::cout << "CURRENT SOURCE EXPR: " << this->currentExprSource->getExpression() << std::endl;
        std::cout << "CURRENT SOURCE STR: " << this->currentExprSource->toString() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;
        auto res = visit(ctx->queryExpression());
        std::cout << "AFTER VISITING QUERY EXPR: " << ctx->getText() << std::endl;
        std::cout << "CURRENT SOURCE EXPR: " << this->currentExprSource->getExpression() << std::endl;
        std::cout << "CURRENT SOURCE STR: " << this->currentExprSource->toString() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;
        return res;
        // return visit(ctx->queryExpression());
    }

    std::any visitCollectExpr(USEParser::CollectExprContext *ctx) override {
        std::cout << "VISITING COLLECT EXPR: " << ctx->getText() << std::endl;
        std::cout << "CURRENT SOURCE EXPR: " << this->currentExprSource->getExpression() << std::endl;
        std::cout << "CURRENT SOURCE STR: " << this->currentExprSource->toString() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;
        std::shared_ptr<MetaModel::Expr> previousExprSource = this->currentExprSource;
        bool clearQueryContext = this->currentQueryContext.empty();
        // this->currentExprSource = nullptr;
        std::string elemVarsDeclarationString = "";
        if (ctx->elemVarsDeclaration()){
            elemVarsDeclarationString = std::any_cast<std::string>(visit(ctx->elemVarsDeclaration()));
            // elemVarsDeclarationString = ctx->elemVarsDeclaration()->getText();
        }else{
            std::cout << "NO VARS DECLARATION:" << std::endl;
        }
        std::shared_ptr<MetaModel::Expr> queryExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));
        if (clearQueryContext) this->currentQueryContext.clear();
        this->currentExprSource = previousExprSource;

        std::cout << "AFTER VISITING QUERY EXPR: " << ctx->getText() << std::endl;
        std::cout << "CURRENT SOURCE EXPR: " << this->currentExprSource->getExpression() << std::endl;
        std::cout << "CURRENT SOURCE STR: " << this->currentExprSource->toString() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;

        std::cout << "elemVarsDeclarationString: " << elemVarsDeclarationString << std::endl;

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::CollectExpr>(ctx->getText(),
                                                     true,
                                                     MetaModel::Void::instance(),
                                                     true,
                                                     this->currentExprSource,
                                                     elemVarsDeclarationString,
                                                     queryExpr));
    }

    std::any visitRejectExpr(USEParser::RejectExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> previousExprSource = this->currentExprSource;
        bool clearQueryContext = this->currentQueryContext.empty();
        // this->currentExprSource = nullptr;
        std::string elemVarsDeclarationString = "";
        if (ctx->elemVarsDeclaration()){
            elemVarsDeclarationString = std::any_cast<std::string>(visit(ctx->elemVarsDeclaration()));
            // elemVarsDeclarationString = ctx->elemVarsDeclaration()->getText();
        }
        std::shared_ptr<MetaModel::Expr> queryExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));
        if (clearQueryContext) this->currentQueryContext.clear();
        this->currentExprSource = previousExprSource;

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::RejectExpr>(ctx->getText(),
                                                    true,
                                                    MetaModel::Void::instance(),
                                                    true,
                                                    this->currentExprSource,
                                                    elemVarsDeclarationString,
                                                    queryExpr));
    }

    std::any visitSelectExpr(USEParser::SelectExprContext *ctx) override {
        std::cout << "VISITING SELECT EXPR: " << ctx->getText() << std::endl;
        std::cout << "CURRENT SOURCE EXPR: " << this->currentExprSource->getExpression() << std::endl;
        std::cout << "CURRENT SOURCE STR: " << this->currentExprSource->toString() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;
        std::shared_ptr<MetaModel::Expr> previousExprSource = this->currentExprSource;
        bool clearQueryContext = this->currentQueryContext.empty();
        // this->currentExprSource = nullptr;
        std::string elemVarsDeclarationString = "";
        if (ctx->elemVarsDeclaration()){
            elemVarsDeclarationString = std::any_cast<std::string>(visit(ctx->elemVarsDeclaration()));
            // elemVarsDeclarationString = ctx->elemVarsDeclaration()->getText();
        }
        std::shared_ptr<MetaModel::Expr> queryExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));
        if (clearQueryContext) this->currentQueryContext.clear();
        this->currentExprSource = previousExprSource;

        std::cout << "AFTER VISITING QUERY EXPR: " << ctx->getText() << std::endl;
        std::cout << "CURRENT SOURCE EXPR: " << this->currentExprSource->getExpression() << std::endl;
        std::cout << "CURRENT TYPE: " << this->currentExprSource->getType()->toString() << std::endl;
        std::cout << "CURRENT SOURCE STR: " << this->currentExprSource->toString() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;

        std::cout << "elemVarsDeclarationString: " << elemVarsDeclarationString << std::endl;

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::SelectExpr>(ctx->getText(),
                                                    true,
                                                    this->currentExprSource->getType(),
                                                    true,
                                                    this->currentExprSource,
                                                    elemVarsDeclarationString,
                                                    queryExpr));
    }

    std::any visitExistsExpr(USEParser::ExistsExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> previousExprSource = this->currentExprSource;
        bool clearQueryContext = this->currentQueryContext.empty();
        // this->currentExprSource = nullptr;
        std::string elemVarsDeclarationString = "";
        if (ctx->elemVarsDeclaration()){
            elemVarsDeclarationString = std::any_cast<std::string>(visit(ctx->elemVarsDeclaration()));
            // elemVarsDeclarationString = ctx->elemVarsDeclaration()->getText();
        }
        std::shared_ptr<MetaModel::Expr> queryExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));
        if (clearQueryContext) this->currentQueryContext.clear();
        this->currentExprSource = previousExprSource;

        std::cout << "elemVarsDeclarationString: " << elemVarsDeclarationString << std::endl;

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::ExistsExpr>(ctx->getText(),
                                                    true,
                                                    MetaModel::Void::instance(),
                                                    true,
                                                    this->currentExprSource,
                                                    elemVarsDeclarationString,
                                                    queryExpr));
    }

    std::any visitForAllExpr(USEParser::ForAllExprContext *ctx) override {
        std::cout << "VISIT FOR ALL EXPR: " << ctx->getText() << std::endl;
        std::shared_ptr<MetaModel::Expr> previousExprSource = this->currentExprSource;
        bool clearQueryContext = this->currentQueryContext.empty();
        // this->currentExprSource = nullptr;
        std::string elemVarsDeclarationString = "";
        if (ctx->elemVarsDeclaration()){
            elemVarsDeclarationString = std::any_cast<std::string>(visit(ctx->elemVarsDeclaration()));
            // elemVarsDeclarationString = ctx->elemVarsDeclaration()->getText();
        }
        std::shared_ptr<MetaModel::Expr> queryExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));
        if (clearQueryContext) this->currentQueryContext.clear();
        this->currentExprSource = previousExprSource;

        std::cout << "elemVarsDeclarationString: " << elemVarsDeclarationString << std::endl;
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::ForAllExpr>(ctx->getText(),
                                                    true,
                                                    MetaModel::Void::instance(),
                                                    true,
                                                    this->currentExprSource,
                                                    elemVarsDeclarationString,
                                                    queryExpr));
    }

    std::any visitIsUniqueExpr(USEParser::IsUniqueExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> previousExprSource = this->currentExprSource;
        bool clearQueryContext = this->currentQueryContext.empty();
        // this->currentExprSource = nullptr;
        std::string elemVarsDeclarationString = "";
        if (ctx->elemVarsDeclaration()){
            elemVarsDeclarationString = ctx->elemVarsDeclaration()->getText();
        }
        std::shared_ptr<MetaModel::Expr> queryExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));
        if (clearQueryContext) this->currentQueryContext.clear();
        this->currentExprSource = previousExprSource;

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::IsUniqueExpr>(ctx->getText(),
                                                      true,
                                                      MetaModel::Void::instance(),
                                                      true,
                                                      this->currentExprSource,
                                                      elemVarsDeclarationString,
                                                      queryExpr));
    }

    std::any visitSortedByExpr(USEParser::SortedByExprContext *ctx) override {
        std::shared_ptr<MetaModel::Expr> previousExprSource = this->currentExprSource;
        bool clearQueryContext = this->currentQueryContext.empty();
        // this->currentExprSource = nullptr;
        std::string elemVarsDeclarationString = "";
        if (ctx->elemVarsDeclaration()){
            elemVarsDeclarationString = ctx->elemVarsDeclaration()->getText();
        }
        std::shared_ptr<MetaModel::Expr> queryExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));
        if (clearQueryContext) this->currentQueryContext.clear();
        this->currentExprSource = previousExprSource;

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::SortedByExpr>(ctx->getText(),
                                                      true,
                                                      MetaModel::Void::instance(),
                                                      true,
                                                      this->currentExprSource,
                                                      elemVarsDeclarationString,
                                                      queryExpr));
    }

    //TYPE EXPRESSIONS

    std::any visitTypeExpr(USEParser::TypeExprContext *ctx) override {
        return visit(ctx->typeExpression());
    }

    std::any visitOclIsTypeOfExpr(USEParser::OclIsTypeOfExprContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::OCLIsTypeOfExpr>(ctx->getText(), true, MetaModel::Void::instance(), this->currentPropertyCallIsArrow, this->currentExprSource, type));
    }

    std::any visitOclIsKindOfExpr(USEParser::OclIsKindOfExprContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::OCLIsKindOfExpr>(ctx->getText(), true, MetaModel::Void::instance(), this->currentPropertyCallIsArrow, this->currentExprSource, type));
    }

    std::any visitOclAsTypeExpr(USEParser::OclAsTypeExprContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::OCLAsTypeExpr>(ctx->getText(), true, MetaModel::Void::instance(), this->currentPropertyCallIsArrow, this->currentExprSource, type));
    }

    std::any visitSelectByTypeExpr(USEParser::SelectByTypeExprContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::SelectByTypeExpr>(ctx->getText(), true, MetaModel::Void::instance(), this->currentPropertyCallIsArrow, this->currentExprSource, type));
    }

    std::any visitSelectByKindExpr(USEParser::SelectByKindExprContext *ctx) override {
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::SelectByKindExpr>(ctx->getText(), true, MetaModel::Void::instance(), this->currentPropertyCallIsArrow, this->currentExprSource, type));
    }

    //OPERATION EXPRESSIONS

    std::any visitOperationExpr(USEParser::OperationExprContext *ctx) override {
        return visit(ctx->operationExpression());
    }

    std::any visitOperationExpression(USEParser::OperationExpressionContext *ctx) override {
        std::cout << "VISIT OPERATION EXPR: " <<ctx->getText() << std::endl;
        if(this->currentExprSource){
            //if currentExprSource si query, (at least a select), use its source
            std::cout << "CURRENT SOURCE EXPR: " << this->currentExprSource->getExpression() << std::endl;
            // std::cout << "CURRENT SOURCE TYPE: " << this->currentExprSource->getType()->toString() << std::endl;
            // std::cout << "CURRENT SOURCE STR: " << this->currentExprSource->toString() << std::endl;
        } else {
            std::cout << "NO CURRENT EXPR" << std::endl;
        }

        if(ctx->getText() == "valor"){
            // this->currentExprSource = nullptr;
            std::cout << "VALOR" << std::endl;

        }
        std::shared_ptr<MetaModel::Expr> resultExpression = nullptr;
        // If no source expression is given, it is either a variable or a reference to expression determined by context.
        // In the latter case we use the context as source expression and proceed as if it has been given explicitly.

        if(this->currentExprSource){
            // First we check if the source isComplex. If it is, we can create a generic operation expression, as the source may not be fully generated
            // if(this->currentExprSource->isComplexExpr()){
            //     resultExpression = buildGenericOperationExpr(ctx);
            // }else{
            resultExpression = std::any_cast< std::shared_ptr<MetaModel::Expr>>(visitOperationExpressionWithSource(ctx));
            // }
        } else {
            if(!ctx->LPAREN()){
                // Check if it's a variable given in the context (defined or implicit "self" in a constraint, implicit "self" in a pre/postCondition defined inside a class)
                if(!this->currentQueryContext.empty()){
                    std::cout << "CURRENT QUERY CONTEXT" << std::endl;
                    if (auto variablePair = this->currentQueryContext.find(ctx->ID()->getText()); variablePair != this->currentQueryContext.end()){
                        auto variable = variablePair->second;
                        resultExpression = buildVariableExpr(variable->getName(), variable->getTypePtr());
                        std::cout << "VARIABLE EXPR: " << resultExpression->getExpression() << std::endl;
                        std::cout << "VARIABLE Type: " << resultExpression->getType()->toString() << std::endl;
                    }
                }else if(this->currentConstraintContext){
                    std::cout << "CURRENT CONSTRAINT CONTEXT" << std::endl;

                    if(auto variable = this->currentConstraintContext->getVariable(ctx->ID()->getText()); variable){
                        resultExpression = buildVariableExpr(variable->getName(), variable->getTypePtr());
                    }
                }else if(this->currentClassContext){
                    std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;
                    if(ctx->ID()->getText() == "self"){
                        std::cout << "its self" << std::endl;
                        resultExpression = buildVariableExpr("self", std::dynamic_pointer_cast<MetaModel::MetaType>(this->currentClassContext));
                    }
                }
            }
            if(!resultExpression){
                // Check if the context is implicitly the source (e.g: context person inv Invariant: age > 0, here it refers to (implicit)self.age)
                std::shared_ptr<MetaModel::MetaVariable> sourceVariable = nullptr;
                if(!this->currentQueryContext.empty()){
                    if (auto variablePair = this->currentQueryContext.find(ctx->ID()->getText()); variablePair != this->currentQueryContext.end()){
                        sourceVariable = variablePair->second;
                    }
                }else if(this->currentConstraintContext){
                    sourceVariable = this->currentConstraintContext->getVariables().begin()->second;
                }else if(this->currentClassContext){
                    sourceVariable = std::make_shared<MetaModel::MetaVariable>("self", std::dynamic_pointer_cast<MetaModel::MetaType>(this->currentClassContext));
                }

                if(sourceVariable){
                    this->currentExprSource = buildVariableExpr(sourceVariable->getName(), sourceVariable->getTypePtr());
                    // Call function that generates a expression that has a source
                    resultExpression = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visitOperationExpressionWithSource(ctx));
                }else{
                    throw std::invalid_argument("Undefined " + std::string(ctx->LPAREN() ? "operation" : "variable") + " with name: '" + ctx->ID()->getText() + "'");
                }
            }
        }
        return resultExpression;
    }

    std::any visitOperationExpressionWithSource(USEParser::OperationExpressionContext *ctx) {
        std::cout << "VISITING: " <<ctx->getText() << " WITH SOURCE: " << this->currentExprSource->getExpression() << std::endl;
        // std::cout << "CURRENT SOURCE TYPE: " << this->currentExprSource->getType()->toString() << std::endl;
        std::cout << "CURRENT CLASS CONTEXT: " << this->currentClassContext->getName() << std::endl;
        if(this->currentExprSource->getExpression() == "self"){
            std::cout << "TYPE: " << this->currentExprSource->getType()->toString() << std::endl;
        }


        std::shared_ptr<MetaModel::Expr> resultExpression = nullptr;
        std::shared_ptr<MetaModel::MetaType> srcType = this->currentExprSource->getType();

        if(auto selectSource = std::dynamic_pointer_cast<MetaModel::SelectExpr>(this->currentExprSource)){
            srcType = selectSource->getSource()->getType();
        }

        if(auto srcVoidType = std::dynamic_pointer_cast<MetaModel::Void>(srcType) || !srcType){
            if(!this->currentExprSource->isComplexExpr()){
                throw std::invalid_argument("'" + ctx->getText() +"' cannot be applied to source expression '"
                                            + this->currentExprSource->getExpression() + "', since the latter doesn't evaluate to something with a type.");
            }else{
                resultExpression = buildStandardOperationExpr(ctx);
            }
        } else if(auto srcMetaClassType = std::dynamic_pointer_cast<MetaModel::MetaClass>(srcType)){

            if(!this->currentPropertyCallIsArrow || std::dynamic_pointer_cast<MetaModel::SelectExpr>(this->currentExprSource)){
                // Either an AttributeNavigationExpr, a NavigationExpr, a ObjectOperationExpr a standard operation. As of now, we only care for AttributeNavigations
                if(ctx->LPAREN()){
                    // Operation expression
                    std::shared_ptr<MetaModel::MetaOperation> metaOperation= srcMetaClassType->getOperation(ctx->ID()->getText());

                    if(metaOperation){
                        resultExpression = buildObjectOperationExpr(ctx, metaOperation, srcMetaClassType);
                    } else {
                        resultExpression = buildStandardOperationExpr(ctx);
                    }
                } else {
                    if(ctx->RBRACK().size() >= 1){
                        // Navigation expression with explicit rolename
                        std::shared_ptr<MetaModel::MetaAssociationEnd> dst = srcMetaClassType->getAssociationEnd(ctx->ID()->getText());
                        resultExpression = buildNavigationExpr(ctx, dst);

                    } else {
                        std::shared_ptr<MetaModel::MetaAttribute> metaAttribute = srcMetaClassType->getAttribute(ctx->ID()->getText());

                        if(metaAttribute){
                            // AttributteNavigation expression
                            resultExpression = buildAttributeNavigationExpr(metaAttribute);

                        } else {
                            std::cout << "TRY TO GET DST FROM: " << srcMetaClassType->toString() << std::endl;

                            std::shared_ptr<MetaModel::MetaAssociationEnd> dst = srcMetaClassType->getAssociationEnd(ctx->ID()->getText());
                            if(!dst){
                                std::cout << "NOT AN ASSOC END FROM A CLASS"<< std::endl;
                                if(auto srcMetaAssocClassType = std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(srcType)){
                                    dst = srcMetaAssocClassType->MetaModel::MetaAssociation::getAssociationEnd(ctx->ID()->getText());
                                }else{
                                    std::cout << "???????" << std::endl;
                                }
                            }
                            if(dst){
                                std::cout << "NAVIGATION " << std::endl;
                                resultExpression = buildNavigationExpr(ctx, dst);
                            } else {
                                std::string associationClassifierName = ctx->ID()->getText();
                                associationClassifierName[0] = std::toupper(associationClassifierName[0]);
                                std::shared_ptr<MetaModel::MetaAssociation> assocClassifier = this->model->getAssociation(associationClassifierName);
                                if (!assocClassifier){
                                    assocClassifier = this->model->getAssociationClass(associationClassifierName);
                                }
                                if (assocClassifier) {
                                    std::cout << "NAVIGATION WITH CLASSIFIER SOURCE: " << ctx->getText() << std::endl;
                                    resultExpression = buildClassifierNavigationExpr(ctx, assocClassifier, srcType);
                                }else{
                                    std::cout << "STANDARD " << std::endl;
                                    resultExpression = buildStandardOperationExpr(ctx);
                                }
                            }
                        }
                    }
                }
            }else{
                // Set operation on single object resulting from navigation over associations with multiplicity 0 or 1
                if(auto srcExprNavigation = std::dynamic_pointer_cast<MetaModel::NavigationExpr>(this->currentExprSource)){
                    resultExpression = buildObjectAsSetExpr(ctx, srcType);

                } else {
                    throw std::invalid_argument("An arrow operation treating a single object as a set may only be applied, "
                                                "if the object results from a navigation to an association end with multiplicity 0..1.");
                }
            }
        } else if(auto srcSimpleType = std::dynamic_pointer_cast<MetaModel::SimpleType>(srcType)){
            resultExpression = buildStandardOperationExpr(ctx);

        } else if(auto srcCollectionType = std::dynamic_pointer_cast<MetaModel::CollectionType>(srcType)){
            // Either a standard operation over a collection or a shorthand for collect
            if(this->currentPropertyCallIsArrow){
                resultExpression = buildStandardOperationExpr(ctx);
            }else{
                resultExpression = buildCollectExpr(ctx);
            }
        } else if(auto srcTupleType = std::dynamic_pointer_cast<MetaModel::TupleType>(srcType)){
            if(this->currentPropertyCallIsArrow){
                throw std::invalid_argument("Collection operation not applicable to tuple type.");
            }else{
                // Either a TupleType navigation or a standard operation over a TupleType
                if(auto tuplePart = srcTupleType->getElement(ctx->ID()->getText())){
                    resultExpression = buildTupleSelectOperationExpr(tuplePart->getName(), tuplePart->getTypePtr());
                }else{
                    resultExpression = buildStandardOperationExpr(ctx);
                }
            }
        }
        return resultExpression;
    }

    std::shared_ptr<MetaModel::Expr> buildVariableExpr(std::string variableName, std::shared_ptr<MetaModel::MetaType> variableType){
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::VariableExpr>(variableName, false, variableType,
                                                      this->currentPropertyCallIsArrow, this->currentExprSource, variableName));
    }

    std::shared_ptr<MetaModel::Expr> buildGenericOperationExpr(USEParser::OperationExpressionContext *ctx){
        std::cout << "BUILDING GENERIC OP" << std::endl;
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::OperationExpr>(ctx->getText(), true, MetaModel::Void::instance(),
                                                       this->currentPropertyCallIsArrow, this->currentExprSource));
    }

    std::shared_ptr<MetaModel::Expr> buildObjectOperationExpr(USEParser::OperationExpressionContext *ctx,
                                                              std::shared_ptr<MetaModel::MetaOperation> metaOperation,
                                                              std::shared_ptr<MetaModel::MetaClass> srcMetaClass){
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::ObjectOperationExpr>(ctx->getText(), true, metaOperation->getReturnTypePtr(),
                                                             this->currentPropertyCallIsArrow, this->currentExprSource, srcMetaClass));
    }

    std::shared_ptr<MetaModel::Expr> buildStandardOperationExpr(USEParser::OperationExpressionContext *ctx){
        // The type of standard operations depends on the operation, we ignore them so it can be void for now
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::StandardOperationExpr>(ctx->getText(), true, MetaModel::Void::instance(),
                                                               this->currentPropertyCallIsArrow, this->currentExprSource));
    }

    std::shared_ptr<MetaModel::Expr> buildAttributeNavigationExpr(std::shared_ptr<MetaModel::MetaAttribute> metaAttribute){
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::AttributeNavigationExpr>(metaAttribute->getName(), false, metaAttribute->getTypePtr(),
                                                                 this->currentPropertyCallIsArrow, this->currentExprSource, metaAttribute));
    }

    std::shared_ptr<MetaModel::Expr> buildNavigationExpr(USEParser::OperationExpressionContext *ctx,
                                                          std::shared_ptr<MetaModel::MetaAssociationEnd> dst){
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::NavigationExpr>(ctx->getText(), false, dst->getClassSharedPtr(),
                                                        this->currentPropertyCallIsArrow, this->currentExprSource, nullptr, dst));
    }

    std::shared_ptr<MetaModel::Expr> buildClassifierNavigationExpr(USEParser::OperationExpressionContext *ctx,
                                                                   std::shared_ptr<MetaModel::MetaAssociation> classifier,
                                                                   std::shared_ptr<MetaModel::MetaType> srcType){
        // For now we skip classifier navigations
        std::shared_ptr<MetaModel::MetaType> targetType = srcType;
        if (auto assocClass = std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(classifier)) {
            targetType = assocClass;
        }

        std::cout << "BUILDING CLASSIFIER NAVIGATION: " << ctx->getText() << " WITH TYPE: "<< targetType->toString() << std::endl;

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::NavigationExpr>(ctx->getText(), true, targetType,
                                                        this->currentPropertyCallIsArrow, this->currentExprSource, nullptr, nullptr));
    }

    std::shared_ptr<MetaModel::Expr> buildObjectAsSetExpr(USEParser::OperationExpressionContext *ctx,
                                                          std::shared_ptr<MetaModel::MetaType> srcType){
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::ObjectAsSetExpr>(ctx->getText(), true, srcType,
                                                         this->currentPropertyCallIsArrow, this->currentExprSource));
    }

    std::shared_ptr<MetaModel::Expr> buildCollectExpr(USEParser::OperationExpressionContext *ctx){
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::CollectExpr>(ctx->getText(), true, this->currentExprSource->getType(),
                                                     this->currentPropertyCallIsArrow, this->currentExprSource, "", nullptr));
    }

    std::shared_ptr<MetaModel::Expr> buildTupleSelectOperationExpr(std::string tuplePartName, std::shared_ptr<MetaModel::MetaType> tuplePartType){
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::TupleSelectOperationExpr>(
                tuplePartName, false, tuplePartType,
                this->currentPropertyCallIsArrow, this->currentExprSource));
    }

    //PRIMARY EXPRESSIONS

    std::any visitPrimaryExpr(USEParser::PrimaryExprContext *ctx) override {
        return visit(ctx->primaryExpression());
    }

    std::any visitEmptyPropertyCallExpr(USEParser::EmptyPropertyCallExprContext *ctx) override {
        return visit(ctx->propertyCall());
    }

    std::any visitParenthesizedExpr(USEParser::ParenthesizedExprContext *ctx) override {
        auto expr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()));

        expr->setHasParenthesis(true);

        return expr;
    }

    std::any visitAllInstancesExpr(USEParser::AllInstancesExprContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::AllInstancesExpr>(
                ctx->getText(), true, nullptr));
    }

    std::any visitByUseIdExpr(USEParser::ByUseIdExprContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::ByUseIdExpr>(
                ctx->getText(), true, nullptr));
    }

    std::any visitObjectReference(USEParser::ObjectReferenceContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::ObjectReferenceExpr>(
                ctx->getText(), true, nullptr, ctx->ID()->getText()));
    }

    // LITERAL EXPRESSIONS

    std::any visitLiteralExpr(USEParser::LiteralExprContext *ctx) override {
        // return std::make_shared<MetaModel::Expr>(ctx->getText(), true, MetaModel::Boolean::instance());

        return visit(ctx->literal());
    }

    std::any visitLiteralBooleanTrue(USEParser::LiteralBooleanTrueContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), false, MetaModel::Boolean::instance(), true));
    }

    std::any visitLiteralBooleanFalse(USEParser::LiteralBooleanFalseContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), false, MetaModel::Boolean::instance(), false));
    }

    std::any visitLiteralInteger(USEParser::LiteralIntegerContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), false, MetaModel::Integer::instance(), std::stoi(ctx->INT()->getText())));
    }

    std::any visitLiteralReal(USEParser::LiteralRealContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), false, MetaModel::Real::instance(), std::stod(ctx->REAL()->getText())));
    }

    std::any visitLiteralString(USEParser::LiteralStringContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), false, MetaModel::String::instance(), ctx->STRING()->getText()));
    }

    std::any visitLiteralEnum(USEParser::LiteralEnumContext *ctx) override {
        std::shared_ptr<MetaModel::MetaEnumElement> enumElement = nullptr;
        std::shared_ptr<MetaModel::MetaEnum> modelEnum = nullptr;
        auto modelEnumsIterator = model->getEnums().begin();

        while(!enumElement && modelEnumsIterator != model->getEnums().end()){
            modelEnum = modelEnumsIterator->second;
            enumElement = modelEnum->getElement(ctx->ID()->getText());

            modelEnumsIterator++;
        }

        if(!enumElement){
            throw std::invalid_argument("Undefined enumeration literal '" + ctx->ID()->getText() + "'.");
        }

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), false, modelEnum, enumElement));
    }

    std::any visitLiteralQualifiedEnum(USEParser::LiteralQualifiedEnumContext *ctx) override {
        std::shared_ptr<MetaModel::MetaEnum> modelEnum = model->getEnum(ctx->ID()[0]->getText());

        if(!modelEnum){
            throw std::invalid_argument("Undefined enumeration '" + ctx->ID()[0]->getText() + "'.");
        }

        std::shared_ptr<MetaModel::MetaEnumElement> enumElement = modelEnum->getElement(ctx->ID()[1]->getText());

        if(!enumElement){
            throw std::invalid_argument("Undefined enumeration literal '" + ctx->ID()[1]->getText() + "'.");
        }

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), false, modelEnum, enumElement));
    }

    std::any visitLiteralTuple(USEParser::LiteralTupleContext *ctx) override {
        // Ignored for now
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), true, std::make_shared<MetaModel::TupleType>(nullptr), nullptr));
    }

    std::any visitLiteralUndefined(USEParser::LiteralUndefinedContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), true, nullptr, "undefined"));
    }

    std::any visitLiteralUnlimitedNatural(USEParser::LiteralUnlimitedNaturalContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), true, nullptr, "*"));
    }

    std::any visitLiteralEmptyCollection(USEParser::LiteralEmptyCollectionContext *ctx) override {
        return visit(ctx->emptyCollectionLiteral());
    }

    std::any visitEmptyCollectionLiteral(USEParser::EmptyCollectionLiteralContext *ctx) override {
        auto collectionType = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->collectionType()));
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), true, collectionType, nullptr));
    }

    // LITETAL COLLECTION EXPRESSIONS
    // Ignored for now, we generate a dummy genereic collection LiteralExpr and dont visit the possible collectionLiterals

    std::any visitLiteralCollection(USEParser::LiteralCollectionContext *ctx) override {
        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LiteralExpr>(
                ctx->getText(), true, std::make_shared<MetaModel::CollectionType>(true, true, 1, MetaModel::Integer::instance()), nullptr));
    }


    std::any visitConditionalExpr(USEParser::ConditionalExprContext *ctx) override {
        return visit(ctx->conditionalExpression());
    }

    // CONDITIONAL EXPRESSION

    std::any visitConditionalExpression(USEParser::ConditionalExpressionContext *ctx) override {
        auto ifExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()[0]));
        auto thenExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()[1]));
        auto elseExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()[2]));
        std::cout << "VISIT CONDITIONAL EXPR: " << ctx->getText() << std::endl;

        std::cout << "THEN EXPR: " << thenExpr->toString() << std::endl;
        std::cout << "THEN EXPR TYPE: " << thenExpr->getType()->toString() << std::endl;

        std::cout << "ELSE EXPR: " << elseExpr->toString() << std::endl;
        std::cout << "ELSE EXPR TYPE: " << elseExpr->getType()->toString() << std::endl;

        if( !std::dynamic_pointer_cast<MetaModel::Void>(thenExpr->getType()) &&
            !std::dynamic_pointer_cast<MetaModel::Void>(elseExpr->getType()) &&
            !thenExpr->getType()->equals(*elseExpr->getType())){
            bool numericCompatible = (std::dynamic_pointer_cast<MetaModel::Integer>(thenExpr->getType()) && std::dynamic_pointer_cast<MetaModel::Real>(elseExpr->getType())) ||
                                     (std::dynamic_pointer_cast<MetaModel::Real>(thenExpr->getType()) && std::dynamic_pointer_cast<MetaModel::Integer>(elseExpr->getType()));
            if(!numericCompatible){
                throw std::invalid_argument("Branches of ConditionalExpr have different types, found '" + thenExpr->getType()->toString() + "' and '" + elseExpr->getType()->toString() + "'.");
            }
        }

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::ConditionalExpr>(
                ctx->getText(), true, thenExpr->getType(), ifExpr, thenExpr, elseExpr));
    }

    //LET EXPRESSION

    std::any visitLetExpr(USEParser::LetExprContext *ctx) override {
        return visit(ctx->letExpression());
    }

    std::any visitLetExpression(USEParser::LetExpressionContext *ctx) override {
        // We return a dummy to ignore the visit of the inExpression, which requires to handle the LetExpr context for the variable

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LetExpr>(
                ctx->getText(), true, nullptr, ctx->ID()->getText(), nullptr, nullptr, nullptr));

        auto varExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()[0]));
        auto inExpr = std::any_cast<std::shared_ptr<MetaModel::Expr>>(visit(ctx->expression()[1]));
        std::shared_ptr<MetaModel::MetaType> varType = nullptr;

        if(ctx->type()){
            varType = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));
        }else{
            varType = varExpr->getType();
        }

        // A check should be made to see if varExpr type conforms to declared varType

        return std::dynamic_pointer_cast<MetaModel::Expr>(
            std::make_shared<MetaModel::LetExpr>(
                ctx->getText(), true, inExpr->getType(), ctx->ID()->getText(), varType, varExpr, inExpr));
    }

};
