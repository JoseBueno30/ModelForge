grammar USE;

// set package for all generated classes
@header { 
/*
 * HEADER TEST
 */

}

/*
--------- Start of file USEBase.gpart -------------------- 
*/

// grammar start

/* ------------------------------------
  model ::= 
    "model" id {modelElement}
*/
model
  : 'model' ID modelElement* EOF;

/* ------------------------------------
  modelElement ::= 
        enumTypeDefinition
      | classDefinition 
      | associationDefinition 
      | associationClassDefinition
      | "constraints" { constraintDefinition }
*/

modelElement
  : enumTypeDefinition                  #Enum
  | classDefinition                     #Class
  | associationDefinition               #Association
  | associationClassDefinition          #AssociationClass
  | 'constraints' constraintDefinition* #Constraints
  ;
    
/* ------------------------------------
  enumTypeDefinition ::= 
    "enum" id "{" idList "}" [ ";" ]
*/
enumTypeDefinition
  : 'enum' ID LBRACE idList RBRACE ( SEMI )?
  ;

/* ------------------------------------
  classDefinition ::= 
    [ "abstract" ] "class" id [ specialization ] 
    [ attributes ] 
    [ operations ] 
    [ constraints ]
    [ statemachines ]
    "end"

  specialization ::= "<" idList
  attributes ::= "attributes" { attributeDefinition }
  operations ::= "operations" { operationDefinition }
  constraints ::= "constraints" { invariantClause }
  statemachines ::= "statemachines" { stateMachine }
*/
classDefinition
  : ABSTRACT? 'class' ID (LESS idList)?
  ('attributes'    attributeDefinition*)?
  ('operations'    operationDefinition*)?
  ('constraints'   invariantClause*)?
  ('statemachines' stateMachine*)?
  'end'
  ;

/* ------------------------------------
  associationClassDefinition ::= 
    [ "abstract" ] "associationClass" id [ specialization ] "between"
    associationEnd { associationEnd }+
    [ attributes ]
    [ operations ] 
    [ constraints ]
    [ statemachines ]
    [( "aggregation" | "composition" )]
    "end"

  specialization ::= "<" idList
  attributes ::= "attributes" { attributeDefinition }
  operations ::= "operations" { operationDefinition }
  constraints ::= "constraints" { invariantClause }
*/
associationClassDefinition
  : ABSTRACT? 'associationclass' ID (LESS idList)?
  ('between'       associationEnd associationEnd+)?
  ('attributes'    attributeDefinition*)?
  ('operations'    operationDefinition*)?
  ('constraints'   invariantClause*)?
  ('statemachines' stateMachine*)?
  (AGGREGATION | COMPOSITION)?
  'end'
  ;
    
/* ------------------------------------
  attributeDefinition ::= 
    id ":" type [initDefinition | derivedDefinition] [ ";" ]

    initDefinition ::= "init" (":" | "=") expression
    derivedDefinition ::= ("derive" | "derived") (":" | "=") expression
*/
attributeDefinition
    : ID COLON type visibilty? (initDefinition | derivedDefinition)? SEMI?
    ;

initDefinition
    : 'init' (COLON|EQUAL) expression
    ;

derivedDefinition
    : ('derive'|'derived') (COLON|EQUAL) expression
    ;

visibilty
    : PUBLIC
    | PRIVATE
    | PROTECTED
    | PACKAGE
    ;

/* ------------------------------------
  operationDefinition ::= 
    id paramList ":" type [ "=" expression ] 
    { prePostClause } [ ";" ]
*/
operationDefinition
    : ID paramList (COLON type)? visibilty?
    ( ( EQUAL expression ) | SOIL_OPERATION)? //USE can have SOIL operations but we dont care about them
    prePostClause*
    ( SEMI )?
    ;

/* ------------------------------------
  associationDefinition ::= 
    ( "association" | "aggregation" | "composition" ) 
    id "between"
    associationEnd associationEnd { associationEnd }
    "end"
*/
associationDefinition
    : 'association' ID 'between' associationEnd associationEnd+ 'end'    #SimpleAssociation
    | AGGREGATION ID 'between' associationEnd associationEnd+ 'end'    #Aggregation
    | COMPOSITION ID 'between' associationEnd associationEnd+ 'end'    #Composition
    ;


