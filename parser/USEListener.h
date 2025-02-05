 
/*
 * HEADER TEST
 */

package org.tzi.use.parser.use; 



// Generated from USE.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "USEParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by USEParser.
 */
class  USEListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterModel(USEParser::ModelContext *ctx) = 0;
  virtual void exitModel(USEParser::ModelContext *ctx) = 0;

  virtual void enterEnum(USEParser::EnumContext *ctx) = 0;
  virtual void exitEnum(USEParser::EnumContext *ctx) = 0;

  virtual void enterClass(USEParser::ClassContext *ctx) = 0;
  virtual void exitClass(USEParser::ClassContext *ctx) = 0;

  virtual void enterAssociation(USEParser::AssociationContext *ctx) = 0;
  virtual void exitAssociation(USEParser::AssociationContext *ctx) = 0;

  virtual void enterAssociationClass(USEParser::AssociationClassContext *ctx) = 0;
  virtual void exitAssociationClass(USEParser::AssociationClassContext *ctx) = 0;

  virtual void enterConstraints(USEParser::ConstraintsContext *ctx) = 0;
  virtual void exitConstraints(USEParser::ConstraintsContext *ctx) = 0;

  virtual void enterEnumTypeDefinition(USEParser::EnumTypeDefinitionContext *ctx) = 0;
  virtual void exitEnumTypeDefinition(USEParser::EnumTypeDefinitionContext *ctx) = 0;

  virtual void enterClassDefinition(USEParser::ClassDefinitionContext *ctx) = 0;
  virtual void exitClassDefinition(USEParser::ClassDefinitionContext *ctx) = 0;

  virtual void enterAssociationClassDefinition(USEParser::AssociationClassDefinitionContext *ctx) = 0;
  virtual void exitAssociationClassDefinition(USEParser::AssociationClassDefinitionContext *ctx) = 0;

  virtual void enterAttributeDefinition(USEParser::AttributeDefinitionContext *ctx) = 0;
  virtual void exitAttributeDefinition(USEParser::AttributeDefinitionContext *ctx) = 0;

  virtual void enterInitDefinition(USEParser::InitDefinitionContext *ctx) = 0;
  virtual void exitInitDefinition(USEParser::InitDefinitionContext *ctx) = 0;

  virtual void enterDerivedDefinition(USEParser::DerivedDefinitionContext *ctx) = 0;
  virtual void exitDerivedDefinition(USEParser::DerivedDefinitionContext *ctx) = 0;

  virtual void enterOperationDefinition(USEParser::OperationDefinitionContext *ctx) = 0;
  virtual void exitOperationDefinition(USEParser::OperationDefinitionContext *ctx) = 0;

  virtual void enterSimpleAssociation(USEParser::SimpleAssociationContext *ctx) = 0;
  virtual void exitSimpleAssociation(USEParser::SimpleAssociationContext *ctx) = 0;

  virtual void enterAggregation(USEParser::AggregationContext *ctx) = 0;
  virtual void exitAggregation(USEParser::AggregationContext *ctx) = 0;

  virtual void enterComposition(USEParser::CompositionContext *ctx) = 0;
  virtual void exitComposition(USEParser::CompositionContext *ctx) = 0;

  virtual void enterAssociationEnd(USEParser::AssociationEndContext *ctx) = 0;
  virtual void exitAssociationEnd(USEParser::AssociationEndContext *ctx) = 0;

  virtual void enterMultiplicity(USEParser::MultiplicityContext *ctx) = 0;
  virtual void exitMultiplicity(USEParser::MultiplicityContext *ctx) = 0;

  virtual void enterMultiplicityRange(USEParser::MultiplicityRangeContext *ctx) = 0;
  virtual void exitMultiplicityRange(USEParser::MultiplicityRangeContext *ctx) = 0;

  virtual void enterMultiplicitySpec(USEParser::MultiplicitySpecContext *ctx) = 0;
  virtual void exitMultiplicitySpec(USEParser::MultiplicitySpecContext *ctx) = 0;

  virtual void enterConstraintDefinition(USEParser::ConstraintDefinitionContext *ctx) = 0;
  virtual void exitConstraintDefinition(USEParser::ConstraintDefinitionContext *ctx) = 0;

  virtual void enterInvariant(USEParser::InvariantContext *ctx) = 0;
  virtual void exitInvariant(USEParser::InvariantContext *ctx) = 0;

  virtual void enterInvariantClause(USEParser::InvariantClauseContext *ctx) = 0;
  virtual void exitInvariantClause(USEParser::InvariantClauseContext *ctx) = 0;

  virtual void enterPrePost(USEParser::PrePostContext *ctx) = 0;
  virtual void exitPrePost(USEParser::PrePostContext *ctx) = 0;

  virtual void enterPreCondition(USEParser::PreConditionContext *ctx) = 0;
  virtual void exitPreCondition(USEParser::PreConditionContext *ctx) = 0;

  virtual void enterPostCondition(USEParser::PostConditionContext *ctx) = 0;
  virtual void exitPostCondition(USEParser::PostConditionContext *ctx) = 0;

  virtual void enterStateMachine(USEParser::StateMachineContext *ctx) = 0;
  virtual void exitStateMachine(USEParser::StateMachineContext *ctx) = 0;

  virtual void enterStateDefinition(USEParser::StateDefinitionContext *ctx) = 0;
  virtual void exitStateDefinition(USEParser::StateDefinitionContext *ctx) = 0;

  virtual void enterTransitionDefinition(USEParser::TransitionDefinitionContext *ctx) = 0;
  virtual void exitTransitionDefinition(USEParser::TransitionDefinitionContext *ctx) = 0;

  virtual void enterExpressionOnly(USEParser::ExpressionOnlyContext *ctx) = 0;
  virtual void exitExpressionOnly(USEParser::ExpressionOnlyContext *ctx) = 0;

  virtual void enterLogicalExpr(USEParser::LogicalExprContext *ctx) = 0;
  virtual void exitLogicalExpr(USEParser::LogicalExprContext *ctx) = 0;

  virtual void enterConditionalExpr(USEParser::ConditionalExprContext *ctx) = 0;
  virtual void exitConditionalExpr(USEParser::ConditionalExprContext *ctx) = 0;

  virtual void enterLambdaExpr(USEParser::LambdaExprContext *ctx) = 0;
  virtual void exitLambdaExpr(USEParser::LambdaExprContext *ctx) = 0;

  virtual void enterLetExpr(USEParser::LetExprContext *ctx) = 0;
  virtual void exitLetExpr(USEParser::LetExprContext *ctx) = 0;

  virtual void enterLambdaExpression(USEParser::LambdaExpressionContext *ctx) = 0;
  virtual void exitLambdaExpression(USEParser::LambdaExpressionContext *ctx) = 0;

  virtual void enterLetExpression(USEParser::LetExpressionContext *ctx) = 0;
  virtual void exitLetExpression(USEParser::LetExpressionContext *ctx) = 0;

  virtual void enterAndExpr(USEParser::AndExprContext *ctx) = 0;
  virtual void exitAndExpr(USEParser::AndExprContext *ctx) = 0;

  virtual void enterEqualityExpr(USEParser::EqualityExprContext *ctx) = 0;
  virtual void exitEqualityExpr(USEParser::EqualityExprContext *ctx) = 0;

  virtual void enterXorExpr(USEParser::XorExprContext *ctx) = 0;
  virtual void exitXorExpr(USEParser::XorExprContext *ctx) = 0;

  virtual void enterImpliesExpr(USEParser::ImpliesExprContext *ctx) = 0;
  virtual void exitImpliesExpr(USEParser::ImpliesExprContext *ctx) = 0;

  virtual void enterOrExpr(USEParser::OrExprContext *ctx) = 0;
  virtual void exitOrExpr(USEParser::OrExprContext *ctx) = 0;

  virtual void enterParamList(USEParser::ParamListContext *ctx) = 0;
  virtual void exitParamList(USEParser::ParamListContext *ctx) = 0;

  virtual void enterIdList(USEParser::IdListContext *ctx) = 0;
  virtual void exitIdList(USEParser::IdListContext *ctx) = 0;

  virtual void enterVariableDeclaration(USEParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(USEParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterEqualExpr(USEParser::EqualExprContext *ctx) = 0;
  virtual void exitEqualExpr(USEParser::EqualExprContext *ctx) = 0;

  virtual void enterRelationalExpr(USEParser::RelationalExprContext *ctx) = 0;
  virtual void exitRelationalExpr(USEParser::RelationalExprContext *ctx) = 0;

  virtual void enterNotEqualExpr(USEParser::NotEqualExprContext *ctx) = 0;
  virtual void exitNotEqualExpr(USEParser::NotEqualExprContext *ctx) = 0;

  virtual void enterLessThanOrEqualExpr(USEParser::LessThanOrEqualExprContext *ctx) = 0;
  virtual void exitLessThanOrEqualExpr(USEParser::LessThanOrEqualExprContext *ctx) = 0;

  virtual void enterGreaterThanExpr(USEParser::GreaterThanExprContext *ctx) = 0;
  virtual void exitGreaterThanExpr(USEParser::GreaterThanExprContext *ctx) = 0;

  virtual void enterAdditiveExpr(USEParser::AdditiveExprContext *ctx) = 0;
  virtual void exitAdditiveExpr(USEParser::AdditiveExprContext *ctx) = 0;

  virtual void enterLessThanExpr(USEParser::LessThanExprContext *ctx) = 0;
  virtual void exitLessThanExpr(USEParser::LessThanExprContext *ctx) = 0;

  virtual void enterGreaterThanOrEqualExpr(USEParser::GreaterThanOrEqualExprContext *ctx) = 0;
  virtual void exitGreaterThanOrEqualExpr(USEParser::GreaterThanOrEqualExprContext *ctx) = 0;

  virtual void enterAdditionExpr(USEParser::AdditionExprContext *ctx) = 0;
  virtual void exitAdditionExpr(USEParser::AdditionExprContext *ctx) = 0;

  virtual void enterSubtractionExpr(USEParser::SubtractionExprContext *ctx) = 0;
  virtual void exitSubtractionExpr(USEParser::SubtractionExprContext *ctx) = 0;

  virtual void enterFactorExpr(USEParser::FactorExprContext *ctx) = 0;
  virtual void exitFactorExpr(USEParser::FactorExprContext *ctx) = 0;

  virtual void enterDivisionExpr(USEParser::DivisionExprContext *ctx) = 0;
  virtual void exitDivisionExpr(USEParser::DivisionExprContext *ctx) = 0;

  virtual void enterMultiplicationExpr(USEParser::MultiplicationExprContext *ctx) = 0;
  virtual void exitMultiplicationExpr(USEParser::MultiplicationExprContext *ctx) = 0;

  virtual void enterUnaryExpr(USEParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(USEParser::UnaryExprContext *ctx) = 0;

  virtual void enterNotExpr(USEParser::NotExprContext *ctx) = 0;
  virtual void exitNotExpr(USEParser::NotExprContext *ctx) = 0;

  virtual void enterMinusExpr(USEParser::MinusExprContext *ctx) = 0;
  virtual void exitMinusExpr(USEParser::MinusExprContext *ctx) = 0;

  virtual void enterPlusExpr(USEParser::PlusExprContext *ctx) = 0;
  virtual void exitPlusExpr(USEParser::PlusExprContext *ctx) = 0;

  virtual void enterPostfixExpr(USEParser::PostfixExprContext *ctx) = 0;
  virtual void exitPostfixExpr(USEParser::PostfixExprContext *ctx) = 0;

  virtual void enterPrimaryExpr(USEParser::PrimaryExprContext *ctx) = 0;
  virtual void exitPrimaryExpr(USEParser::PrimaryExprContext *ctx) = 0;

  virtual void enterPropertyCallExpr(USEParser::PropertyCallExprContext *ctx) = 0;
  virtual void exitPropertyCallExpr(USEParser::PropertyCallExprContext *ctx) = 0;

  virtual void enterLiteralExpr(USEParser::LiteralExprContext *ctx) = 0;
  virtual void exitLiteralExpr(USEParser::LiteralExprContext *ctx) = 0;

  virtual void enterObjectReferenceExpr(USEParser::ObjectReferenceExprContext *ctx) = 0;
  virtual void exitObjectReferenceExpr(USEParser::ObjectReferenceExprContext *ctx) = 0;

  virtual void enterEmptyPropertyCallExpr(USEParser::EmptyPropertyCallExprContext *ctx) = 0;
  virtual void exitEmptyPropertyCallExpr(USEParser::EmptyPropertyCallExprContext *ctx) = 0;

  virtual void enterParenthesizedExpr(USEParser::ParenthesizedExprContext *ctx) = 0;
  virtual void exitParenthesizedExpr(USEParser::ParenthesizedExprContext *ctx) = 0;

  virtual void enterAllInstancesExpr(USEParser::AllInstancesExprContext *ctx) = 0;
  virtual void exitAllInstancesExpr(USEParser::AllInstancesExprContext *ctx) = 0;

  virtual void enterByUseIdExpr(USEParser::ByUseIdExprContext *ctx) = 0;
  virtual void exitByUseIdExpr(USEParser::ByUseIdExprContext *ctx) = 0;

  virtual void enterObjectReference(USEParser::ObjectReferenceContext *ctx) = 0;
  virtual void exitObjectReference(USEParser::ObjectReferenceContext *ctx) = 0;

  virtual void enterQueryExpr(USEParser::QueryExprContext *ctx) = 0;
  virtual void exitQueryExpr(USEParser::QueryExprContext *ctx) = 0;

  virtual void enterIterateExpr(USEParser::IterateExprContext *ctx) = 0;
  virtual void exitIterateExpr(USEParser::IterateExprContext *ctx) = 0;

  virtual void enterOperationExpr(USEParser::OperationExprContext *ctx) = 0;
  virtual void exitOperationExpr(USEParser::OperationExprContext *ctx) = 0;

  virtual void enterTypeExpr(USEParser::TypeExprContext *ctx) = 0;
  virtual void exitTypeExpr(USEParser::TypeExprContext *ctx) = 0;

  virtual void enterInStateExpr(USEParser::InStateExprContext *ctx) = 0;
  virtual void exitInStateExpr(USEParser::InStateExprContext *ctx) = 0;

  virtual void enterSelectExpr(USEParser::SelectExprContext *ctx) = 0;
  virtual void exitSelectExpr(USEParser::SelectExprContext *ctx) = 0;

  virtual void enterRejectExpr(USEParser::RejectExprContext *ctx) = 0;
  virtual void exitRejectExpr(USEParser::RejectExprContext *ctx) = 0;

  virtual void enterCollectExpr(USEParser::CollectExprContext *ctx) = 0;
  virtual void exitCollectExpr(USEParser::CollectExprContext *ctx) = 0;

  virtual void enterExistsExpr(USEParser::ExistsExprContext *ctx) = 0;
  virtual void exitExistsExpr(USEParser::ExistsExprContext *ctx) = 0;

  virtual void enterForAllExpr(USEParser::ForAllExprContext *ctx) = 0;
  virtual void exitForAllExpr(USEParser::ForAllExprContext *ctx) = 0;

  virtual void enterIsUniqueExpr(USEParser::IsUniqueExprContext *ctx) = 0;
  virtual void exitIsUniqueExpr(USEParser::IsUniqueExprContext *ctx) = 0;

  virtual void enterSortedByExpr(USEParser::SortedByExprContext *ctx) = 0;
  virtual void exitSortedByExpr(USEParser::SortedByExprContext *ctx) = 0;

  virtual void enterIterateExpression(USEParser::IterateExpressionContext *ctx) = 0;
  virtual void exitIterateExpression(USEParser::IterateExpressionContext *ctx) = 0;

  virtual void enterOperationExpression(USEParser::OperationExpressionContext *ctx) = 0;
  virtual void exitOperationExpression(USEParser::OperationExpressionContext *ctx) = 0;

  virtual void enterInStateExpression(USEParser::InStateExpressionContext *ctx) = 0;
  virtual void exitInStateExpression(USEParser::InStateExpressionContext *ctx) = 0;

  virtual void enterOclAsTypeExpr(USEParser::OclAsTypeExprContext *ctx) = 0;
  virtual void exitOclAsTypeExpr(USEParser::OclAsTypeExprContext *ctx) = 0;

  virtual void enterOclIsKindOfExpr(USEParser::OclIsKindOfExprContext *ctx) = 0;
  virtual void exitOclIsKindOfExpr(USEParser::OclIsKindOfExprContext *ctx) = 0;

  virtual void enterOclIsTypeOfExpr(USEParser::OclIsTypeOfExprContext *ctx) = 0;
  virtual void exitOclIsTypeOfExpr(USEParser::OclIsTypeOfExprContext *ctx) = 0;

  virtual void enterSelectByTypeExpr(USEParser::SelectByTypeExprContext *ctx) = 0;
  virtual void exitSelectByTypeExpr(USEParser::SelectByTypeExprContext *ctx) = 0;

  virtual void enterSelectByKindExpr(USEParser::SelectByKindExprContext *ctx) = 0;
  virtual void exitSelectByKindExpr(USEParser::SelectByKindExprContext *ctx) = 0;

  virtual void enterElemVarsDeclaration(USEParser::ElemVarsDeclarationContext *ctx) = 0;
  virtual void exitElemVarsDeclaration(USEParser::ElemVarsDeclarationContext *ctx) = 0;

  virtual void enterVariableInitialization(USEParser::VariableInitializationContext *ctx) = 0;
  virtual void exitVariableInitialization(USEParser::VariableInitializationContext *ctx) = 0;

  virtual void enterConditionalExpression(USEParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(USEParser::ConditionalExpressionContext *ctx) = 0;

  virtual void enterLiteralBooleanTrue(USEParser::LiteralBooleanTrueContext *ctx) = 0;
  virtual void exitLiteralBooleanTrue(USEParser::LiteralBooleanTrueContext *ctx) = 0;

  virtual void enterLiteralBooleanFalse(USEParser::LiteralBooleanFalseContext *ctx) = 0;
  virtual void exitLiteralBooleanFalse(USEParser::LiteralBooleanFalseContext *ctx) = 0;

  virtual void enterLiteralInteger(USEParser::LiteralIntegerContext *ctx) = 0;
  virtual void exitLiteralInteger(USEParser::LiteralIntegerContext *ctx) = 0;

  virtual void enterLiteralReal(USEParser::LiteralRealContext *ctx) = 0;
  virtual void exitLiteralReal(USEParser::LiteralRealContext *ctx) = 0;

  virtual void enterLiteralString(USEParser::LiteralStringContext *ctx) = 0;
  virtual void exitLiteralString(USEParser::LiteralStringContext *ctx) = 0;

  virtual void enterLiteralEnum(USEParser::LiteralEnumContext *ctx) = 0;
  virtual void exitLiteralEnum(USEParser::LiteralEnumContext *ctx) = 0;

  virtual void enterLiteralQualifiedEnum(USEParser::LiteralQualifiedEnumContext *ctx) = 0;
  virtual void exitLiteralQualifiedEnum(USEParser::LiteralQualifiedEnumContext *ctx) = 0;

  virtual void enterLiteralCollection(USEParser::LiteralCollectionContext *ctx) = 0;
  virtual void exitLiteralCollection(USEParser::LiteralCollectionContext *ctx) = 0;

  virtual void enterLiteralEmptyCollection(USEParser::LiteralEmptyCollectionContext *ctx) = 0;
  virtual void exitLiteralEmptyCollection(USEParser::LiteralEmptyCollectionContext *ctx) = 0;

  virtual void enterLiteralUndefined(USEParser::LiteralUndefinedContext *ctx) = 0;
  virtual void exitLiteralUndefined(USEParser::LiteralUndefinedContext *ctx) = 0;

  virtual void enterLiteralTuple(USEParser::LiteralTupleContext *ctx) = 0;
  virtual void exitLiteralTuple(USEParser::LiteralTupleContext *ctx) = 0;

  virtual void enterLiteralUnlimitedNatural(USEParser::LiteralUnlimitedNaturalContext *ctx) = 0;
  virtual void exitLiteralUnlimitedNatural(USEParser::LiteralUnlimitedNaturalContext *ctx) = 0;

  virtual void enterSetLiteral(USEParser::SetLiteralContext *ctx) = 0;
  virtual void exitSetLiteral(USEParser::SetLiteralContext *ctx) = 0;

  virtual void enterSequenceLiteral(USEParser::SequenceLiteralContext *ctx) = 0;
  virtual void exitSequenceLiteral(USEParser::SequenceLiteralContext *ctx) = 0;

  virtual void enterBagLiteral(USEParser::BagLiteralContext *ctx) = 0;
  virtual void exitBagLiteral(USEParser::BagLiteralContext *ctx) = 0;

  virtual void enterOrderedSetLiteral(USEParser::OrderedSetLiteralContext *ctx) = 0;
  virtual void exitOrderedSetLiteral(USEParser::OrderedSetLiteralContext *ctx) = 0;

  virtual void enterCollectionItem(USEParser::CollectionItemContext *ctx) = 0;
  virtual void exitCollectionItem(USEParser::CollectionItemContext *ctx) = 0;

  virtual void enterEmptyCollectionLiteral(USEParser::EmptyCollectionLiteralContext *ctx) = 0;
  virtual void exitEmptyCollectionLiteral(USEParser::EmptyCollectionLiteralContext *ctx) = 0;

  virtual void enterUndefinedLiteral(USEParser::UndefinedLiteralContext *ctx) = 0;
  virtual void exitUndefinedLiteral(USEParser::UndefinedLiteralContext *ctx) = 0;

  virtual void enterTupleLiteral(USEParser::TupleLiteralContext *ctx) = 0;
  virtual void exitTupleLiteral(USEParser::TupleLiteralContext *ctx) = 0;

  virtual void enterTypedTupleItem(USEParser::TypedTupleItemContext *ctx) = 0;
  virtual void exitTypedTupleItem(USEParser::TypedTupleItemContext *ctx) = 0;

  virtual void enterUntypedTupleItem(USEParser::UntypedTupleItemContext *ctx) = 0;
  virtual void exitUntypedTupleItem(USEParser::UntypedTupleItemContext *ctx) = 0;

  virtual void enterTypeSimple(USEParser::TypeSimpleContext *ctx) = 0;
  virtual void exitTypeSimple(USEParser::TypeSimpleContext *ctx) = 0;

  virtual void enterTypeCollection(USEParser::TypeCollectionContext *ctx) = 0;
  virtual void exitTypeCollection(USEParser::TypeCollectionContext *ctx) = 0;

  virtual void enterTypeTuple(USEParser::TypeTupleContext *ctx) = 0;
  virtual void exitTypeTuple(USEParser::TypeTupleContext *ctx) = 0;

  virtual void enterTypeOnly(USEParser::TypeOnlyContext *ctx) = 0;
  virtual void exitTypeOnly(USEParser::TypeOnlyContext *ctx) = 0;

  virtual void enterSimpleType(USEParser::SimpleTypeContext *ctx) = 0;
  virtual void exitSimpleType(USEParser::SimpleTypeContext *ctx) = 0;

  virtual void enterTypeSimpleCollection(USEParser::TypeSimpleCollectionContext *ctx) = 0;
  virtual void exitTypeSimpleCollection(USEParser::TypeSimpleCollectionContext *ctx) = 0;

  virtual void enterTypeSet(USEParser::TypeSetContext *ctx) = 0;
  virtual void exitTypeSet(USEParser::TypeSetContext *ctx) = 0;

  virtual void enterTypeSequence(USEParser::TypeSequenceContext *ctx) = 0;
  virtual void exitTypeSequence(USEParser::TypeSequenceContext *ctx) = 0;

  virtual void enterTypeBag(USEParser::TypeBagContext *ctx) = 0;
  virtual void exitTypeBag(USEParser::TypeBagContext *ctx) = 0;

  virtual void enterTypeOrderedSet(USEParser::TypeOrderedSetContext *ctx) = 0;
  virtual void exitTypeOrderedSet(USEParser::TypeOrderedSetContext *ctx) = 0;

  virtual void enterTupleType(USEParser::TupleTypeContext *ctx) = 0;
  virtual void exitTupleType(USEParser::TupleTypeContext *ctx) = 0;

  virtual void enterTuplePart(USEParser::TuplePartContext *ctx) = 0;
  virtual void exitTuplePart(USEParser::TuplePartContext *ctx) = 0;


};

