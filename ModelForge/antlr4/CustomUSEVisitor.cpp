#include "generated/USEBaseVisitor.h"
#include "metamodel/MetaModel.h"
#include <QDebug>
#include <any>

class CustomUSEVisitor : public USEBaseVisitor{
public:
    std::shared_ptr<MetaModel::MetaModel> model;

    virtual antlrcpp::Any visitModel(USEParser::ModelContext *ctx) override {

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

    virtual std::any visitEnum(USEParser::EnumContext *ctx) override {
        return visit(ctx->enumTypeDefinition());
    }

    virtual std::any visitEnumTypeDefinition(USEParser::EnumTypeDefinitionContext *ctx) override {

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

    virtual std::any visitClassDefinition(USEParser::ClassDefinitionContext *ctx) override {
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

    virtual std::any visitAttributeDefinition(USEParser::AttributeDefinitionContext *ctx) override {
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

    virtual std::any visitInitDefinition(USEParser::InitDefinitionContext *ctx) override {
        return visit(ctx->expression());
    }

    virtual std::any visitDerivedDefinition(USEParser::DerivedDefinitionContext *ctx) override {
        return visit(ctx->expression());
    }

    virtual std::any visitOclExpression(USEParser::OclExpressionContext *ctx) override {

        return std::make_shared<MetaModel::OCLExpr>(ctx->getText());
    }
};