/* ------------------------------------
  associationEnd ::= 
    id "[" multiplicity "]" [ "role" id ] ( "ordered" | "subsets" id | "union" | "redefines" )* [ ";" ]
*/
associationEnd
    : ID LBRACK multiplicity RBRACK
    ( role)?
    (NO_NAVIGABLE)?
    visibilty?
    (
          ORDERED
        | subsets
        | UNION
        | redefines
        | ('derived'|'derive') ( LPAREN elemVarsDeclaration RPAREN)? EQUAL expression
        | 'qualifier' paramList
    )*
    (SEMI)?
    ;

role          
    : 'role' ID
    ;

redefines     
    : 'redefines' ID
    ;

subsets       
    : 'subsets' ID
    ;

/* ------------------------------------
  multiplicity ::= 
    multiplicityRange { "," multiplicityRange }

  multiplicityRange ::=
    multiplicitySpec [ ".." multiplicitySpec ]

  multiplicitySpec ::=
    "*" | INT
*/
multiplicity
    : multiplicityRange (COMMA multiplicityRange)*
    ;

multiplicityRange
    : multiplicitySpec (DOTDOT multiplicitySpec)?
    ;

multiplicitySpec
    : INT 
    | STAR  
    ;

/* ------------------------------------
  constraintDefinition ::= 
        invariant | prePost
*/

constraintDefinition
  : invariant   #InvariantDefinition
  | prePost     #PrePostDefinition
  ;

/* ------------------------------------
  invariant ::= 
    invariantContext invariantClause { invariantClause }

  invariantContext := 
    "context" [ id ":" ] simpleType
*/
invariant
    : 'context'
    (ID (',' ID)* COLON )?
    simpleType
    (invariantClause)*
    ;

/* ------------------------------------
  invariantClause ::= 
    "inv" [ id ] ":" expression
*/
invariantClause
    : 'inv' (ID)? COLON expression 
    | EXISTENTIAL 'inv' (ID)? COLON expression 
    ;


/* ------------------------------------
  prePost ::=
    prePostContext prePostClause { prePostClause }

  prePostContext := 
    "context" id "::" id paramList [ ":" type ]
*/
prePost
    : 'context' ID COLON_COLON ID paramList ( COLON type )?
    ( prePostClause )+
    ;

/* ------------------------------------
  prePostClause :=
    ("pre" | "post") [ id ] ":" expression
*/
prePostClause
    : 'pre' ( ID )? COLON expression     #PreCondition
    | 'post'( ID )? COLON expression     #PostCondition
	;

stateMachine
    : 'psm' ID
        'states' stateDefinition+
        'transitions' transitionDefinition+
        'end'
    ;

stateDefinition
    : ID
    ( COLON ID )? //( COLON ID )? define el tipo del estado (state: initial, state: final) en el codigo se comprueba si es un IDificador valido (final, el resto definidios en MPseudoStateKind), no se porq no en la gramatica pero bueno, por esto seguramente no haya que preocuparse
    ( LBRACK expression RBRACK )?
;

/* ------------------------------------
  transitionDefinition :=
    source "->" target ["{"[PreCondition] operation [PostCondition]"}"]

  source := id
  target := id
  PreCondition := "[" expression "]"
  PostCondition := "[" expression "]"
  operation := id "(" paramList ")"

*/

transitionDefinition
    : ID ARROW ID 
    (LBRACE 
      (LBRACK expression RBRACK)?
      (
        ID LPAREN (paramList )? RPAREN
      )
      (LBRACK expression RBRACK)?
    RBRACE)?
    ;

/*
--------- Start of file OCLBase.gpart -------------------- 
*/

/*
 * USE - UML based specification environment
 * Copyright (C) 1999-2012 University of Bremen
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  
 */
 
/* ------------------------------------
  expressionOnly ::= 
    conditionalImpliesExpression
*/
expressionOnly
    : expression EOF
    ;
 
