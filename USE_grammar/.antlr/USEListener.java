// Generated from c:/Users/jabr3/Documents/GitHub/ModelForge/USE_grammar/USE.g4 by ANTLR 4.13.1
 
/*
 * HEADER TEST
 */


import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link USEParser}.
 */
public interface USEListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link USEParser#model}.
	 * @param ctx the parse tree
	 */
	void enterModel(USEParser.ModelContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#model}.
	 * @param ctx the parse tree
	 */
	void exitModel(USEParser.ModelContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Enum}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void enterEnum(USEParser.EnumContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Enum}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void exitEnum(USEParser.EnumContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Class}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void enterClass(USEParser.ClassContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Class}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void exitClass(USEParser.ClassContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Association}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void enterAssociation(USEParser.AssociationContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Association}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void exitAssociation(USEParser.AssociationContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AssociationClass}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void enterAssociationClass(USEParser.AssociationClassContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AssociationClass}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void exitAssociationClass(USEParser.AssociationClassContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Constraints}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void enterConstraints(USEParser.ConstraintsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Constraints}
	 * labeled alternative in {@link USEParser#modelElement}.
	 * @param ctx the parse tree
	 */
	void exitConstraints(USEParser.ConstraintsContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#enumTypeDefinition}.
	 * @param ctx the parse tree
	 */
	void enterEnumTypeDefinition(USEParser.EnumTypeDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#enumTypeDefinition}.
	 * @param ctx the parse tree
	 */
	void exitEnumTypeDefinition(USEParser.EnumTypeDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#classDefinition}.
	 * @param ctx the parse tree
	 */
	void enterClassDefinition(USEParser.ClassDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#classDefinition}.
	 * @param ctx the parse tree
	 */
	void exitClassDefinition(USEParser.ClassDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#associationClassDefinition}.
	 * @param ctx the parse tree
	 */
	void enterAssociationClassDefinition(USEParser.AssociationClassDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#associationClassDefinition}.
	 * @param ctx the parse tree
	 */
	void exitAssociationClassDefinition(USEParser.AssociationClassDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#attributeDefinition}.
	 * @param ctx the parse tree
	 */
	void enterAttributeDefinition(USEParser.AttributeDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#attributeDefinition}.
	 * @param ctx the parse tree
	 */
	void exitAttributeDefinition(USEParser.AttributeDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#initDefinition}.
	 * @param ctx the parse tree
	 */
	void enterInitDefinition(USEParser.InitDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#initDefinition}.
	 * @param ctx the parse tree
	 */
	void exitInitDefinition(USEParser.InitDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#derivedDefinition}.
	 * @param ctx the parse tree
	 */
	void enterDerivedDefinition(USEParser.DerivedDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#derivedDefinition}.
	 * @param ctx the parse tree
	 */
	void exitDerivedDefinition(USEParser.DerivedDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#operationDefinition}.
	 * @param ctx the parse tree
	 */
	void enterOperationDefinition(USEParser.OperationDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#operationDefinition}.
	 * @param ctx the parse tree
	 */
	void exitOperationDefinition(USEParser.OperationDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SimpleAssociation}
	 * labeled alternative in {@link USEParser#associationDefinition}.
	 * @param ctx the parse tree
	 */
	void enterSimpleAssociation(USEParser.SimpleAssociationContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SimpleAssociation}
	 * labeled alternative in {@link USEParser#associationDefinition}.
	 * @param ctx the parse tree
	 */
	void exitSimpleAssociation(USEParser.SimpleAssociationContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Aggregation}
	 * labeled alternative in {@link USEParser#associationDefinition}.
	 * @param ctx the parse tree
	 */
	void enterAggregation(USEParser.AggregationContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Aggregation}
	 * labeled alternative in {@link USEParser#associationDefinition}.
	 * @param ctx the parse tree
	 */
	void exitAggregation(USEParser.AggregationContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Composition}
	 * labeled alternative in {@link USEParser#associationDefinition}.
	 * @param ctx the parse tree
	 */
	void enterComposition(USEParser.CompositionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Composition}
	 * labeled alternative in {@link USEParser#associationDefinition}.
	 * @param ctx the parse tree
	 */
	void exitComposition(USEParser.CompositionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#associationEnd}.
	 * @param ctx the parse tree
	 */
	void enterAssociationEnd(USEParser.AssociationEndContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#associationEnd}.
	 * @param ctx the parse tree
	 */
	void exitAssociationEnd(USEParser.AssociationEndContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#role}.
	 * @param ctx the parse tree
	 */
	void enterRole(USEParser.RoleContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#role}.
	 * @param ctx the parse tree
	 */
	void exitRole(USEParser.RoleContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#redefines}.
	 * @param ctx the parse tree
	 */
	void enterRedefines(USEParser.RedefinesContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#redefines}.
	 * @param ctx the parse tree
	 */
	void exitRedefines(USEParser.RedefinesContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#subsets}.
	 * @param ctx the parse tree
	 */
	void enterSubsets(USEParser.SubsetsContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#subsets}.
	 * @param ctx the parse tree
	 */
	void exitSubsets(USEParser.SubsetsContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#multiplicity}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity(USEParser.MultiplicityContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#multiplicity}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity(USEParser.MultiplicityContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#multiplicityRange}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicityRange(USEParser.MultiplicityRangeContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#multiplicityRange}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicityRange(USEParser.MultiplicityRangeContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#multiplicitySpec}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicitySpec(USEParser.MultiplicitySpecContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#multiplicitySpec}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicitySpec(USEParser.MultiplicitySpecContext ctx);
	/**
	 * Enter a parse tree produced by the {@code InvariantDefinition}
	 * labeled alternative in {@link USEParser#constraintDefinition}.
	 * @param ctx the parse tree
	 */
	void enterInvariantDefinition(USEParser.InvariantDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code InvariantDefinition}
	 * labeled alternative in {@link USEParser#constraintDefinition}.
	 * @param ctx the parse tree
	 */
	void exitInvariantDefinition(USEParser.InvariantDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PrePostDefinition}
	 * labeled alternative in {@link USEParser#constraintDefinition}.
	 * @param ctx the parse tree
	 */
	void enterPrePostDefinition(USEParser.PrePostDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PrePostDefinition}
	 * labeled alternative in {@link USEParser#constraintDefinition}.
	 * @param ctx the parse tree
	 */
	void exitPrePostDefinition(USEParser.PrePostDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#invariant}.
	 * @param ctx the parse tree
	 */
	void enterInvariant(USEParser.InvariantContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#invariant}.
	 * @param ctx the parse tree
	 */
	void exitInvariant(USEParser.InvariantContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#invariantClause}.
	 * @param ctx the parse tree
	 */
	void enterInvariantClause(USEParser.InvariantClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#invariantClause}.
	 * @param ctx the parse tree
	 */
	void exitInvariantClause(USEParser.InvariantClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#prePost}.
	 * @param ctx the parse tree
	 */
	void enterPrePost(USEParser.PrePostContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#prePost}.
	 * @param ctx the parse tree
	 */
	void exitPrePost(USEParser.PrePostContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PreCondition}
	 * labeled alternative in {@link USEParser#prePostClause}.
	 * @param ctx the parse tree
	 */
	void enterPreCondition(USEParser.PreConditionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PreCondition}
	 * labeled alternative in {@link USEParser#prePostClause}.
	 * @param ctx the parse tree
	 */
	void exitPreCondition(USEParser.PreConditionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PostCondition}
	 * labeled alternative in {@link USEParser#prePostClause}.
	 * @param ctx the parse tree
	 */
	void enterPostCondition(USEParser.PostConditionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PostCondition}
	 * labeled alternative in {@link USEParser#prePostClause}.
	 * @param ctx the parse tree
	 */
	void exitPostCondition(USEParser.PostConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#stateMachine}.
	 * @param ctx the parse tree
	 */
	void enterStateMachine(USEParser.StateMachineContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#stateMachine}.
	 * @param ctx the parse tree
	 */
	void exitStateMachine(USEParser.StateMachineContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#stateDefinition}.
	 * @param ctx the parse tree
	 */
	void enterStateDefinition(USEParser.StateDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#stateDefinition}.
	 * @param ctx the parse tree
	 */
	void exitStateDefinition(USEParser.StateDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#transitionDefinition}.
	 * @param ctx the parse tree
	 */
	void enterTransitionDefinition(USEParser.TransitionDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#transitionDefinition}.
	 * @param ctx the parse tree
	 */
	void exitTransitionDefinition(USEParser.TransitionDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#expressionOnly}.
	 * @param ctx the parse tree
	 */
	void enterExpressionOnly(USEParser.ExpressionOnlyContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#expressionOnly}.
	 * @param ctx the parse tree
	 */
	void exitExpressionOnly(USEParser.ExpressionOnlyContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#oclExpression}.
	 * @param ctx the parse tree
	 */
	void enterOclExpression(USEParser.OclExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#oclExpression}.
	 * @param ctx the parse tree
	 */
	void exitOclExpression(USEParser.OclExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicalExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalExpr(USEParser.LogicalExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicalExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalExpr(USEParser.LogicalExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ConditionalExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterConditionalExpr(USEParser.ConditionalExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ConditionalExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitConditionalExpr(USEParser.ConditionalExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LambdaExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLambdaExpr(USEParser.LambdaExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LambdaExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLambdaExpr(USEParser.LambdaExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LetExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLetExpr(USEParser.LetExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LetExpr}
	 * labeled alternative in {@link USEParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLetExpr(USEParser.LetExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#lambdaExpression}.
	 * @param ctx the parse tree
	 */
	void enterLambdaExpression(USEParser.LambdaExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#lambdaExpression}.
	 * @param ctx the parse tree
	 */
	void exitLambdaExpression(USEParser.LambdaExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#letExpression}.
	 * @param ctx the parse tree
	 */
	void enterLetExpression(USEParser.LetExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#letExpression}.
	 * @param ctx the parse tree
	 */
	void exitLetExpression(USEParser.LetExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AndExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void enterAndExpr(USEParser.AndExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AndExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void exitAndExpr(USEParser.AndExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code EqualityExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualityExpr(USEParser.EqualityExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code EqualityExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualityExpr(USEParser.EqualityExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code XorExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void enterXorExpr(USEParser.XorExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code XorExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void exitXorExpr(USEParser.XorExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ImpliesExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void enterImpliesExpr(USEParser.ImpliesExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ImpliesExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void exitImpliesExpr(USEParser.ImpliesExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code OrExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void enterOrExpr(USEParser.OrExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code OrExpr}
	 * labeled alternative in {@link USEParser#logicalExpression}.
	 * @param ctx the parse tree
	 */
	void exitOrExpr(USEParser.OrExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#paramList}.
	 * @param ctx the parse tree
	 */
	void enterParamList(USEParser.ParamListContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#paramList}.
	 * @param ctx the parse tree
	 */
	void exitParamList(USEParser.ParamListContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#idList}.
	 * @param ctx the parse tree
	 */
	void enterIdList(USEParser.IdListContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#idList}.
	 * @param ctx the parse tree
	 */
	void exitIdList(USEParser.IdListContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclaration(USEParser.VariableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclaration(USEParser.VariableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by the {@code EqualExpr}
	 * labeled alternative in {@link USEParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualExpr(USEParser.EqualExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code EqualExpr}
	 * labeled alternative in {@link USEParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualExpr(USEParser.EqualExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code RelationalExpr}
	 * labeled alternative in {@link USEParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterRelationalExpr(USEParser.RelationalExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code RelationalExpr}
	 * labeled alternative in {@link USEParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitRelationalExpr(USEParser.RelationalExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code NotEqualExpr}
	 * labeled alternative in {@link USEParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterNotEqualExpr(USEParser.NotEqualExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code NotEqualExpr}
	 * labeled alternative in {@link USEParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitNotEqualExpr(USEParser.NotEqualExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LessThanOrEqualExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterLessThanOrEqualExpr(USEParser.LessThanOrEqualExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LessThanOrEqualExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitLessThanOrEqualExpr(USEParser.LessThanOrEqualExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GreaterThanExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterGreaterThanExpr(USEParser.GreaterThanExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GreaterThanExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitGreaterThanExpr(USEParser.GreaterThanExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AdditiveExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterAdditiveExpr(USEParser.AdditiveExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AdditiveExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitAdditiveExpr(USEParser.AdditiveExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LessThanExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterLessThanExpr(USEParser.LessThanExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LessThanExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitLessThanExpr(USEParser.LessThanExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GreaterThanOrEqualExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterGreaterThanOrEqualExpr(USEParser.GreaterThanOrEqualExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GreaterThanOrEqualExpr}
	 * labeled alternative in {@link USEParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitGreaterThanOrEqualExpr(USEParser.GreaterThanOrEqualExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AdditionExpr}
	 * labeled alternative in {@link USEParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterAdditionExpr(USEParser.AdditionExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AdditionExpr}
	 * labeled alternative in {@link USEParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitAdditionExpr(USEParser.AdditionExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SubtractionExpr}
	 * labeled alternative in {@link USEParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterSubtractionExpr(USEParser.SubtractionExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SubtractionExpr}
	 * labeled alternative in {@link USEParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitSubtractionExpr(USEParser.SubtractionExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FactorExpr}
	 * labeled alternative in {@link USEParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterFactorExpr(USEParser.FactorExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FactorExpr}
	 * labeled alternative in {@link USEParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitFactorExpr(USEParser.FactorExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DivisionExpr}
	 * labeled alternative in {@link USEParser#factorExpression}.
	 * @param ctx the parse tree
	 */
	void enterDivisionExpr(USEParser.DivisionExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DivisionExpr}
	 * labeled alternative in {@link USEParser#factorExpression}.
	 * @param ctx the parse tree
	 */
	void exitDivisionExpr(USEParser.DivisionExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MultiplicationExpr}
	 * labeled alternative in {@link USEParser#factorExpression}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicationExpr(USEParser.MultiplicationExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MultiplicationExpr}
	 * labeled alternative in {@link USEParser#factorExpression}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicationExpr(USEParser.MultiplicationExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnaryExpr}
	 * labeled alternative in {@link USEParser#factorExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryExpr(USEParser.UnaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnaryExpr}
	 * labeled alternative in {@link USEParser#factorExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryExpr(USEParser.UnaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code NotExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterNotExpr(USEParser.NotExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code NotExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitNotExpr(USEParser.NotExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MinusExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterMinusExpr(USEParser.MinusExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MinusExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitMinusExpr(USEParser.MinusExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PlusExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterPlusExpr(USEParser.PlusExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PlusExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitPlusExpr(USEParser.PlusExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PostfixExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterPostfixExpr(USEParser.PostfixExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PostfixExpr}
	 * labeled alternative in {@link USEParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitPostfixExpr(USEParser.PostfixExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PrimaryExpr}
	 * labeled alternative in {@link USEParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterPrimaryExpr(USEParser.PrimaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PrimaryExpr}
	 * labeled alternative in {@link USEParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitPrimaryExpr(USEParser.PrimaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PropertyCallExpr}
	 * labeled alternative in {@link USEParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterPropertyCallExpr(USEParser.PropertyCallExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PropertyCallExpr}
	 * labeled alternative in {@link USEParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitPropertyCallExpr(USEParser.PropertyCallExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterLiteralExpr(USEParser.LiteralExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitLiteralExpr(USEParser.LiteralExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ObjectReferenceExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterObjectReferenceExpr(USEParser.ObjectReferenceExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ObjectReferenceExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitObjectReferenceExpr(USEParser.ObjectReferenceExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code EmptyPropertyCallExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterEmptyPropertyCallExpr(USEParser.EmptyPropertyCallExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code EmptyPropertyCallExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitEmptyPropertyCallExpr(USEParser.EmptyPropertyCallExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParenthesizedExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterParenthesizedExpr(USEParser.ParenthesizedExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParenthesizedExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitParenthesizedExpr(USEParser.ParenthesizedExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AllInstancesExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterAllInstancesExpr(USEParser.AllInstancesExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AllInstancesExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitAllInstancesExpr(USEParser.AllInstancesExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ByUseIdExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterByUseIdExpr(USEParser.ByUseIdExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ByUseIdExpr}
	 * labeled alternative in {@link USEParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitByUseIdExpr(USEParser.ByUseIdExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#objectReference}.
	 * @param ctx the parse tree
	 */
	void enterObjectReference(USEParser.ObjectReferenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#objectReference}.
	 * @param ctx the parse tree
	 */
	void exitObjectReference(USEParser.ObjectReferenceContext ctx);
	/**
	 * Enter a parse tree produced by the {@code QueryExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void enterQueryExpr(USEParser.QueryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code QueryExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void exitQueryExpr(USEParser.QueryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code IterateExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void enterIterateExpr(USEParser.IterateExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code IterateExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void exitIterateExpr(USEParser.IterateExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code OperationExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void enterOperationExpr(USEParser.OperationExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code OperationExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void exitOperationExpr(USEParser.OperationExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void enterTypeExpr(USEParser.TypeExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void exitTypeExpr(USEParser.TypeExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code InStateExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void enterInStateExpr(USEParser.InStateExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code InStateExpr}
	 * labeled alternative in {@link USEParser#propertyCall}.
	 * @param ctx the parse tree
	 */
	void exitInStateExpr(USEParser.InStateExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SelectExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void enterSelectExpr(USEParser.SelectExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SelectExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void exitSelectExpr(USEParser.SelectExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code RejectExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void enterRejectExpr(USEParser.RejectExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code RejectExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void exitRejectExpr(USEParser.RejectExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code CollectExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void enterCollectExpr(USEParser.CollectExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code CollectExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void exitCollectExpr(USEParser.CollectExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExistsExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void enterExistsExpr(USEParser.ExistsExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExistsExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void exitExistsExpr(USEParser.ExistsExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ForAllExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void enterForAllExpr(USEParser.ForAllExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ForAllExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void exitForAllExpr(USEParser.ForAllExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code IsUniqueExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void enterIsUniqueExpr(USEParser.IsUniqueExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code IsUniqueExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void exitIsUniqueExpr(USEParser.IsUniqueExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SortedByExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void enterSortedByExpr(USEParser.SortedByExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SortedByExpr}
	 * labeled alternative in {@link USEParser#queryExpression}.
	 * @param ctx the parse tree
	 */
	void exitSortedByExpr(USEParser.SortedByExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#iterateExpression}.
	 * @param ctx the parse tree
	 */
	void enterIterateExpression(USEParser.IterateExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#iterateExpression}.
	 * @param ctx the parse tree
	 */
	void exitIterateExpression(USEParser.IterateExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#operationExpression}.
	 * @param ctx the parse tree
	 */
	void enterOperationExpression(USEParser.OperationExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#operationExpression}.
	 * @param ctx the parse tree
	 */
	void exitOperationExpression(USEParser.OperationExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#inStateExpression}.
	 * @param ctx the parse tree
	 */
	void enterInStateExpression(USEParser.InStateExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#inStateExpression}.
	 * @param ctx the parse tree
	 */
	void exitInStateExpression(USEParser.InStateExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code OclAsTypeExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void enterOclAsTypeExpr(USEParser.OclAsTypeExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code OclAsTypeExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void exitOclAsTypeExpr(USEParser.OclAsTypeExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code OclIsKindOfExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void enterOclIsKindOfExpr(USEParser.OclIsKindOfExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code OclIsKindOfExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void exitOclIsKindOfExpr(USEParser.OclIsKindOfExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code OclIsTypeOfExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void enterOclIsTypeOfExpr(USEParser.OclIsTypeOfExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code OclIsTypeOfExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void exitOclIsTypeOfExpr(USEParser.OclIsTypeOfExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SelectByTypeExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void enterSelectByTypeExpr(USEParser.SelectByTypeExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SelectByTypeExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void exitSelectByTypeExpr(USEParser.SelectByTypeExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SelectByKindExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void enterSelectByKindExpr(USEParser.SelectByKindExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SelectByKindExpr}
	 * labeled alternative in {@link USEParser#typeExpression}.
	 * @param ctx the parse tree
	 */
	void exitSelectByKindExpr(USEParser.SelectByKindExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#elemVarsDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterElemVarsDeclaration(USEParser.ElemVarsDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#elemVarsDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitElemVarsDeclaration(USEParser.ElemVarsDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#variableInitialization}.
	 * @param ctx the parse tree
	 */
	void enterVariableInitialization(USEParser.VariableInitializationContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#variableInitialization}.
	 * @param ctx the parse tree
	 */
	void exitVariableInitialization(USEParser.VariableInitializationContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void enterConditionalExpression(USEParser.ConditionalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#conditionalExpression}.
	 * @param ctx the parse tree
	 */
	void exitConditionalExpression(USEParser.ConditionalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralBooleanTrue}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralBooleanTrue(USEParser.LiteralBooleanTrueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralBooleanTrue}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralBooleanTrue(USEParser.LiteralBooleanTrueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralBooleanFalse}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralBooleanFalse(USEParser.LiteralBooleanFalseContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralBooleanFalse}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralBooleanFalse(USEParser.LiteralBooleanFalseContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralInteger}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralInteger(USEParser.LiteralIntegerContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralInteger}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralInteger(USEParser.LiteralIntegerContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralReal}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralReal(USEParser.LiteralRealContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralReal}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralReal(USEParser.LiteralRealContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralString}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralString(USEParser.LiteralStringContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralString}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralString(USEParser.LiteralStringContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralEnum}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralEnum(USEParser.LiteralEnumContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralEnum}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralEnum(USEParser.LiteralEnumContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralQualifiedEnum}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralQualifiedEnum(USEParser.LiteralQualifiedEnumContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralQualifiedEnum}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralQualifiedEnum(USEParser.LiteralQualifiedEnumContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralCollection}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralCollection(USEParser.LiteralCollectionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralCollection}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralCollection(USEParser.LiteralCollectionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralEmptyCollection}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralEmptyCollection(USEParser.LiteralEmptyCollectionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralEmptyCollection}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralEmptyCollection(USEParser.LiteralEmptyCollectionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralUndefined}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralUndefined(USEParser.LiteralUndefinedContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralUndefined}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralUndefined(USEParser.LiteralUndefinedContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralTuple}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralTuple(USEParser.LiteralTupleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralTuple}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralTuple(USEParser.LiteralTupleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralUnlimitedNatural}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteralUnlimitedNatural(USEParser.LiteralUnlimitedNaturalContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralUnlimitedNatural}
	 * labeled alternative in {@link USEParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteralUnlimitedNatural(USEParser.LiteralUnlimitedNaturalContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SetLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void enterSetLiteral(USEParser.SetLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SetLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void exitSetLiteral(USEParser.SetLiteralContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SequenceLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void enterSequenceLiteral(USEParser.SequenceLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SequenceLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void exitSequenceLiteral(USEParser.SequenceLiteralContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BagLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void enterBagLiteral(USEParser.BagLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BagLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void exitBagLiteral(USEParser.BagLiteralContext ctx);
	/**
	 * Enter a parse tree produced by the {@code OrderedSetLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void enterOrderedSetLiteral(USEParser.OrderedSetLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code OrderedSetLiteral}
	 * labeled alternative in {@link USEParser#collectionLiteral}.
	 * @param ctx the parse tree
	 */
	void exitOrderedSetLiteral(USEParser.OrderedSetLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#collectionItem}.
	 * @param ctx the parse tree
	 */
	void enterCollectionItem(USEParser.CollectionItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#collectionItem}.
	 * @param ctx the parse tree
	 */
	void exitCollectionItem(USEParser.CollectionItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#emptyCollectionLiteral}.
	 * @param ctx the parse tree
	 */
	void enterEmptyCollectionLiteral(USEParser.EmptyCollectionLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#emptyCollectionLiteral}.
	 * @param ctx the parse tree
	 */
	void exitEmptyCollectionLiteral(USEParser.EmptyCollectionLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#undefinedLiteral}.
	 * @param ctx the parse tree
	 */
	void enterUndefinedLiteral(USEParser.UndefinedLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#undefinedLiteral}.
	 * @param ctx the parse tree
	 */
	void exitUndefinedLiteral(USEParser.UndefinedLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#tupleLiteral}.
	 * @param ctx the parse tree
	 */
	void enterTupleLiteral(USEParser.TupleLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#tupleLiteral}.
	 * @param ctx the parse tree
	 */
	void exitTupleLiteral(USEParser.TupleLiteralContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypedTupleItem}
	 * labeled alternative in {@link USEParser#tupleItem}.
	 * @param ctx the parse tree
	 */
	void enterTypedTupleItem(USEParser.TypedTupleItemContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypedTupleItem}
	 * labeled alternative in {@link USEParser#tupleItem}.
	 * @param ctx the parse tree
	 */
	void exitTypedTupleItem(USEParser.TypedTupleItemContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UntypedTupleItem}
	 * labeled alternative in {@link USEParser#tupleItem}.
	 * @param ctx the parse tree
	 */
	void enterUntypedTupleItem(USEParser.UntypedTupleItemContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UntypedTupleItem}
	 * labeled alternative in {@link USEParser#tupleItem}.
	 * @param ctx the parse tree
	 */
	void exitUntypedTupleItem(USEParser.UntypedTupleItemContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeSimple}
	 * labeled alternative in {@link USEParser#type}.
	 * @param ctx the parse tree
	 */
	void enterTypeSimple(USEParser.TypeSimpleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeSimple}
	 * labeled alternative in {@link USEParser#type}.
	 * @param ctx the parse tree
	 */
	void exitTypeSimple(USEParser.TypeSimpleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeCollection}
	 * labeled alternative in {@link USEParser#type}.
	 * @param ctx the parse tree
	 */
	void enterTypeCollection(USEParser.TypeCollectionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeCollection}
	 * labeled alternative in {@link USEParser#type}.
	 * @param ctx the parse tree
	 */
	void exitTypeCollection(USEParser.TypeCollectionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeTuple}
	 * labeled alternative in {@link USEParser#type}.
	 * @param ctx the parse tree
	 */
	void enterTypeTuple(USEParser.TypeTupleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeTuple}
	 * labeled alternative in {@link USEParser#type}.
	 * @param ctx the parse tree
	 */
	void exitTypeTuple(USEParser.TypeTupleContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#typeOnly}.
	 * @param ctx the parse tree
	 */
	void enterTypeOnly(USEParser.TypeOnlyContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#typeOnly}.
	 * @param ctx the parse tree
	 */
	void exitTypeOnly(USEParser.TypeOnlyContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#simpleType}.
	 * @param ctx the parse tree
	 */
	void enterSimpleType(USEParser.SimpleTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#simpleType}.
	 * @param ctx the parse tree
	 */
	void exitSimpleType(USEParser.SimpleTypeContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeSimpleCollection}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void enterTypeSimpleCollection(USEParser.TypeSimpleCollectionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeSimpleCollection}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void exitTypeSimpleCollection(USEParser.TypeSimpleCollectionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeSet}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void enterTypeSet(USEParser.TypeSetContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeSet}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void exitTypeSet(USEParser.TypeSetContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeSequence}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void enterTypeSequence(USEParser.TypeSequenceContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeSequence}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void exitTypeSequence(USEParser.TypeSequenceContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeBag}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void enterTypeBag(USEParser.TypeBagContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeBag}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void exitTypeBag(USEParser.TypeBagContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TypeOrderedSet}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void enterTypeOrderedSet(USEParser.TypeOrderedSetContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TypeOrderedSet}
	 * labeled alternative in {@link USEParser#collectionType}.
	 * @param ctx the parse tree
	 */
	void exitTypeOrderedSet(USEParser.TypeOrderedSetContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#tupleType}.
	 * @param ctx the parse tree
	 */
	void enterTupleType(USEParser.TupleTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#tupleType}.
	 * @param ctx the parse tree
	 */
	void exitTupleType(USEParser.TupleTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link USEParser#tuplePart}.
	 * @param ctx the parse tree
	 */
	void enterTuplePart(USEParser.TuplePartContext ctx);
	/**
	 * Exit a parse tree produced by {@link USEParser#tuplePart}.
	 * @param ctx the parse tree
	 */
	void exitTuplePart(USEParser.TuplePartContext ctx);
}