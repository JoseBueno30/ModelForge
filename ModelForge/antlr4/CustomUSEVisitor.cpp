#include "generated/USEBaseVisitor.h"
#include "metamodel/MetaModel.h"
#include <QDebug>
#include <any>

class CustomUSEVisitor : public USEBaseVisitor{
public:
    std::shared_ptr<MetaModel::MetaModel> model;

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

        // Add attributes and set generalization  relationships. The names of all classes are known at this point
        for (auto classElem : classElements) {
            visit(classElem);
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





        return nullptr;
    }

    std::any visitAttributeDefinition(USEParser::AttributeDefinitionContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::shared_ptr<MetaModel::MetaType> type = std::any_cast<std::shared_ptr<MetaModel::MetaType>>(visit(ctx->type()));

        //En el constructor y el setter de attribute comprobar que type no sea void
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
        return visitChildren(ctx);
    }

    std::any visitTuplePart(USEParser::TuplePartContext *ctx) override {
        return visitChildren(ctx);
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
};