/* ------------------------------------
  expression ::= 
    logicalExpression | conditionalExpresion | letExpression
*/
expression
    : logicalExpression       #LogicalExpr
    | conditionalExpression   #ConditionalExpr
    | letExpression           #LetExpr
    ;

/* ------------------------------------
  letExpression ::= 
    "let" id [ : type ] "=" expression "in" expression
*/
letExpression
  : 'let' ID ( COLON type )? EQUAL expression 'in' expression
  ;

logicalExpression
    : logicalExpression 'and' logicalExpression       #AndExpr
    | logicalExpression '&' logicalExpression         #AndExpr
    | logicalExpression 'or' logicalExpression        #OrExpr
    | logicalExpression 'xor' logicalExpression       #XorExpr
    | logicalExpression '=>' logicalExpression        #ImpliesExpr
    | logicalExpression 'implies' logicalExpression   #ImpliesExpr
    | equalityExpression                              #EqualityExpr
    ;


/* ------------------------------------
  paramList ::= 
    "(" [ variableDeclaration { "," variableDeclaration } ] ")"
*/
paramList
  : LPAREN ( variableDeclaration (COMMA variableDeclaration)* )? RPAREN
  ;

/* ------------------------------------
  idList ::= id { "," id }
*/
idList
  : ID (COMMA ID)*
  ;


/* ------------------------------------
  variableDeclaration ::= 
    id ":" type
*/
variableDeclaration
  : ID COLON type
  ;

/* ------------------------------------
  equalityExpression ::= 
    relationalExpression { ("=" | "<>") relationalExpression }
*/
equalityExpression
  : relationalExpression                                #RelationalExpr
  | equalityExpression EQUAL relationalExpression       #EqualExpr
  | equalityExpression NOT_EQUAL relationalExpression   #NotEqualExpr
  ;

/* ------------------------------------
  relationalExpression ::= 
    additiveExpression { ("<" | ">" | "<=" | ">=") additiveExpression }
*/
relationalExpression
    : additiveExpression                            #AdditiveExpr
    | relationalExpression '<' additiveExpression   #LessThanExpr
    | relationalExpression '>' additiveExpression   #GreaterThanExpr
    | relationalExpression '<=' additiveExpression  #LessThanOrEqualExpr
    | relationalExpression '>=' additiveExpression  #GreaterThanOrEqualExpr
    ;

/* ------------------------------------
  additiveExpression ::= 
    multiplicativeExpression { ("+" | "-") multiplicativeExpression }
*/
additiveExpression
    : factorExpression                          #FactorExpr
    | additiveExpression '+' factorExpression   #AdditionExpr
    | additiveExpression '-' factorExpression   #SubtractionExpr
    ;

/* ------------------------------------
  factorExpression ::= 
    unaryExpression { ("*" | "/" | "div") unaryExpression }
*/
factorExpression
  : unaryExpression                                   #UnaryExpr
  | factorExpression STAR unaryExpression             #MultiplicationExpr
  | factorExpression (SLASH | 'div') unaryExpression  #DivisionExpr 
  ;

/* ------------------------------------
  unaryExpression ::= 
      ( "not" | "-" | "+" ) unaryExpression
    | postfixExpression
*/
unaryExpression
  : 'not' unaryExpression   #NotExpr
  | MINUS unaryExpression   #MinusExpr
  | PLUS unaryExpression    #PlusExpr
  | postfixExpression       #PostfixExpr
  ;

/* ------------------------------------
  postfixExpression ::= 
      primaryExpression { ( "." | "->" ) propertyCall }
*/
postfixExpression
  : primaryExpression                  #PrimaryExpr
  | primaryExpression propertyChain+   #PropertyCallExpr
  ;

/* ------------------------------------
  propertyChain ::=
    ( "." | "->" ) propertyCall
 */
propertyChain 
  : (DOT | ARROW) propertyCall
  ;


/* ------------------------------------
  primaryExpression ::= 
      literal
    | propertyCall
    | "(" expression ")"

  Note: propertyCall includes variables
*/

