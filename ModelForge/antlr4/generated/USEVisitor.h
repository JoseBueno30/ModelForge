 
/*
 * HEADER TEST
 */



// Generated from c:/Users/Victor/Documents/ModelForge/USE_grammar/USE.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "USEParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by USEParser.
 */
class  USEVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by USEParser.
   */
    virtual std::any visitModel(USEParser::ModelContext *context) = 0;

    virtual std::any visitEnum(USEParser::EnumContext *context) = 0;

    virtual std::any visitClass(USEParser::ClassContext *context) = 0;

    virtual std::any visitAssociation(USEParser::AssociationContext *context) = 0;

    virtual std::any visitAssociationClass(USEParser::AssociationClassContext *context) = 0;

    virtual std::any visitConstraints(USEParser::ConstraintsContext *context) = 0;

    virtual std::any visitEnumTypeDefinition(USEParser::EnumTypeDefinitionContext *context) = 0;

    virtual std::any visitClassDefinition(USEParser::ClassDefinitionContext *context) = 0;

    virtual std::any visitAssociationClassDefinition(USEParser::AssociationClassDefinitionContext *context) = 0;

    virtual std::any visitAttributeDefinition(USEParser::AttributeDefinitionContext *context) = 0;

    virtual std::any visitInitDefinition(USEParser::InitDefinitionContext *context) = 0;

    virtual std::any visitDerivedDefinition(USEParser::DerivedDefinitionContext *context) = 0;

    virtual std::any visitOperationDefinition(USEParser::OperationDefinitionContext *context) = 0;

    virtual std::any visitSimpleAssociation(USEParser::SimpleAssociationContext *context) = 0;

    virtual std::any visitAggregation(USEParser::AggregationContext *context) = 0;

    virtual std::any visitComposition(USEParser::CompositionContext *context) = 0;

    virtual std::any visitAssociationEnd(USEParser::AssociationEndContext *context) = 0;

    virtual std::any visitMultiplicity(USEParser::MultiplicityContext *context) = 0;

    virtual std::any visitMultiplicityRange(USEParser::MultiplicityRangeContext *context) = 0;

    virtual std::any visitMultiplicitySpec(USEParser::MultiplicitySpecContext *context) = 0;

    virtual std::any visitInvariantDefinition(USEParser::InvariantDefinitionContext *context) = 0;

    virtual std::any visitPrePostDefinition(USEParser::PrePostDefinitionContext *context) = 0;

    virtual std::any visitInvariant(USEParser::InvariantContext *context) = 0;

    virtual std::any visitInvariantClause(USEParser::InvariantClauseContext *context) = 0;

    virtual std::any visitPrePost(USEParser::PrePostContext *context) = 0;

    virtual std::any visitPreCondition(USEParser::PreConditionContext *context) = 0;

    virtual std::any visitPostCondition(USEParser::PostConditionContext *context) = 0;

    virtual std::any visitStateMachine(USEParser::StateMachineContext *context) = 0;

    virtual std::any visitStateDefinition(USEParser::StateDefinitionContext *context) = 0;

    virtual std::any visitTransitionDefinition(USEParser::TransitionDefinitionContext *context) = 0;

    virtual std::any visitExpressionOnly(USEParser::ExpressionOnlyContext *context) = 0;

    virtual std::any visitOclExpression(USEParser::OclExpressionContext *context) = 0;

    virtual std::any visitLogicalExpr(USEParser::LogicalExprContext *context) = 0;

    virtual std::any visitConditionalExpr(USEParser::ConditionalExprContext *context) = 0;

    virtual std::any visitLambdaExpr(USEParser::LambdaExprContext *context) = 0;

    virtual std::any visitLetExpr(USEParser::LetExprContext *context) = 0;

    virtual std::any visitLambdaExpression(USEParser::LambdaExpressionContext *context) = 0;

    virtual std::any visitLetExpression(USEParser::LetExpressionContext *context) = 0;

    virtual std::any visitAndExpr(USEParser::AndExprContext *context) = 0;

    virtual std::any visitEqualityExpr(USEParser::EqualityExprContext *context) = 0;

    virtual std::any visitXorExpr(USEParser::XorExprContext *context) = 0;

    virtual std::any visitImpliesExpr(USEParser::ImpliesExprContext *context) = 0;

    virtual std::any visitOrExpr(USEParser::OrExprContext *context) = 0;

    virtual std::any visitParamList(USEParser::ParamListContext *context) = 0;

    virtual std::any visitIdList(USEParser::IdListContext *context) = 0;

    virtual std::any visitVariableDeclaration(USEParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitEqualExpr(USEParser::EqualExprContext *context) = 0;

    virtual std::any visitRelationalExpr(USEParser::RelationalExprContext *context) = 0;

    virtual std::any visitNotEqualExpr(USEParser::NotEqualExprContext *context) = 0;

    virtual std::any visitLessThanOrEqualExpr(USEParser::LessThanOrEqualExprContext *context) = 0;

    virtual std::any visitGreaterThanExpr(USEParser::GreaterThanExprContext *context) = 0;

    virtual std::any visitAdditiveExpr(USEParser::AdditiveExprContext *context) = 0;

    virtual std::any visitLessThanExpr(USEParser::LessThanExprContext *context) = 0;

    virtual std::any visitGreaterThanOrEqualExpr(USEParser::GreaterThanOrEqualExprContext *context) = 0;

    virtual std::any visitAdditionExpr(USEParser::AdditionExprContext *context) = 0;

    virtual std::any visitSubtractionExpr(USEParser::SubtractionExprContext *context) = 0;

    virtual std::any visitFactorExpr(USEParser::FactorExprContext *context) = 0;

    virtual std::any visitDivisionExpr(USEParser::DivisionExprContext *context) = 0;

    virtual std::any visitMultiplicationExpr(USEParser::MultiplicationExprContext *context) = 0;

    virtual std::any visitUnaryExpr(USEParser::UnaryExprContext *context) = 0;

    virtual std::any visitNotExpr(USEParser::NotExprContext *context) = 0;

    virtual std::any visitMinusExpr(USEParser::MinusExprContext *context) = 0;

    virtual std::any visitPlusExpr(USEParser::PlusExprContext *context) = 0;

    virtual std::any visitPostfixExpr(USEParser::PostfixExprContext *context) = 0;

    virtual std::any visitPrimaryExpr(USEParser::PrimaryExprContext *context) = 0;

    virtual std::any visitPropertyCallExpr(USEParser::PropertyCallExprContext *context) = 0;

    virtual std::any visitLiteralExpr(USEParser::LiteralExprContext *context) = 0;

    virtual std::any visitObjectReferenceExpr(USEParser::ObjectReferenceExprContext *context) = 0;

    virtual std::any visitEmptyPropertyCallExpr(USEParser::EmptyPropertyCallExprContext *context) = 0;

    virtual std::any visitParenthesizedExpr(USEParser::ParenthesizedExprContext *context) = 0;

    virtual std::any visitAllInstancesExpr(USEParser::AllInstancesExprContext *context) = 0;

    virtual std::any visitByUseIdExpr(USEParser::ByUseIdExprContext *context) = 0;

    virtual std::any visitObjectReference(USEParser::ObjectReferenceContext *context) = 0;

    virtual std::any visitQueryExpr(USEParser::QueryExprContext *context) = 0;

    virtual std::any visitIterateExpr(USEParser::IterateExprContext *context) = 0;

    virtual std::any visitOperationExpr(USEParser::OperationExprContext *context) = 0;

    virtual std::any visitTypeExpr(USEParser::TypeExprContext *context) = 0;

    virtual std::any visitInStateExpr(USEParser::InStateExprContext *context) = 0;

    virtual std::any visitSelectExpr(USEParser::SelectExprContext *context) = 0;

    virtual std::any visitRejectExpr(USEParser::RejectExprContext *context) = 0;

    virtual std::any visitCollectExpr(USEParser::CollectExprContext *context) = 0;

    virtual std::any visitExistsExpr(USEParser::ExistsExprContext *context) = 0;

    virtual std::any visitForAllExpr(USEParser::ForAllExprContext *context) = 0;

    virtual std::any visitIsUniqueExpr(USEParser::IsUniqueExprContext *context) = 0;

    virtual std::any visitSortedByExpr(USEParser::SortedByExprContext *context) = 0;

    virtual std::any visitIterateExpression(USEParser::IterateExpressionContext *context) = 0;

    virtual std::any visitOperationExpression(USEParser::OperationExpressionContext *context) = 0;

    virtual std::any visitInStateExpression(USEParser::InStateExpressionContext *context) = 0;

    virtual std::any visitOclAsTypeExpr(USEParser::OclAsTypeExprContext *context) = 0;

    virtual std::any visitOclIsKindOfExpr(USEParser::OclIsKindOfExprContext *context) = 0;

    virtual std::any visitOclIsTypeOfExpr(USEParser::OclIsTypeOfExprContext *context) = 0;

    virtual std::any visitSelectByTypeExpr(USEParser::SelectByTypeExprContext *context) = 0;

    virtual std::any visitSelectByKindExpr(USEParser::SelectByKindExprContext *context) = 0;

    virtual std::any visitElemVarsDeclaration(USEParser::ElemVarsDeclarationContext *context) = 0;

    virtual std::any visitVariableInitialization(USEParser::VariableInitializationContext *context) = 0;

    virtual std::any visitConditionalExpression(USEParser::ConditionalExpressionContext *context) = 0;

    virtual std::any visitLiteralBooleanTrue(USEParser::LiteralBooleanTrueContext *context) = 0;

    virtual std::any visitLiteralBooleanFalse(USEParser::LiteralBooleanFalseContext *context) = 0;

    virtual std::any visitLiteralInteger(USEParser::LiteralIntegerContext *context) = 0;

    virtual std::any visitLiteralReal(USEParser::LiteralRealContext *context) = 0;

    virtual std::any visitLiteralString(USEParser::LiteralStringContext *context) = 0;

    virtual std::any visitLiteralEnum(USEParser::LiteralEnumContext *context) = 0;

    virtual std::any visitLiteralQualifiedEnum(USEParser::LiteralQualifiedEnumContext *context) = 0;

    virtual std::any visitLiteralCollection(USEParser::LiteralCollectionContext *context) = 0;

    virtual std::any visitLiteralEmptyCollection(USEParser::LiteralEmptyCollectionContext *context) = 0;

    virtual std::any visitLiteralUndefined(USEParser::LiteralUndefinedContext *context) = 0;

    virtual std::any visitLiteralTuple(USEParser::LiteralTupleContext *context) = 0;

    virtual std::any visitLiteralUnlimitedNatural(USEParser::LiteralUnlimitedNaturalContext *context) = 0;

    virtual std::any visitSetLiteral(USEParser::SetLiteralContext *context) = 0;

    virtual std::any visitSequenceLiteral(USEParser::SequenceLiteralContext *context) = 0;

    virtual std::any visitBagLiteral(USEParser::BagLiteralContext *context) = 0;

    virtual std::any visitOrderedSetLiteral(USEParser::OrderedSetLiteralContext *context) = 0;

    virtual std::any visitCollectionItem(USEParser::CollectionItemContext *context) = 0;

    virtual std::any visitEmptyCollectionLiteral(USEParser::EmptyCollectionLiteralContext *context) = 0;

    virtual std::any visitUndefinedLiteral(USEParser::UndefinedLiteralContext *context) = 0;

    virtual std::any visitTupleLiteral(USEParser::TupleLiteralContext *context) = 0;

    virtual std::any visitTypedTupleItem(USEParser::TypedTupleItemContext *context) = 0;

    virtual std::any visitUntypedTupleItem(USEParser::UntypedTupleItemContext *context) = 0;

    virtual std::any visitTypeSimple(USEParser::TypeSimpleContext *context) = 0;

    virtual std::any visitTypeCollection(USEParser::TypeCollectionContext *context) = 0;

    virtual std::any visitTypeTuple(USEParser::TypeTupleContext *context) = 0;

    virtual std::any visitTypeOnly(USEParser::TypeOnlyContext *context) = 0;

    virtual std::any visitSimpleType(USEParser::SimpleTypeContext *context) = 0;

    virtual std::any visitTypeSimpleCollection(USEParser::TypeSimpleCollectionContext *context) = 0;

    virtual std::any visitTypeSet(USEParser::TypeSetContext *context) = 0;

    virtual std::any visitTypeSequence(USEParser::TypeSequenceContext *context) = 0;

    virtual std::any visitTypeBag(USEParser::TypeBagContext *context) = 0;

    virtual std::any visitTypeOrderedSet(USEParser::TypeOrderedSetContext *context) = 0;

    virtual std::any visitTupleType(USEParser::TupleTypeContext *context) = 0;

    virtual std::any visitTuplePart(USEParser::TuplePartContext *context) = 0;

    virtual std::any visitRole(USEParser::RoleContext *context) = 0;

    virtual std::any visitRedefines(USEParser::RedefinesContext *context) = 0;

    virtual std::any visitSubsets(USEParser::SubsetsContext *context) = 0;


};

