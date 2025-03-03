 
/*
 * HEADER TEST
 */



// Generated from USE.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "USEListener.h"


/**
 * This class provides an empty implementation of USEListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  USEBaseListener : public USEListener {
public:

  virtual void enterModel(USEParser::ModelContext * /*ctx*/) override { }
  virtual void exitModel(USEParser::ModelContext * /*ctx*/) override { }

  virtual void enterEnum(USEParser::EnumContext * /*ctx*/) override { }
  virtual void exitEnum(USEParser::EnumContext * /*ctx*/) override { }

  virtual void enterClass(USEParser::ClassContext * /*ctx*/) override { }
  virtual void exitClass(USEParser::ClassContext * /*ctx*/) override { }

  virtual void enterAssociation(USEParser::AssociationContext * /*ctx*/) override { }
  virtual void exitAssociation(USEParser::AssociationContext * /*ctx*/) override { }

  virtual void enterAssociationClass(USEParser::AssociationClassContext * /*ctx*/) override { }
  virtual void exitAssociationClass(USEParser::AssociationClassContext * /*ctx*/) override { }

  virtual void enterConstraints(USEParser::ConstraintsContext * /*ctx*/) override { }
  virtual void exitConstraints(USEParser::ConstraintsContext * /*ctx*/) override { }

  virtual void enterEnumTypeDefinition(USEParser::EnumTypeDefinitionContext * /*ctx*/) override { }
  virtual void exitEnumTypeDefinition(USEParser::EnumTypeDefinitionContext * /*ctx*/) override { }

  virtual void enterClassDefinition(USEParser::ClassDefinitionContext * /*ctx*/) override { }
  virtual void exitClassDefinition(USEParser::ClassDefinitionContext * /*ctx*/) override { }

  virtual void enterAssociationClassDefinition(USEParser::AssociationClassDefinitionContext * /*ctx*/) override { }
  virtual void exitAssociationClassDefinition(USEParser::AssociationClassDefinitionContext * /*ctx*/) override { }

  virtual void enterAttributeDefinition(USEParser::AttributeDefinitionContext * /*ctx*/) override { }
  virtual void exitAttributeDefinition(USEParser::AttributeDefinitionContext * /*ctx*/) override { }

  virtual void enterInitDefinition(USEParser::InitDefinitionContext * /*ctx*/) override { }
  virtual void exitInitDefinition(USEParser::InitDefinitionContext * /*ctx*/) override { }

  virtual void enterDerivedDefinition(USEParser::DerivedDefinitionContext * /*ctx*/) override { }
  virtual void exitDerivedDefinition(USEParser::DerivedDefinitionContext * /*ctx*/) override { }

  virtual void enterOperationDefinition(USEParser::OperationDefinitionContext * /*ctx*/) override { }
  virtual void exitOperationDefinition(USEParser::OperationDefinitionContext * /*ctx*/) override { }

  virtual void enterSimpleAssociation(USEParser::SimpleAssociationContext * /*ctx*/) override { }
  virtual void exitSimpleAssociation(USEParser::SimpleAssociationContext * /*ctx*/) override { }

  virtual void enterAggregation(USEParser::AggregationContext * /*ctx*/) override { }
  virtual void exitAggregation(USEParser::AggregationContext * /*ctx*/) override { }

  virtual void enterComposition(USEParser::CompositionContext * /*ctx*/) override { }
  virtual void exitComposition(USEParser::CompositionContext * /*ctx*/) override { }

  virtual void enterAssociationEnd(USEParser::AssociationEndContext * /*ctx*/) override { }
  virtual void exitAssociationEnd(USEParser::AssociationEndContext * /*ctx*/) override { }

  virtual void enterMultiplicity(USEParser::MultiplicityContext * /*ctx*/) override { }
  virtual void exitMultiplicity(USEParser::MultiplicityContext * /*ctx*/) override { }

  virtual void enterMultiplicityRange(USEParser::MultiplicityRangeContext * /*ctx*/) override { }
  virtual void exitMultiplicityRange(USEParser::MultiplicityRangeContext * /*ctx*/) override { }

  virtual void enterMultiplicitySpec(USEParser::MultiplicitySpecContext * /*ctx*/) override { }
  virtual void exitMultiplicitySpec(USEParser::MultiplicitySpecContext * /*ctx*/) override { }

  virtual void enterConstraintDefinition(USEParser::ConstraintDefinitionContext * /*ctx*/) override { }
  virtual void exitConstraintDefinition(USEParser::ConstraintDefinitionContext * /*ctx*/) override { }

  virtual void enterInvariant(USEParser::InvariantContext * /*ctx*/) override { }
  virtual void exitInvariant(USEParser::InvariantContext * /*ctx*/) override { }

  virtual void enterInvariantClause(USEParser::InvariantClauseContext * /*ctx*/) override { }
  virtual void exitInvariantClause(USEParser::InvariantClauseContext * /*ctx*/) override { }

  virtual void enterPrePost(USEParser::PrePostContext * /*ctx*/) override { }
  virtual void exitPrePost(USEParser::PrePostContext * /*ctx*/) override { }

  virtual void enterPreCondition(USEParser::PreConditionContext * /*ctx*/) override { }
  virtual void exitPreCondition(USEParser::PreConditionContext * /*ctx*/) override { }

  virtual void enterPostCondition(USEParser::PostConditionContext * /*ctx*/) override { }
  virtual void exitPostCondition(USEParser::PostConditionContext * /*ctx*/) override { }

  virtual void enterStateMachine(USEParser::StateMachineContext * /*ctx*/) override { }
  virtual void exitStateMachine(USEParser::StateMachineContext * /*ctx*/) override { }

  virtual void enterStateDefinition(USEParser::StateDefinitionContext * /*ctx*/) override { }
  virtual void exitStateDefinition(USEParser::StateDefinitionContext * /*ctx*/) override { }

  virtual void enterTransitionDefinition(USEParser::TransitionDefinitionContext * /*ctx*/) override { }
  virtual void exitTransitionDefinition(USEParser::TransitionDefinitionContext * /*ctx*/) override { }

  virtual void enterExpressionOnly(USEParser::ExpressionOnlyContext * /*ctx*/) override { }
  virtual void exitExpressionOnly(USEParser::ExpressionOnlyContext * /*ctx*/) override { }

  virtual void enterLogicalExpr(USEParser::LogicalExprContext * /*ctx*/) override { }
  virtual void exitLogicalExpr(USEParser::LogicalExprContext * /*ctx*/) override { }

  virtual void enterConditionalExpr(USEParser::ConditionalExprContext * /*ctx*/) override { }
  virtual void exitConditionalExpr(USEParser::ConditionalExprContext * /*ctx*/) override { }

  virtual void enterLambdaExpr(USEParser::LambdaExprContext * /*ctx*/) override { }
  virtual void exitLambdaExpr(USEParser::LambdaExprContext * /*ctx*/) override { }

  virtual void enterLetExpr(USEParser::LetExprContext * /*ctx*/) override { }
  virtual void exitLetExpr(USEParser::LetExprContext * /*ctx*/) override { }

  virtual void enterLambdaExpression(USEParser::LambdaExpressionContext * /*ctx*/) override { }
  virtual void exitLambdaExpression(USEParser::LambdaExpressionContext * /*ctx*/) override { }

  virtual void enterLetExpression(USEParser::LetExpressionContext * /*ctx*/) override { }
  virtual void exitLetExpression(USEParser::LetExpressionContext * /*ctx*/) override { }

  virtual void enterAndExpr(USEParser::AndExprContext * /*ctx*/) override { }
  virtual void exitAndExpr(USEParser::AndExprContext * /*ctx*/) override { }

  virtual void enterEqualityExpr(USEParser::EqualityExprContext * /*ctx*/) override { }
  virtual void exitEqualityExpr(USEParser::EqualityExprContext * /*ctx*/) override { }

  virtual void enterXorExpr(USEParser::XorExprContext * /*ctx*/) override { }
  virtual void exitXorExpr(USEParser::XorExprContext * /*ctx*/) override { }

  virtual void enterImpliesExpr(USEParser::ImpliesExprContext * /*ctx*/) override { }
  virtual void exitImpliesExpr(USEParser::ImpliesExprContext * /*ctx*/) override { }

  virtual void enterOrExpr(USEParser::OrExprContext * /*ctx*/) override { }
  virtual void exitOrExpr(USEParser::OrExprContext * /*ctx*/) override { }

  virtual void enterParamList(USEParser::ParamListContext * /*ctx*/) override { }
  virtual void exitParamList(USEParser::ParamListContext * /*ctx*/) override { }

  virtual void enterIdList(USEParser::IdListContext * /*ctx*/) override { }
  virtual void exitIdList(USEParser::IdListContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(USEParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(USEParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterEqualExpr(USEParser::EqualExprContext * /*ctx*/) override { }
  virtual void exitEqualExpr(USEParser::EqualExprContext * /*ctx*/) override { }

  virtual void enterRelationalExpr(USEParser::RelationalExprContext * /*ctx*/) override { }
  virtual void exitRelationalExpr(USEParser::RelationalExprContext * /*ctx*/) override { }

  virtual void enterNotEqualExpr(USEParser::NotEqualExprContext * /*ctx*/) override { }
  virtual void exitNotEqualExpr(USEParser::NotEqualExprContext * /*ctx*/) override { }

  virtual void enterLessThanOrEqualExpr(USEParser::LessThanOrEqualExprContext * /*ctx*/) override { }
  virtual void exitLessThanOrEqualExpr(USEParser::LessThanOrEqualExprContext * /*ctx*/) override { }

  virtual void enterGreaterThanExpr(USEParser::GreaterThanExprContext * /*ctx*/) override { }
  virtual void exitGreaterThanExpr(USEParser::GreaterThanExprContext * /*ctx*/) override { }

  virtual void enterAdditiveExpr(USEParser::AdditiveExprContext * /*ctx*/) override { }
  virtual void exitAdditiveExpr(USEParser::AdditiveExprContext * /*ctx*/) override { }

  virtual void enterLessThanExpr(USEParser::LessThanExprContext * /*ctx*/) override { }
  virtual void exitLessThanExpr(USEParser::LessThanExprContext * /*ctx*/) override { }

  virtual void enterGreaterThanOrEqualExpr(USEParser::GreaterThanOrEqualExprContext * /*ctx*/) override { }
  virtual void exitGreaterThanOrEqualExpr(USEParser::GreaterThanOrEqualExprContext * /*ctx*/) override { }

  virtual void enterAdditionExpr(USEParser::AdditionExprContext * /*ctx*/) override { }
  virtual void exitAdditionExpr(USEParser::AdditionExprContext * /*ctx*/) override { }

  virtual void enterSubtractionExpr(USEParser::SubtractionExprContext * /*ctx*/) override { }
  virtual void exitSubtractionExpr(USEParser::SubtractionExprContext * /*ctx*/) override { }

  virtual void enterFactorExpr(USEParser::FactorExprContext * /*ctx*/) override { }
  virtual void exitFactorExpr(USEParser::FactorExprContext * /*ctx*/) override { }

  virtual void enterDivisionExpr(USEParser::DivisionExprContext * /*ctx*/) override { }
  virtual void exitDivisionExpr(USEParser::DivisionExprContext * /*ctx*/) override { }

  virtual void enterMultiplicationExpr(USEParser::MultiplicationExprContext * /*ctx*/) override { }
  virtual void exitMultiplicationExpr(USEParser::MultiplicationExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(USEParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(USEParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterNotExpr(USEParser::NotExprContext * /*ctx*/) override { }
  virtual void exitNotExpr(USEParser::NotExprContext * /*ctx*/) override { }

  virtual void enterMinusExpr(USEParser::MinusExprContext * /*ctx*/) override { }
  virtual void exitMinusExpr(USEParser::MinusExprContext * /*ctx*/) override { }

  virtual void enterPlusExpr(USEParser::PlusExprContext * /*ctx*/) override { }
  virtual void exitPlusExpr(USEParser::PlusExprContext * /*ctx*/) override { }

  virtual void enterPostfixExpr(USEParser::PostfixExprContext * /*ctx*/) override { }
  virtual void exitPostfixExpr(USEParser::PostfixExprContext * /*ctx*/) override { }

  virtual void enterPrimaryExpr(USEParser::PrimaryExprContext * /*ctx*/) override { }
  virtual void exitPrimaryExpr(USEParser::PrimaryExprContext * /*ctx*/) override { }

  virtual void enterPropertyCallExpr(USEParser::PropertyCallExprContext * /*ctx*/) override { }
  virtual void exitPropertyCallExpr(USEParser::PropertyCallExprContext * /*ctx*/) override { }

  virtual void enterLiteralExpr(USEParser::LiteralExprContext * /*ctx*/) override { }
  virtual void exitLiteralExpr(USEParser::LiteralExprContext * /*ctx*/) override { }

  virtual void enterObjectReferenceExpr(USEParser::ObjectReferenceExprContext * /*ctx*/) override { }
  virtual void exitObjectReferenceExpr(USEParser::ObjectReferenceExprContext * /*ctx*/) override { }

  virtual void enterEmptyPropertyCallExpr(USEParser::EmptyPropertyCallExprContext * /*ctx*/) override { }
  virtual void exitEmptyPropertyCallExpr(USEParser::EmptyPropertyCallExprContext * /*ctx*/) override { }

  virtual void enterParenthesizedExpr(USEParser::ParenthesizedExprContext * /*ctx*/) override { }
  virtual void exitParenthesizedExpr(USEParser::ParenthesizedExprContext * /*ctx*/) override { }

  virtual void enterAllInstancesExpr(USEParser::AllInstancesExprContext * /*ctx*/) override { }
  virtual void exitAllInstancesExpr(USEParser::AllInstancesExprContext * /*ctx*/) override { }

  virtual void enterByUseIdExpr(USEParser::ByUseIdExprContext * /*ctx*/) override { }
  virtual void exitByUseIdExpr(USEParser::ByUseIdExprContext * /*ctx*/) override { }

  virtual void enterObjectReference(USEParser::ObjectReferenceContext * /*ctx*/) override { }
  virtual void exitObjectReference(USEParser::ObjectReferenceContext * /*ctx*/) override { }

  virtual void enterQueryExpr(USEParser::QueryExprContext * /*ctx*/) override { }
  virtual void exitQueryExpr(USEParser::QueryExprContext * /*ctx*/) override { }

  virtual void enterIterateExpr(USEParser::IterateExprContext * /*ctx*/) override { }
  virtual void exitIterateExpr(USEParser::IterateExprContext * /*ctx*/) override { }

  virtual void enterOperationExpr(USEParser::OperationExprContext * /*ctx*/) override { }
  virtual void exitOperationExpr(USEParser::OperationExprContext * /*ctx*/) override { }

  virtual void enterTypeExpr(USEParser::TypeExprContext * /*ctx*/) override { }
  virtual void exitTypeExpr(USEParser::TypeExprContext * /*ctx*/) override { }

  virtual void enterInStateExpr(USEParser::InStateExprContext * /*ctx*/) override { }
  virtual void exitInStateExpr(USEParser::InStateExprContext * /*ctx*/) override { }

  virtual void enterSelectExpr(USEParser::SelectExprContext * /*ctx*/) override { }
  virtual void exitSelectExpr(USEParser::SelectExprContext * /*ctx*/) override { }

  virtual void enterRejectExpr(USEParser::RejectExprContext * /*ctx*/) override { }
  virtual void exitRejectExpr(USEParser::RejectExprContext * /*ctx*/) override { }

  virtual void enterCollectExpr(USEParser::CollectExprContext * /*ctx*/) override { }
  virtual void exitCollectExpr(USEParser::CollectExprContext * /*ctx*/) override { }

  virtual void enterExistsExpr(USEParser::ExistsExprContext * /*ctx*/) override { }
  virtual void exitExistsExpr(USEParser::ExistsExprContext * /*ctx*/) override { }

  virtual void enterForAllExpr(USEParser::ForAllExprContext * /*ctx*/) override { }
  virtual void exitForAllExpr(USEParser::ForAllExprContext * /*ctx*/) override { }

  virtual void enterIsUniqueExpr(USEParser::IsUniqueExprContext * /*ctx*/) override { }
  virtual void exitIsUniqueExpr(USEParser::IsUniqueExprContext * /*ctx*/) override { }

  virtual void enterSortedByExpr(USEParser::SortedByExprContext * /*ctx*/) override { }
  virtual void exitSortedByExpr(USEParser::SortedByExprContext * /*ctx*/) override { }

  virtual void enterIterateExpression(USEParser::IterateExpressionContext * /*ctx*/) override { }
  virtual void exitIterateExpression(USEParser::IterateExpressionContext * /*ctx*/) override { }

  virtual void enterOperationExpression(USEParser::OperationExpressionContext * /*ctx*/) override { }
  virtual void exitOperationExpression(USEParser::OperationExpressionContext * /*ctx*/) override { }

  virtual void enterInStateExpression(USEParser::InStateExpressionContext * /*ctx*/) override { }
  virtual void exitInStateExpression(USEParser::InStateExpressionContext * /*ctx*/) override { }

  virtual void enterOclAsTypeExpr(USEParser::OclAsTypeExprContext * /*ctx*/) override { }
  virtual void exitOclAsTypeExpr(USEParser::OclAsTypeExprContext * /*ctx*/) override { }

  virtual void enterOclIsKindOfExpr(USEParser::OclIsKindOfExprContext * /*ctx*/) override { }
  virtual void exitOclIsKindOfExpr(USEParser::OclIsKindOfExprContext * /*ctx*/) override { }

  virtual void enterOclIsTypeOfExpr(USEParser::OclIsTypeOfExprContext * /*ctx*/) override { }
  virtual void exitOclIsTypeOfExpr(USEParser::OclIsTypeOfExprContext * /*ctx*/) override { }

  virtual void enterSelectByTypeExpr(USEParser::SelectByTypeExprContext * /*ctx*/) override { }
  virtual void exitSelectByTypeExpr(USEParser::SelectByTypeExprContext * /*ctx*/) override { }

  virtual void enterSelectByKindExpr(USEParser::SelectByKindExprContext * /*ctx*/) override { }
  virtual void exitSelectByKindExpr(USEParser::SelectByKindExprContext * /*ctx*/) override { }

  virtual void enterElemVarsDeclaration(USEParser::ElemVarsDeclarationContext * /*ctx*/) override { }
  virtual void exitElemVarsDeclaration(USEParser::ElemVarsDeclarationContext * /*ctx*/) override { }

  virtual void enterVariableInitialization(USEParser::VariableInitializationContext * /*ctx*/) override { }
  virtual void exitVariableInitialization(USEParser::VariableInitializationContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(USEParser::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(USEParser::ConditionalExpressionContext * /*ctx*/) override { }

  virtual void enterLiteralBooleanTrue(USEParser::LiteralBooleanTrueContext * /*ctx*/) override { }
  virtual void exitLiteralBooleanTrue(USEParser::LiteralBooleanTrueContext * /*ctx*/) override { }

  virtual void enterLiteralBooleanFalse(USEParser::LiteralBooleanFalseContext * /*ctx*/) override { }
  virtual void exitLiteralBooleanFalse(USEParser::LiteralBooleanFalseContext * /*ctx*/) override { }

  virtual void enterLiteralInteger(USEParser::LiteralIntegerContext * /*ctx*/) override { }
  virtual void exitLiteralInteger(USEParser::LiteralIntegerContext * /*ctx*/) override { }

  virtual void enterLiteralReal(USEParser::LiteralRealContext * /*ctx*/) override { }
  virtual void exitLiteralReal(USEParser::LiteralRealContext * /*ctx*/) override { }

  virtual void enterLiteralString(USEParser::LiteralStringContext * /*ctx*/) override { }
  virtual void exitLiteralString(USEParser::LiteralStringContext * /*ctx*/) override { }

  virtual void enterLiteralEnum(USEParser::LiteralEnumContext * /*ctx*/) override { }
  virtual void exitLiteralEnum(USEParser::LiteralEnumContext * /*ctx*/) override { }

  virtual void enterLiteralQualifiedEnum(USEParser::LiteralQualifiedEnumContext * /*ctx*/) override { }
  virtual void exitLiteralQualifiedEnum(USEParser::LiteralQualifiedEnumContext * /*ctx*/) override { }

  virtual void enterLiteralCollection(USEParser::LiteralCollectionContext * /*ctx*/) override { }
  virtual void exitLiteralCollection(USEParser::LiteralCollectionContext * /*ctx*/) override { }

  virtual void enterLiteralEmptyCollection(USEParser::LiteralEmptyCollectionContext * /*ctx*/) override { }
  virtual void exitLiteralEmptyCollection(USEParser::LiteralEmptyCollectionContext * /*ctx*/) override { }

  virtual void enterLiteralUndefined(USEParser::LiteralUndefinedContext * /*ctx*/) override { }
  virtual void exitLiteralUndefined(USEParser::LiteralUndefinedContext * /*ctx*/) override { }

  virtual void enterLiteralTuple(USEParser::LiteralTupleContext * /*ctx*/) override { }
  virtual void exitLiteralTuple(USEParser::LiteralTupleContext * /*ctx*/) override { }

  virtual void enterLiteralUnlimitedNatural(USEParser::LiteralUnlimitedNaturalContext * /*ctx*/) override { }
  virtual void exitLiteralUnlimitedNatural(USEParser::LiteralUnlimitedNaturalContext * /*ctx*/) override { }

  virtual void enterSetLiteral(USEParser::SetLiteralContext * /*ctx*/) override { }
  virtual void exitSetLiteral(USEParser::SetLiteralContext * /*ctx*/) override { }

  virtual void enterSequenceLiteral(USEParser::SequenceLiteralContext * /*ctx*/) override { }
  virtual void exitSequenceLiteral(USEParser::SequenceLiteralContext * /*ctx*/) override { }

  virtual void enterBagLiteral(USEParser::BagLiteralContext * /*ctx*/) override { }
  virtual void exitBagLiteral(USEParser::BagLiteralContext * /*ctx*/) override { }

  virtual void enterOrderedSetLiteral(USEParser::OrderedSetLiteralContext * /*ctx*/) override { }
  virtual void exitOrderedSetLiteral(USEParser::OrderedSetLiteralContext * /*ctx*/) override { }

  virtual void enterCollectionItem(USEParser::CollectionItemContext * /*ctx*/) override { }
  virtual void exitCollectionItem(USEParser::CollectionItemContext * /*ctx*/) override { }

  virtual void enterEmptyCollectionLiteral(USEParser::EmptyCollectionLiteralContext * /*ctx*/) override { }
  virtual void exitEmptyCollectionLiteral(USEParser::EmptyCollectionLiteralContext * /*ctx*/) override { }

  virtual void enterUndefinedLiteral(USEParser::UndefinedLiteralContext * /*ctx*/) override { }
  virtual void exitUndefinedLiteral(USEParser::UndefinedLiteralContext * /*ctx*/) override { }

  virtual void enterTupleLiteral(USEParser::TupleLiteralContext * /*ctx*/) override { }
  virtual void exitTupleLiteral(USEParser::TupleLiteralContext * /*ctx*/) override { }

  virtual void enterTypedTupleItem(USEParser::TypedTupleItemContext * /*ctx*/) override { }
  virtual void exitTypedTupleItem(USEParser::TypedTupleItemContext * /*ctx*/) override { }

  virtual void enterUntypedTupleItem(USEParser::UntypedTupleItemContext * /*ctx*/) override { }
  virtual void exitUntypedTupleItem(USEParser::UntypedTupleItemContext * /*ctx*/) override { }

  virtual void enterTypeSimple(USEParser::TypeSimpleContext * /*ctx*/) override { }
  virtual void exitTypeSimple(USEParser::TypeSimpleContext * /*ctx*/) override { }

  virtual void enterTypeCollection(USEParser::TypeCollectionContext * /*ctx*/) override { }
  virtual void exitTypeCollection(USEParser::TypeCollectionContext * /*ctx*/) override { }

  virtual void enterTypeTuple(USEParser::TypeTupleContext * /*ctx*/) override { }
  virtual void exitTypeTuple(USEParser::TypeTupleContext * /*ctx*/) override { }

  virtual void enterTypeOnly(USEParser::TypeOnlyContext * /*ctx*/) override { }
  virtual void exitTypeOnly(USEParser::TypeOnlyContext * /*ctx*/) override { }

  virtual void enterSimpleType(USEParser::SimpleTypeContext * /*ctx*/) override { }
  virtual void exitSimpleType(USEParser::SimpleTypeContext * /*ctx*/) override { }

  virtual void enterTypeSimpleCollection(USEParser::TypeSimpleCollectionContext * /*ctx*/) override { }
  virtual void exitTypeSimpleCollection(USEParser::TypeSimpleCollectionContext * /*ctx*/) override { }

  virtual void enterTypeSet(USEParser::TypeSetContext * /*ctx*/) override { }
  virtual void exitTypeSet(USEParser::TypeSetContext * /*ctx*/) override { }

  virtual void enterTypeSequence(USEParser::TypeSequenceContext * /*ctx*/) override { }
  virtual void exitTypeSequence(USEParser::TypeSequenceContext * /*ctx*/) override { }

  virtual void enterTypeBag(USEParser::TypeBagContext * /*ctx*/) override { }
  virtual void exitTypeBag(USEParser::TypeBagContext * /*ctx*/) override { }

  virtual void enterTypeOrderedSet(USEParser::TypeOrderedSetContext * /*ctx*/) override { }
  virtual void exitTypeOrderedSet(USEParser::TypeOrderedSetContext * /*ctx*/) override { }

  virtual void enterTupleType(USEParser::TupleTypeContext * /*ctx*/) override { }
  virtual void exitTupleType(USEParser::TupleTypeContext * /*ctx*/) override { }

  virtual void enterTuplePart(USEParser::TuplePartContext * /*ctx*/) override { }
  virtual void exitTuplePart(USEParser::TuplePartContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