primaryExpression
  : literal                                                   #LiteralExpr
  | objectReference                                           #ObjectReferenceExpr
  | propertyCall                                              #EmptyPropertyCallExpr
  | LPAREN expression RPAREN                                  #ParenthesizedExpr
  | ID DOT 'allInstances' (AT 'pre')? (LPAREN RPAREN)?     #AllInstancesExpr
  | ID DOT 'byUseId' LPAREN expression RPAREN (AT 'pre')?  #ByUseIdExpr
  ;


objectReference
  : AT ID
  ;

/* ------------------------------------
  propertyCall ::= 
      queryId   "(" [ elemVarsDeclaration "|" ] expression ")"
    | "iterate" "(" elemVarsDeclaration ";" variableInitialization "|" expression ")"
    | id [ "(" actualParameterList ")" ]


  Note: source may be null (see primaryExpression).
*/
propertyCall
  : queryExpression       #QueryExpr
  | iterateExpression     #IterateExpr
  | operationExpression   #OperationExpr
  | typeExpression        #TypeExpr
  | inStateExpression     #InStateExpr
  ;


/* ------------------------------------
  queryExpression ::= 
    ("select" | "reject" | "collect" | "exists" | "forAll" | "isUnique" | "sortedBy" ) 
    "(" [ elemVarsDeclaration "|" ] expression ")"
*/
queryExpression
    : 'select'    LPAREN ( elemVarsDeclaration BAR )? expression RPAREN  # SelectExpr
    | 'reject'    LPAREN ( elemVarsDeclaration BAR )? expression RPAREN  # RejectExpr
    | 'collect'   LPAREN ( elemVarsDeclaration BAR )? expression RPAREN  # CollectExpr
    | 'exists'    LPAREN ( elemVarsDeclaration BAR )? expression RPAREN  # ExistsExpr
    | 'forAll'    LPAREN ( elemVarsDeclaration BAR )? expression RPAREN  # ForAllExpr
    | 'isUnique'  LPAREN ( elemVarsDeclaration BAR )? expression RPAREN  # IsUniqueExpr
    | 'sortedBy'  LPAREN ( elemVarsDeclaration BAR )? expression RPAREN  # SortedByExpr
    ;

/* ------------------------------------
  iterateExpression ::= 
    "iterate" "(" 
    elemVarsDeclaration ";" 
    variableInitialization "|"
    expression ")"
*/
iterateExpression:
    'iterate'
    LPAREN
    elemVarsDeclaration SEMI
    variableInitialization BAR
    expression
    RPAREN
    ;


/* ------------------------------------
  operationExpression ::= 
    id ( ("[" id "]") 
       | ( [ "@" "pre" ] [ "(" [ expression { "," expression } ] ")" ] ) )

  No se corresponde con la implementación
*/

// Operations always require parentheses even if no arguments are
// required. This makes it easier, for example, to distinguish a
// class-defined operation from an attribute access operation where
// both operations may have the same name.

operationExpression //COMPROBAR IMPLEMENTACIÓN
  : ID
	// This is a little dirty, because either it is a navigation
	// along a m-ary association or a navigation over a qualified association 
	// or both.
  ( LBRACK expression (COMMA expression)* RBRACK ( LBRACK expression (COMMA expression)* RBRACK )? )?
  ( AT 'pre')?
  ( LPAREN ( expression (COMMA expression)* )? RPAREN )?
  ;

inStateExpression
  :'oclInState' LPAREN ID RPAREN
  ;

/* ------------------------------------
  typeExpression ::= 
    ("oclAsType" | "oclIsKindOf" | "oclIsTypeOf" | "selectByType" | "selectByKind" ) LPAREN type RPAREN
*/

typeExpression
  : 'oclAsType'     LPAREN type RPAREN  # OclAsTypeExpr
  | 'oclIsKindOf'   LPAREN type RPAREN  # OclIsKindOfExpr
  | 'oclIsTypeOf'   LPAREN type RPAREN  # OclIsTypeOfExpr
  | 'selectByType'  LPAREN type RPAREN  # SelectByTypeExpr
  | 'selectByKind'  LPAREN type RPAREN  # SelectByKindExpr
  ;


