 
/*
 * HEADER TEST
 */



// Generated from USE.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  USEParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, T__61 = 62, 
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, WS = 68, 
    SL_COMMENT = 69, ML_COMMENT = 70, ARROW = 71, AT = 72, BAR = 73, COLON = 74, 
    COLON_COLON = 75, COLON_EQUAL = 76, COMMA = 77, DOT = 78, DOTDOT = 79, 
    EQUAL = 80, GREATER = 81, GREATER_EQUAL = 82, HASH = 83, LBRACE = 84, 
    LBRACK = 85, LESS = 86, LESS_EQUAL = 87, LPAREN = 88, MINUS = 89, NOT_EQUAL = 90, 
    PLUS = 91, RBRACE = 92, RBRACK = 93, RPAREN = 94, SEMI = 95, SLASH = 96, 
    STAR = 97, ABSTRACT = 98, EXISTENTIAL = 99, AGGREGATION = 100, COMPOSITION = 101, 
    ORDERED = 102, UNION = 103, NO_NAVIGABLE = 104, PUBLIC = 105, PRIVATE = 106, 
    PROTECTED = 107, PACKAGE = 108, INT = 109, REAL = 110, SOIL_OPERATION = 111, 
    STRING = 112, NON_OCL_STRING = 113, ID = 114
  };

  enum {
    RuleModel = 0, RuleModelElement = 1, RuleEnumTypeDefinition = 2, RuleClassDefinition = 3, 
    RuleAssociationClassDefinition = 4, RuleAttributeDefinition = 5, RuleInitDefinition = 6, 
    RuleDerivedDefinition = 7, RuleVisibilty = 8, RuleOperationDefinition = 9, 
    RuleAssociationDefinition = 10, RuleAssociationEnd = 11, RuleRole = 12, 
    RuleRedefines = 13, RuleSubsets = 14, RuleMultiplicity = 15, RuleMultiplicityRange = 16, 
    RuleMultiplicitySpec = 17, RuleConstraintDefinition = 18, RuleInvariant = 19, 
    RuleInvariantClause = 20, RulePrePost = 21, RulePrePostClause = 22, 
    RuleStateMachine = 23, RuleStateDefinition = 24, RuleTransitionDefinition = 25, 
    RuleExpressionOnly = 26, RuleExpression = 27, RuleLetExpression = 28, 
    RuleLogicalExpression = 29, RuleParamList = 30, RuleIdList = 31, RuleVariableDeclaration = 32, 
    RuleEqualityExpression = 33, RuleRelationalExpression = 34, RuleAdditiveExpression = 35, 
    RuleFactorExpression = 36, RuleUnaryExpression = 37, RulePostfixExpression = 38, 
    RulePropertyChain = 39, RulePrimaryExpression = 40, RuleObjectReference = 41, 
    RulePropertyCall = 42, RuleQueryExpression = 43, RuleIterateExpression = 44, 
    RuleOperationExpression = 45, RuleInStateExpression = 46, RuleTypeExpression = 47, 
    RuleElemVarsDeclaration = 48, RuleVariableInitialization = 49, RuleConditionalExpression = 50, 
    RuleLiteral = 51, RuleCollectionLiteral = 52, RuleCollectionItem = 53, 
    RuleEmptyCollectionLiteral = 54, RuleUndefinedLiteral = 55, RuleTupleLiteral = 56, 
    RuleTupleItem = 57, RuleType = 58, RuleTypeOnly = 59, RuleSimpleType = 60, 
    RuleCollectionType = 61, RuleTupleType = 62, RuleTuplePart = 63
  };

  explicit USEParser(antlr4::TokenStream *input);

  USEParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~USEParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ModelContext;
  class ModelElementContext;
  class EnumTypeDefinitionContext;
  class ClassDefinitionContext;
  class AssociationClassDefinitionContext;
  class AttributeDefinitionContext;
  class InitDefinitionContext;
  class DerivedDefinitionContext;
  class VisibiltyContext;
  class OperationDefinitionContext;
  class AssociationDefinitionContext;
  class AssociationEndContext;
  class RoleContext;
  class RedefinesContext;
  class SubsetsContext;
  class MultiplicityContext;
  class MultiplicityRangeContext;
  class MultiplicitySpecContext;
  class ConstraintDefinitionContext;
  class InvariantContext;
  class InvariantClauseContext;
  class PrePostContext;
  class PrePostClauseContext;
  class StateMachineContext;
  class StateDefinitionContext;
  class TransitionDefinitionContext;
  class ExpressionOnlyContext;
  class ExpressionContext;
  class LetExpressionContext;
  class LogicalExpressionContext;
  class ParamListContext;
  class IdListContext;
  class VariableDeclarationContext;
  class EqualityExpressionContext;
  class RelationalExpressionContext;
  class AdditiveExpressionContext;
  class FactorExpressionContext;
  class UnaryExpressionContext;
  class PostfixExpressionContext;
  class PropertyChainContext;
  class PrimaryExpressionContext;
  class ObjectReferenceContext;
  class PropertyCallContext;
  class QueryExpressionContext;
  class IterateExpressionContext;
  class OperationExpressionContext;
  class InStateExpressionContext;
  class TypeExpressionContext;
  class ElemVarsDeclarationContext;
  class VariableInitializationContext;
  class ConditionalExpressionContext;
  class LiteralContext;
  class CollectionLiteralContext;
  class CollectionItemContext;
  class EmptyCollectionLiteralContext;
  class UndefinedLiteralContext;
  class TupleLiteralContext;
  class TupleItemContext;
  class TypeContext;
  class TypeOnlyContext;
  class SimpleTypeContext;
  class CollectionTypeContext;
  class TupleTypeContext;
  class TuplePartContext; 

  class  ModelContext : public antlr4::ParserRuleContext {
  public:
    ModelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EOF();
    std::vector<ModelElementContext *> modelElement();
    ModelElementContext* modelElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModelContext* model();

  class  ModelElementContext : public antlr4::ParserRuleContext {
  public:
    ModelElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ModelElementContext() = default;
    void copyFrom(ModelElementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EnumContext : public ModelElementContext {
  public:
    EnumContext(ModelElementContext *ctx);

    EnumTypeDefinitionContext *enumTypeDefinition();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssociationContext : public ModelElementContext {
  public:
    AssociationContext(ModelElementContext *ctx);

    AssociationDefinitionContext *associationDefinition();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstraintsContext : public ModelElementContext {
  public:
    ConstraintsContext(ModelElementContext *ctx);

    std::vector<ConstraintDefinitionContext *> constraintDefinition();
    ConstraintDefinitionContext* constraintDefinition(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassContext : public ModelElementContext {
  public:
    ClassContext(ModelElementContext *ctx);

    ClassDefinitionContext *classDefinition();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssociationClassContext : public ModelElementContext {
  public:
    AssociationClassContext(ModelElementContext *ctx);

    AssociationClassDefinitionContext *associationClassDefinition();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ModelElementContext* modelElement();

  class  EnumTypeDefinitionContext : public antlr4::ParserRuleContext {
  public:
    EnumTypeDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LBRACE();
    IdListContext *idList();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *SEMI();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumTypeDefinitionContext* enumTypeDefinition();

  class  ClassDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ClassDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ABSTRACT();
    antlr4::tree::TerminalNode *LESS();
    IdListContext *idList();
    std::vector<AttributeDefinitionContext *> attributeDefinition();
    AttributeDefinitionContext* attributeDefinition(size_t i);
    std::vector<OperationDefinitionContext *> operationDefinition();
    OperationDefinitionContext* operationDefinition(size_t i);
    std::vector<InvariantClauseContext *> invariantClause();
    InvariantClauseContext* invariantClause(size_t i);
    std::vector<StateMachineContext *> stateMachine();
    StateMachineContext* stateMachine(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassDefinitionContext* classDefinition();

  class  AssociationClassDefinitionContext : public antlr4::ParserRuleContext {
  public:
    AssociationClassDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ABSTRACT();
    antlr4::tree::TerminalNode *LESS();
    IdListContext *idList();
    std::vector<AssociationEndContext *> associationEnd();
    AssociationEndContext* associationEnd(size_t i);
    antlr4::tree::TerminalNode *AGGREGATION();
    antlr4::tree::TerminalNode *COMPOSITION();
    std::vector<AttributeDefinitionContext *> attributeDefinition();
    AttributeDefinitionContext* attributeDefinition(size_t i);
    std::vector<OperationDefinitionContext *> operationDefinition();
    OperationDefinitionContext* operationDefinition(size_t i);
    std::vector<InvariantClauseContext *> invariantClause();
    InvariantClauseContext* invariantClause(size_t i);
    std::vector<StateMachineContext *> stateMachine();
    StateMachineContext* stateMachine(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssociationClassDefinitionContext* associationClassDefinition();

  class  AttributeDefinitionContext : public antlr4::ParserRuleContext {
  public:
    AttributeDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    VisibiltyContext *visibilty();
    InitDefinitionContext *initDefinition();
    DerivedDefinitionContext *derivedDefinition();
    antlr4::tree::TerminalNode *SEMI();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeDefinitionContext* attributeDefinition();

  class  InitDefinitionContext : public antlr4::ParserRuleContext {
  public:
    InitDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *EQUAL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitDefinitionContext* initDefinition();

  class  DerivedDefinitionContext : public antlr4::ParserRuleContext {
  public:
    DerivedDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *EQUAL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DerivedDefinitionContext* derivedDefinition();

  class  VisibiltyContext : public antlr4::ParserRuleContext {
  public:
    VisibiltyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PUBLIC();
    antlr4::tree::TerminalNode *PRIVATE();
    antlr4::tree::TerminalNode *PROTECTED();
    antlr4::tree::TerminalNode *PACKAGE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VisibiltyContext* visibilty();

  class  OperationDefinitionContext : public antlr4::ParserRuleContext {
  public:
    OperationDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ParamListContext *paramList();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    VisibiltyContext *visibilty();
    antlr4::tree::TerminalNode *SOIL_OPERATION();
    std::vector<PrePostClauseContext *> prePostClause();
    PrePostClauseContext* prePostClause(size_t i);
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperationDefinitionContext* operationDefinition();

  class  AssociationDefinitionContext : public antlr4::ParserRuleContext {
  public:
    AssociationDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AssociationDefinitionContext() = default;
    void copyFrom(AssociationDefinitionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AggregationContext : public AssociationDefinitionContext {
  public:
    AggregationContext(AssociationDefinitionContext *ctx);

    antlr4::tree::TerminalNode *AGGREGATION();
    antlr4::tree::TerminalNode *ID();
    std::vector<AssociationEndContext *> associationEnd();
    AssociationEndContext* associationEnd(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CompositionContext : public AssociationDefinitionContext {
  public:
    CompositionContext(AssociationDefinitionContext *ctx);

    antlr4::tree::TerminalNode *COMPOSITION();
    antlr4::tree::TerminalNode *ID();
    std::vector<AssociationEndContext *> associationEnd();
    AssociationEndContext* associationEnd(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SimpleAssociationContext : public AssociationDefinitionContext {
  public:
    SimpleAssociationContext(AssociationDefinitionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    std::vector<AssociationEndContext *> associationEnd();
    AssociationEndContext* associationEnd(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AssociationDefinitionContext* associationDefinition();

  class  AssociationEndContext : public antlr4::ParserRuleContext {
  public:
    AssociationEndContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LBRACK();
    MultiplicityContext *multiplicity();
    antlr4::tree::TerminalNode *RBRACK();
    RoleContext *role();
    antlr4::tree::TerminalNode *NO_NAVIGABLE();
    VisibiltyContext *visibilty();
    std::vector<antlr4::tree::TerminalNode *> ORDERED();
    antlr4::tree::TerminalNode* ORDERED(size_t i);
    std::vector<SubsetsContext *> subsets();
    SubsetsContext* subsets(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNION();
    antlr4::tree::TerminalNode* UNION(size_t i);
    std::vector<RedefinesContext *> redefines();
    RedefinesContext* redefines(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<ParamListContext *> paramList();
    ParamListContext* paramList(size_t i);
    antlr4::tree::TerminalNode *SEMI();
    std::vector<antlr4::tree::TerminalNode *> LPAREN();
    antlr4::tree::TerminalNode* LPAREN(size_t i);
    std::vector<ElemVarsDeclarationContext *> elemVarsDeclaration();
    ElemVarsDeclarationContext* elemVarsDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RPAREN();
    antlr4::tree::TerminalNode* RPAREN(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssociationEndContext* associationEnd();

  class  RoleContext : public antlr4::ParserRuleContext {
  public:
    RoleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RoleContext* role();

  class  RedefinesContext : public antlr4::ParserRuleContext {
  public:
    RedefinesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RedefinesContext* redefines();

  class  SubsetsContext : public antlr4::ParserRuleContext {
  public:
    SubsetsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubsetsContext* subsets();

  class  MultiplicityContext : public antlr4::ParserRuleContext {
  public:
    MultiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicityRangeContext *> multiplicityRange();
    MultiplicityRangeContext* multiplicityRange(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicityContext* multiplicity();

  class  MultiplicityRangeContext : public antlr4::ParserRuleContext {
  public:
    MultiplicityRangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicitySpecContext *> multiplicitySpec();
    MultiplicitySpecContext* multiplicitySpec(size_t i);
    antlr4::tree::TerminalNode *DOTDOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicityRangeContext* multiplicityRange();

  class  MultiplicitySpecContext : public antlr4::ParserRuleContext {
  public:
    MultiplicitySpecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *STAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicitySpecContext* multiplicitySpec();

  class  ConstraintDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ConstraintDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ConstraintDefinitionContext() = default;
    void copyFrom(ConstraintDefinitionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PrePostDefinitionContext : public ConstraintDefinitionContext {
  public:
    PrePostDefinitionContext(ConstraintDefinitionContext *ctx);

    PrePostContext *prePost();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InvariantDefinitionContext : public ConstraintDefinitionContext {
  public:
    InvariantDefinitionContext(ConstraintDefinitionContext *ctx);

    InvariantContext *invariant();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConstraintDefinitionContext* constraintDefinition();

  class  InvariantContext : public antlr4::ParserRuleContext {
  public:
    InvariantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimpleTypeContext *simpleType();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *COLON();
    std::vector<InvariantClauseContext *> invariantClause();
    InvariantClauseContext* invariantClause(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantContext* invariant();

  class  InvariantClauseContext : public antlr4::ParserRuleContext {
  public:
    InvariantClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EXISTENTIAL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantClauseContext* invariantClause();

  class  PrePostContext : public antlr4::ParserRuleContext {
  public:
    PrePostContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *COLON_COLON();
    ParamListContext *paramList();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    std::vector<PrePostClauseContext *> prePostClause();
    PrePostClauseContext* prePostClause(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrePostContext* prePost();

  class  PrePostClauseContext : public antlr4::ParserRuleContext {
  public:
    PrePostClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrePostClauseContext() = default;
    void copyFrom(PrePostClauseContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PreConditionContext : public PrePostClauseContext {
  public:
    PreConditionContext(PrePostClauseContext *ctx);

    antlr4::tree::TerminalNode *COLON();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PostConditionContext : public PrePostClauseContext {
  public:
    PostConditionContext(PrePostClauseContext *ctx);

    antlr4::tree::TerminalNode *COLON();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrePostClauseContext* prePostClause();

  class  StateMachineContext : public antlr4::ParserRuleContext {
  public:
    StateMachineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    std::vector<StateDefinitionContext *> stateDefinition();
    StateDefinitionContext* stateDefinition(size_t i);
    std::vector<TransitionDefinitionContext *> transitionDefinition();
    TransitionDefinitionContext* transitionDefinition(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StateMachineContext* stateMachine();

  class  StateDefinitionContext : public antlr4::ParserRuleContext {
  public:
    StateDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *LBRACK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACK();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StateDefinitionContext* stateDefinition();

  class  TransitionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    TransitionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> LBRACK();
    antlr4::tree::TerminalNode* LBRACK(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACK();
    antlr4::tree::TerminalNode* RBRACK(size_t i);
    ParamListContext *paramList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TransitionDefinitionContext* transitionDefinition();

  class  ExpressionOnlyContext : public antlr4::ParserRuleContext {
  public:
    ExpressionOnlyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionOnlyContext* expressionOnly();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LetExprContext : public ExpressionContext {
  public:
    LetExprContext(ExpressionContext *ctx);

    LetExpressionContext *letExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConditionalExprContext : public ExpressionContext {
  public:
    ConditionalExprContext(ExpressionContext *ctx);

    ConditionalExpressionContext *conditionalExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalExprContext : public ExpressionContext {
  public:
    LogicalExprContext(ExpressionContext *ctx);

    LogicalExpressionContext *logicalExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();

  class  LetExpressionContext : public antlr4::ParserRuleContext {
  public:
    LetExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EQUAL();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LetExpressionContext* letExpression();

  class  LogicalExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LogicalExpressionContext() = default;
    void copyFrom(LogicalExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AndExprContext : public LogicalExpressionContext {
  public:
    AndExprContext(LogicalExpressionContext *ctx);

    std::vector<LogicalExpressionContext *> logicalExpression();
    LogicalExpressionContext* logicalExpression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EqualityExprContext : public LogicalExpressionContext {
  public:
    EqualityExprContext(LogicalExpressionContext *ctx);

    EqualityExpressionContext *equalityExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  XorExprContext : public LogicalExpressionContext {
  public:
    XorExprContext(LogicalExpressionContext *ctx);

    std::vector<LogicalExpressionContext *> logicalExpression();
    LogicalExpressionContext* logicalExpression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ImpliesExprContext : public LogicalExpressionContext {
  public:
    ImpliesExprContext(LogicalExpressionContext *ctx);

    std::vector<LogicalExpressionContext *> logicalExpression();
    LogicalExpressionContext* logicalExpression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OrExprContext : public LogicalExpressionContext {
  public:
    OrExprContext(LogicalExpressionContext *ctx);

    std::vector<LogicalExpressionContext *> logicalExpression();
    LogicalExpressionContext* logicalExpression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LogicalExpressionContext* logicalExpression();
  LogicalExpressionContext* logicalExpression(int precedence);
  class  ParamListContext : public antlr4::ParserRuleContext {
  public:
    ParamListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamListContext* paramList();

  class  IdListContext : public antlr4::ParserRuleContext {
  public:
    IdListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdListContext* idList();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  EqualityExpressionContext : public antlr4::ParserRuleContext {
  public:
    EqualityExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    EqualityExpressionContext() = default;
    void copyFrom(EqualityExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EqualExprContext : public EqualityExpressionContext {
  public:
    EqualExprContext(EqualityExpressionContext *ctx);

    EqualityExpressionContext *equalityExpression();
    antlr4::tree::TerminalNode *EQUAL();
    RelationalExpressionContext *relationalExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RelationalExprContext : public EqualityExpressionContext {
  public:
    RelationalExprContext(EqualityExpressionContext *ctx);

    RelationalExpressionContext *relationalExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotEqualExprContext : public EqualityExpressionContext {
  public:
    NotEqualExprContext(EqualityExpressionContext *ctx);

    EqualityExpressionContext *equalityExpression();
    antlr4::tree::TerminalNode *NOT_EQUAL();
    RelationalExpressionContext *relationalExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  EqualityExpressionContext* equalityExpression();
  EqualityExpressionContext* equalityExpression(int precedence);
  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    RelationalExpressionContext() = default;
    void copyFrom(RelationalExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LessThanOrEqualExprContext : public RelationalExpressionContext {
  public:
    LessThanOrEqualExprContext(RelationalExpressionContext *ctx);

    RelationalExpressionContext *relationalExpression();
    antlr4::tree::TerminalNode *LESS_EQUAL();
    AdditiveExpressionContext *additiveExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GreaterThanExprContext : public RelationalExpressionContext {
  public:
    GreaterThanExprContext(RelationalExpressionContext *ctx);

    RelationalExpressionContext *relationalExpression();
    antlr4::tree::TerminalNode *GREATER();
    AdditiveExpressionContext *additiveExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AdditiveExprContext : public RelationalExpressionContext {
  public:
    AdditiveExprContext(RelationalExpressionContext *ctx);

    AdditiveExpressionContext *additiveExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LessThanExprContext : public RelationalExpressionContext {
  public:
    LessThanExprContext(RelationalExpressionContext *ctx);

    RelationalExpressionContext *relationalExpression();
    antlr4::tree::TerminalNode *LESS();
    AdditiveExpressionContext *additiveExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GreaterThanOrEqualExprContext : public RelationalExpressionContext {
  public:
    GreaterThanOrEqualExprContext(RelationalExpressionContext *ctx);

    RelationalExpressionContext *relationalExpression();
    antlr4::tree::TerminalNode *GREATER_EQUAL();
    AdditiveExpressionContext *additiveExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  RelationalExpressionContext* relationalExpression();
  RelationalExpressionContext* relationalExpression(int precedence);
  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AdditiveExpressionContext() = default;
    void copyFrom(AdditiveExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AdditionExprContext : public AdditiveExpressionContext {
  public:
    AdditionExprContext(AdditiveExpressionContext *ctx);

    AdditiveExpressionContext *additiveExpression();
    antlr4::tree::TerminalNode *PLUS();
    FactorExpressionContext *factorExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubtractionExprContext : public AdditiveExpressionContext {
  public:
    SubtractionExprContext(AdditiveExpressionContext *ctx);

    AdditiveExpressionContext *additiveExpression();
    antlr4::tree::TerminalNode *MINUS();
    FactorExpressionContext *factorExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FactorExprContext : public AdditiveExpressionContext {
  public:
    FactorExprContext(AdditiveExpressionContext *ctx);

    FactorExpressionContext *factorExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AdditiveExpressionContext* additiveExpression();
  AdditiveExpressionContext* additiveExpression(int precedence);
  class  FactorExpressionContext : public antlr4::ParserRuleContext {
  public:
    FactorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FactorExpressionContext() = default;
    void copyFrom(FactorExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DivisionExprContext : public FactorExpressionContext {
  public:
    DivisionExprContext(FactorExpressionContext *ctx);

    FactorExpressionContext *factorExpression();
    UnaryExpressionContext *unaryExpression();
    antlr4::tree::TerminalNode *SLASH();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MultiplicationExprContext : public FactorExpressionContext {
  public:
    MultiplicationExprContext(FactorExpressionContext *ctx);

    FactorExpressionContext *factorExpression();
    antlr4::tree::TerminalNode *STAR();
    UnaryExpressionContext *unaryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExprContext : public FactorExpressionContext {
  public:
    UnaryExprContext(FactorExpressionContext *ctx);

    UnaryExpressionContext *unaryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FactorExpressionContext* factorExpression();
  FactorExpressionContext* factorExpression(int precedence);
  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryExpressionContext() = default;
    void copyFrom(UnaryExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PostfixExprContext : public UnaryExpressionContext {
  public:
    PostfixExprContext(UnaryExpressionContext *ctx);

    PostfixExpressionContext *postfixExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PlusExprContext : public UnaryExpressionContext {
  public:
    PlusExprContext(UnaryExpressionContext *ctx);

    antlr4::tree::TerminalNode *PLUS();
    UnaryExpressionContext *unaryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotExprContext : public UnaryExpressionContext {
  public:
    NotExprContext(UnaryExpressionContext *ctx);

    UnaryExpressionContext *unaryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MinusExprContext : public UnaryExpressionContext {
  public:
    MinusExprContext(UnaryExpressionContext *ctx);

    antlr4::tree::TerminalNode *MINUS();
    UnaryExpressionContext *unaryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryExpressionContext* unaryExpression();

  class  PostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    PostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PostfixExpressionContext() = default;
    void copyFrom(PostfixExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PropertyCallExprContext : public PostfixExpressionContext {
  public:
    PropertyCallExprContext(PostfixExpressionContext *ctx);

    PrimaryExpressionContext *primaryExpression();
    std::vector<PropertyChainContext *> propertyChain();
    PropertyChainContext* propertyChain(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PrimaryExprContext : public PostfixExpressionContext {
  public:
    PrimaryExprContext(PostfixExpressionContext *ctx);

    PrimaryExpressionContext *primaryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PostfixExpressionContext* postfixExpression();

  class  PropertyChainContext : public antlr4::ParserRuleContext {
  public:
    PropertyChainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyCallContext *propertyCall();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *ARROW();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyChainContext* propertyChain();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryExpressionContext() = default;
    void copyFrom(PrimaryExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EmptyPropertyCallExprContext : public PrimaryExpressionContext {
  public:
    EmptyPropertyCallExprContext(PrimaryExpressionContext *ctx);

    PropertyCallContext *propertyCall();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ByUseIdExprContext : public PrimaryExpressionContext {
  public:
    ByUseIdExprContext(PrimaryExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *AT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralExprContext : public PrimaryExpressionContext {
  public:
    LiteralExprContext(PrimaryExpressionContext *ctx);

    LiteralContext *literal();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesizedExprContext : public PrimaryExpressionContext {
  public:
    ParenthesizedExprContext(PrimaryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AllInstancesExprContext : public PrimaryExpressionContext {
  public:
    AllInstancesExprContext(PrimaryExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *AT();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ObjectReferenceExprContext : public PrimaryExpressionContext {
  public:
    ObjectReferenceExprContext(PrimaryExpressionContext *ctx);

    ObjectReferenceContext *objectReference();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrimaryExpressionContext* primaryExpression();

  class  ObjectReferenceContext : public antlr4::ParserRuleContext {
  public:
    ObjectReferenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT();
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectReferenceContext* objectReference();

  class  PropertyCallContext : public antlr4::ParserRuleContext {
  public:
    PropertyCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PropertyCallContext() = default;
    void copyFrom(PropertyCallContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  QueryExprContext : public PropertyCallContext {
  public:
    QueryExprContext(PropertyCallContext *ctx);

    QueryExpressionContext *queryExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OperationExprContext : public PropertyCallContext {
  public:
    OperationExprContext(PropertyCallContext *ctx);

    OperationExpressionContext *operationExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IterateExprContext : public PropertyCallContext {
  public:
    IterateExprContext(PropertyCallContext *ctx);

    IterateExpressionContext *iterateExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeExprContext : public PropertyCallContext {
  public:
    TypeExprContext(PropertyCallContext *ctx);

    TypeExpressionContext *typeExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InStateExprContext : public PropertyCallContext {
  public:
    InStateExprContext(PropertyCallContext *ctx);

    InStateExpressionContext *inStateExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PropertyCallContext* propertyCall();

  class  QueryExpressionContext : public antlr4::ParserRuleContext {
  public:
    QueryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    QueryExpressionContext() = default;
    void copyFrom(QueryExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IsUniqueExprContext : public QueryExpressionContext {
  public:
    IsUniqueExprContext(QueryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *BAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SortedByExprContext : public QueryExpressionContext {
  public:
    SortedByExprContext(QueryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *BAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SelectExprContext : public QueryExpressionContext {
  public:
    SelectExprContext(QueryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *BAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CollectExprContext : public QueryExpressionContext {
  public:
    CollectExprContext(QueryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *BAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForAllExprContext : public QueryExpressionContext {
  public:
    ForAllExprContext(QueryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *BAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExistsExprContext : public QueryExpressionContext {
  public:
    ExistsExprContext(QueryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *BAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RejectExprContext : public QueryExpressionContext {
  public:
    RejectExprContext(QueryExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *BAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  QueryExpressionContext* queryExpression();

  class  IterateExpressionContext : public antlr4::ParserRuleContext {
  public:
    IterateExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    ElemVarsDeclarationContext *elemVarsDeclaration();
    antlr4::tree::TerminalNode *SEMI();
    VariableInitializationContext *variableInitialization();
    antlr4::tree::TerminalNode *BAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IterateExpressionContext* iterateExpression();

  class  OperationExpressionContext : public antlr4::ParserRuleContext {
  public:
    OperationExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    std::vector<antlr4::tree::TerminalNode *> LBRACK();
    antlr4::tree::TerminalNode* LBRACK(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACK();
    antlr4::tree::TerminalNode* RBRACK(size_t i);
    antlr4::tree::TerminalNode *AT();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperationExpressionContext* operationExpression();

  class  InStateExpressionContext : public antlr4::ParserRuleContext {
  public:
    InStateExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InStateExpressionContext* inStateExpression();

  class  TypeExpressionContext : public antlr4::ParserRuleContext {
  public:
    TypeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeExpressionContext() = default;
    void copyFrom(TypeExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  OclIsTypeOfExprContext : public TypeExpressionContext {
  public:
    OclIsTypeOfExprContext(TypeExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OclIsKindOfExprContext : public TypeExpressionContext {
  public:
    OclIsKindOfExprContext(TypeExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SelectByKindExprContext : public TypeExpressionContext {
  public:
    SelectByKindExprContext(TypeExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SelectByTypeExprContext : public TypeExpressionContext {
  public:
    SelectByTypeExprContext(TypeExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OclAsTypeExprContext : public TypeExpressionContext {
  public:
    OclAsTypeExprContext(TypeExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeExpressionContext* typeExpression();

  class  ElemVarsDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ElemVarsDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElemVarsDeclarationContext* elemVarsDeclaration();

  class  VariableInitializationContext : public antlr4::ParserRuleContext {
  public:
    VariableInitializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableInitializationContext* variableInitialization();

  class  ConditionalExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionalExpressionContext* conditionalExpression();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LiteralContext() = default;
    void copyFrom(LiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LiteralIntegerContext : public LiteralContext {
  public:
    LiteralIntegerContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralEmptyCollectionContext : public LiteralContext {
  public:
    LiteralEmptyCollectionContext(LiteralContext *ctx);

    EmptyCollectionLiteralContext *emptyCollectionLiteral();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralStringContext : public LiteralContext {
  public:
    LiteralStringContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *STRING();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralUnlimitedNaturalContext : public LiteralContext {
  public:
    LiteralUnlimitedNaturalContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *STAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralCollectionContext : public LiteralContext {
  public:
    LiteralCollectionContext(LiteralContext *ctx);

    CollectionLiteralContext *collectionLiteral();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralBooleanFalseContext : public LiteralContext {
  public:
    LiteralBooleanFalseContext(LiteralContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralEnumContext : public LiteralContext {
  public:
    LiteralEnumContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *HASH();
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralQualifiedEnumContext : public LiteralContext {
  public:
    LiteralQualifiedEnumContext(LiteralContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *COLON_COLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralUndefinedContext : public LiteralContext {
  public:
    LiteralUndefinedContext(LiteralContext *ctx);

    UndefinedLiteralContext *undefinedLiteral();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralTupleContext : public LiteralContext {
  public:
    LiteralTupleContext(LiteralContext *ctx);

    TupleLiteralContext *tupleLiteral();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralBooleanTrueContext : public LiteralContext {
  public:
    LiteralBooleanTrueContext(LiteralContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralRealContext : public LiteralContext {
  public:
    LiteralRealContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *REAL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LiteralContext* literal();

  class  CollectionLiteralContext : public antlr4::ParserRuleContext {
  public:
    CollectionLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    CollectionLiteralContext() = default;
    void copyFrom(CollectionLiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  OrderedSetLiteralContext : public CollectionLiteralContext {
  public:
    OrderedSetLiteralContext(CollectionLiteralContext *ctx);

    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<CollectionItemContext *> collectionItem();
    CollectionItemContext* collectionItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SequenceLiteralContext : public CollectionLiteralContext {
  public:
    SequenceLiteralContext(CollectionLiteralContext *ctx);

    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<CollectionItemContext *> collectionItem();
    CollectionItemContext* collectionItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BagLiteralContext : public CollectionLiteralContext {
  public:
    BagLiteralContext(CollectionLiteralContext *ctx);

    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<CollectionItemContext *> collectionItem();
    CollectionItemContext* collectionItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SetLiteralContext : public CollectionLiteralContext {
  public:
    SetLiteralContext(CollectionLiteralContext *ctx);

    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<CollectionItemContext *> collectionItem();
    CollectionItemContext* collectionItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CollectionLiteralContext* collectionLiteral();

  class  CollectionItemContext : public antlr4::ParserRuleContext {
  public:
    CollectionItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *DOTDOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CollectionItemContext* collectionItem();

  class  EmptyCollectionLiteralContext : public antlr4::ParserRuleContext {
  public:
    EmptyCollectionLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    CollectionTypeContext *collectionType();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmptyCollectionLiteralContext* emptyCollectionLiteral();

  class  UndefinedLiteralContext : public antlr4::ParserRuleContext {
  public:
    UndefinedLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UndefinedLiteralContext* undefinedLiteral();

  class  TupleLiteralContext : public antlr4::ParserRuleContext {
  public:
    TupleLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<TupleItemContext *> tupleItem();
    TupleItemContext* tupleItem(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TupleLiteralContext* tupleLiteral();

  class  TupleItemContext : public antlr4::ParserRuleContext {
  public:
    TupleItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TupleItemContext() = default;
    void copyFrom(TupleItemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  UntypedTupleItemContext : public TupleItemContext {
  public:
    UntypedTupleItemContext(TupleItemContext *ctx);

    antlr4::tree::TerminalNode *ID();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *EQUAL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypedTupleItemContext : public TupleItemContext {
  public:
    TypedTupleItemContext(TupleItemContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TupleItemContext* tupleItem();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeContext() = default;
    void copyFrom(TypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TypeTupleContext : public TypeContext {
  public:
    TypeTupleContext(TypeContext *ctx);

    TupleTypeContext *tupleType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeCollectionContext : public TypeContext {
  public:
    TypeCollectionContext(TypeContext *ctx);

    CollectionTypeContext *collectionType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeSimpleContext : public TypeContext {
  public:
    TypeSimpleContext(TypeContext *ctx);

    SimpleTypeContext *simpleType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeContext* type();

  class  TypeOnlyContext : public antlr4::ParserRuleContext {
  public:
    TypeOnlyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeOnlyContext* typeOnly();

  class  SimpleTypeContext : public antlr4::ParserRuleContext {
  public:
    SimpleTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleTypeContext* simpleType();

  class  CollectionTypeContext : public antlr4::ParserRuleContext {
  public:
    CollectionTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    CollectionTypeContext() = default;
    void copyFrom(CollectionTypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TypeBagContext : public CollectionTypeContext {
  public:
    TypeBagContext(CollectionTypeContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeSimpleCollectionContext : public CollectionTypeContext {
  public:
    TypeSimpleCollectionContext(CollectionTypeContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeOrderedSetContext : public CollectionTypeContext {
  public:
    TypeOrderedSetContext(CollectionTypeContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeSequenceContext : public CollectionTypeContext {
  public:
    TypeSequenceContext(CollectionTypeContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeSetContext : public CollectionTypeContext {
  public:
    TypeSetContext(CollectionTypeContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CollectionTypeContext* collectionType();

  class  TupleTypeContext : public antlr4::ParserRuleContext {
  public:
    TupleTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<TuplePartContext *> tuplePart();
    TuplePartContext* tuplePart(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TupleTypeContext* tupleType();

  class  TuplePartContext : public antlr4::ParserRuleContext {
  public:
    TuplePartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TuplePartContext* tuplePart();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool logicalExpressionSempred(LogicalExpressionContext *_localctx, size_t predicateIndex);
  bool equalityExpressionSempred(EqualityExpressionContext *_localctx, size_t predicateIndex);
  bool relationalExpressionSempred(RelationalExpressionContext *_localctx, size_t predicateIndex);
  bool additiveExpressionSempred(AdditiveExpressionContext *_localctx, size_t predicateIndex);
  bool factorExpressionSempred(FactorExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

