 
/*
 * HEADER TEST
 */



// Generated from USE.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "USEVisitor.h"


/**
 * This class provides an empty implementation of USEVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  USEBaseVisitor : public USEVisitor {
public:

  virtual std::any visitModel(USEParser::ModelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnum(USEParser::EnumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass(USEParser::ClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociation(USEParser::AssociationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociationClass(USEParser::AssociationClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraints(USEParser::ConstraintsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumTypeDefinition(USEParser::EnumTypeDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDefinition(USEParser::ClassDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociationClassDefinition(USEParser::AssociationClassDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeDefinition(USEParser::AttributeDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitDefinition(USEParser::InitDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDerivedDefinition(USEParser::DerivedDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperationDefinition(USEParser::OperationDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleAssociation(USEParser::SimpleAssociationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAggregation(USEParser::AggregationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComposition(USEParser::CompositionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociationEnd(USEParser::AssociationEndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRole(USEParser::RoleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRedefines(USEParser::RedefinesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsets(USEParser::SubsetsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity(USEParser::MultiplicityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicityRange(USEParser::MultiplicityRangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicitySpec(USEParser::MultiplicitySpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvariantDefinition(USEParser::InvariantDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrePostDefinition(USEParser::PrePostDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvariant(USEParser::InvariantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvariantClause(USEParser::InvariantClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrePost(USEParser::PrePostContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPreCondition(USEParser::PreConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostCondition(USEParser::PostConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStateMachine(USEParser::StateMachineContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStateDefinition(USEParser::StateDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransitionDefinition(USEParser::TransitionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionOnly(USEParser::ExpressionOnlyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalExpr(USEParser::LogicalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalExpr(USEParser::ConditionalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLetExpr(USEParser::LetExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLetExpression(USEParser::LetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpr(USEParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpr(USEParser::EqualityExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitXorExpr(USEParser::XorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImpliesExpr(USEParser::ImpliesExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpr(USEParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParamList(USEParser::ParamListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdList(USEParser::IdListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(USEParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualExpr(USEParser::EqualExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpr(USEParser::RelationalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotEqualExpr(USEParser::NotEqualExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLessThanOrEqualExpr(USEParser::LessThanOrEqualExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGreaterThanExpr(USEParser::GreaterThanExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpr(USEParser::AdditiveExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLessThanExpr(USEParser::LessThanExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGreaterThanOrEqualExpr(USEParser::GreaterThanOrEqualExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditionExpr(USEParser::AdditionExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubtractionExpr(USEParser::SubtractionExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactorExpr(USEParser::FactorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDivisionExpr(USEParser::DivisionExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicationExpr(USEParser::MultiplicationExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(USEParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotExpr(USEParser::NotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMinusExpr(USEParser::MinusExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlusExpr(USEParser::PlusExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfixExpr(USEParser::PostfixExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpr(USEParser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyCallExpr(USEParser::PropertyCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpr(USEParser::LiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectReferenceExpr(USEParser::ObjectReferenceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyPropertyCallExpr(USEParser::EmptyPropertyCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesizedExpr(USEParser::ParenthesizedExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllInstancesExpr(USEParser::AllInstancesExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitByUseIdExpr(USEParser::ByUseIdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectReference(USEParser::ObjectReferenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQueryExpr(USEParser::QueryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterateExpr(USEParser::IterateExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperationExpr(USEParser::OperationExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeExpr(USEParser::TypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInStateExpr(USEParser::InStateExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectExpr(USEParser::SelectExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRejectExpr(USEParser::RejectExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectExpr(USEParser::CollectExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExistsExpr(USEParser::ExistsExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForAllExpr(USEParser::ForAllExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIsUniqueExpr(USEParser::IsUniqueExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSortedByExpr(USEParser::SortedByExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterateExpression(USEParser::IterateExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperationExpression(USEParser::OperationExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInStateExpression(USEParser::InStateExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOclAsTypeExpr(USEParser::OclAsTypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOclIsKindOfExpr(USEParser::OclIsKindOfExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOclIsTypeOfExpr(USEParser::OclIsTypeOfExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectByTypeExpr(USEParser::SelectByTypeExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectByKindExpr(USEParser::SelectByKindExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemVarsDeclaration(USEParser::ElemVarsDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableInitialization(USEParser::VariableInitializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalExpression(USEParser::ConditionalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralBooleanTrue(USEParser::LiteralBooleanTrueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralBooleanFalse(USEParser::LiteralBooleanFalseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralInteger(USEParser::LiteralIntegerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralReal(USEParser::LiteralRealContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralString(USEParser::LiteralStringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralEnum(USEParser::LiteralEnumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralQualifiedEnum(USEParser::LiteralQualifiedEnumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralCollection(USEParser::LiteralCollectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralEmptyCollection(USEParser::LiteralEmptyCollectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralUndefined(USEParser::LiteralUndefinedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralTuple(USEParser::LiteralTupleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralUnlimitedNatural(USEParser::LiteralUnlimitedNaturalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetLiteral(USEParser::SetLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequenceLiteral(USEParser::SequenceLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBagLiteral(USEParser::BagLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrderedSetLiteral(USEParser::OrderedSetLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectionItem(USEParser::CollectionItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyCollectionLiteral(USEParser::EmptyCollectionLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUndefinedLiteral(USEParser::UndefinedLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTupleLiteral(USEParser::TupleLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedTupleItem(USEParser::TypedTupleItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUntypedTupleItem(USEParser::UntypedTupleItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSimple(USEParser::TypeSimpleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeCollection(USEParser::TypeCollectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeTuple(USEParser::TypeTupleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeOnly(USEParser::TypeOnlyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleType(USEParser::SimpleTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSimpleCollection(USEParser::TypeSimpleCollectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSet(USEParser::TypeSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSequence(USEParser::TypeSequenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeBag(USEParser::TypeBagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeOrderedSet(USEParser::TypeOrderedSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTupleType(USEParser::TupleTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTuplePart(USEParser::TuplePartContext *ctx) override {
    return visitChildren(ctx);
  }


};