/* ------------------------------------
  elemVarsDeclaration ::= 
    id (":" type)? ("," id (":" type)?)*  
*/
elemVarsDeclaration
  : ID (COLON type)? (COMMA ID (COLON type)?)*
  ;


/* ------------------------------------
  variableInitialization ::= 
    id ":" type "=" expression
*/
variableInitialization
  : ID COLON type EQUAL expression
  ;


/* ------------------------------------
  conditionalExpression ::= 
    "if" expression "then" expression "else" expression "endif"
*/
conditionalExpression
  : 'if' expression 'then' expression 'else' expression 'endif'
  ;


/* ------------------------------------
  literal ::= 
      "true"
    | "false"
    | INT
    | REAL
    | STRING
    | "#" id
    | id "::" id
    | collectionLiteral
    | emptyCollectionLiteral
    | undefinedLiteral
    | tupleLiteral
*/
literal
    : 'true'                    # LiteralBooleanTrue
    | 'false'                   # LiteralBooleanFalse
    | INT                       # LiteralInteger
    | REAL                      # LiteralReal
    | STRING                    # LiteralString
    | HASH ID                # LiteralEnum
    | ID COLON_COLON ID   # LiteralQualifiedEnum
    | collectionLiteral         # LiteralCollection
    | emptyCollectionLiteral    # LiteralEmptyCollection
    | undefinedLiteral          # LiteralUndefined
    | tupleLiteral              # LiteralTuple
    | STAR                      # LiteralUnlimitedNatural
    ;


/* ------------------------------------
  collectionLiteral ::= 
    ( "Set" | "Sequence" | "Bag" | "OrderedSet" ) "{" collectionItem { "," collectionItem } "}"
*/
collectionLiteral
  : 'Set'         LBRACE (collectionItem (COMMA collectionItem)*)? RBRACE   # SetLiteral
  | 'Sequence'    LBRACE (collectionItem (COMMA collectionItem)*)? RBRACE   # SequenceLiteral
  | 'Bag'         LBRACE (collectionItem (COMMA collectionItem)*)? RBRACE   # BagLiteral
  | 'OrderedSet'  LBRACE (collectionItem (COMMA collectionItem)*)? RBRACE   # OrderedSetLiteral
  ;

/* ------------------------------------
  collectionItem ::=
    expression [ ".." expression ]
*/
collectionItem
  : expression (DOTDOT expression)?
  ;

/* ------------------------------------
  emptyCollectionLiteral ::= 
    "oclEmpty" "(" collectionType ")"

  Hack for avoiding typing problems with e.g. Set{}
*/
emptyCollectionLiteral
  : 'oclEmpty' LPAREN collectionType RPAREN
  | collectionType LBRACE RBRACE;


/* ------------------------------------
  undefinedLiteral ::= 
    "oclUndefined" "(" type ")"

  OCL extension
*/
undefinedLiteral
  : 'oclUndefined' LPAREN type RPAREN
  | 'Undefined'
  | 'null' LPAREN type RPAREN
  | 'null'
  ;

/* ------------------------------------
  tupleLiteral ::= 
    "Tuple" "{" tupleItem { "," tupleItem } "}"
*/
tupleLiteral
  : 'Tuple' LBRACE tupleItem ( COMMA tupleItem )* RBRACE
  ;

/* ------------------------------------
  tupleItem ::= id ":" expression
*/
tupleItem
  : ID COLON type EQUAL expression   #TypedTupleItem
  | ID (COLON | EQUAL) expression    #UntypedTupleItem
  ;

/* ------------------------------------
  type ::= 
      simpleType 
    | collectionType
    | tupleType
*/
type
  : simpleType      #TypeSimple
  | collectionType  #TypeCollection
  | tupleType       #TypeTuple
  ;


typeOnly
  : type EOF
  ;

/* ------------------------------------
  simpleType ::= id 

  A simple type may be a basic type (Integer, Real, Boolean, String),
  an enumeration type, an object type, or OclAny.
*/
simpleType
  : ID
  ;


/* ------------------------------------
  collectionType ::= 
    ( "Collection" | "Set" | "Sequence" | "Bag" | "OrderedSet" ) "(" type ")"
*/
collectionType
  : 'Collection' LPAREN type RPAREN   #TypeSimpleCollection
  | 'Set' LPAREN type RPAREN          #TypeSet
  | 'Sequence' LPAREN type RPAREN     #TypeSequence
  | 'Bag' LPAREN type RPAREN          #TypeBag
  | 'OrderedSet' LPAREN type RPAREN   #TypeOrderedSet
  ;


/* ------------------------------------
  tupleType ::= "Tuple" "(" tuplePart { "," tuplePart } ")"
*/
tupleType
  : 'Tuple' LPAREN tuplePart ( COMMA tuplePart )* RPAREN
  ;


/* ------------------------------------
  tuplePart ::= id ":" type
*/
tuplePart
  : ID COLON type
  ;


/*
--------- Start of file OCLLexerRules.gpart -------------------- 
*/

// Whitespace -- ignored
WS:
  [ \t\f\r\n]+ -> skip
  ;
    
// Use paraphrases for nice error messages
ARROW         : '->';
AT            : '@';
BAR           : '|';
COLON         : ':';
COLON_COLON   : '::';
COLON_EQUAL   : ':=';
COMMA         : ',';
DOT           : '.';
DOTDOT        : '..';
EQUAL         : '=';
GREATER       : '>';
GREATER_EQUAL : '>=';
HASH          : '#';
LBRACE        : '{';
LBRACK        : '[';
LESS          : '<';
LESS_EQUAL    : '<=';
LPAREN        : '(';
MINUS         : '-';
NOT_EQUAL     : '<>';
PLUS          : '+';
RBRACE        : '}';
RBRACK        : ']';
RPAREN        : ')';
SEMI          : ';';
SLASH         : '/';
STAR          : '*';
ABSTRACT      : 'abstract';
EXISTENTIAL   : 'existential';
AGGREGATION   : 'aggregation';
COMPOSITION   : 'composition';
ORDERED       : 'ordered';
UNION         : 'union';
NO_NAVIGABLE  : '--X';
PUBLIC        : '--+';
PRIVATE       : '--—';
PROTECTED     : '--#';
PACKAGE       : '--~';

// Single-line comments
SL_COMMENT:
    ('//' | '--') ~[\r\n]* -> skip
    ;

// multiple-line comments
ML_COMMENT:
    '/*' .*? '*/' -> skip
    ;


  
INT:
    [0-9]+
    ;

REAL:
    INT ('.' INT ([eE] [+-]? INT)? | [eE] [+-]? INT)
    ;

SOIL_OPERATION: 'begin' .*? 'end';

// String literals
STRING:	
    '\'' ( ~('\''|'\\') | ESC )* '\'';

NON_OCL_STRING:	
    '"' ( ~('"'|'\\') | ESC)* '"';
    
// escape sequence -- note that this is protected; it can only be called
//   from another lexer rule -- it will not ever directly return a token to
//   the parser
// There are various ambiguities hushed in this rule.  The optional
// '0'...'7' digit matches should be matched here rather than letting
// them go back to STRING_LITERAL to be matched.  ANTLR does the
// right thing by matching immediately; hence, it's ok to shut off
// the FOLLOW ambig warnings.
fragment
ESC
:
    '\\' 
    ( [btnfr"'\\] 
    | 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT 
    | [0-3] ([0-7] [0-7]?)? | [4-7] [0-7]? )
    ;

// hexadecimal digit (again, note it's protected!)
fragment
HEX_DIGIT:
    [0-9a-fA-F];


// An IDifier.  Note that testLiterals is set to true!  This means
// that after we match the rule, we look in the literals table to see
// if it's a literal or really an IDifier.

ID:
    ('$' | [a-zA-Z_] ) ([a-zA-Z_] | [0-9])*
    ;
    
// A dummy rule to force vocabulary to be all characters (except
// special ones that ANTLR uses internally (0 to 2)

fragment
VOCAB:	
    '\u0003'..'\u0377'
    ;