 
/*
 * HEADER TEST
 */



// Generated from USE.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  USELexer : public antlr4::Lexer {
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
    ARROW = 69, AT = 70, BAR = 71, COLON = 72, COLON_COLON = 73, COLON_EQUAL = 74, 
    COMMA = 75, DOT = 76, DOTDOT = 77, EQUAL = 78, GREATER = 79, GREATER_EQUAL = 80, 
    HASH = 81, LBRACE = 82, LBRACK = 83, LESS = 84, LESS_EQUAL = 85, LPAREN = 86, 
    MINUS = 87, NOT_EQUAL = 88, PLUS = 89, RBRACE = 90, RBRACK = 91, RPAREN = 92, 
    SEMI = 93, SLASH = 94, STAR = 95, ABSTRACT = 96, EXISTENTIAL = 97, AGGREGATION = 98, 
    COMPOSITION = 99, ORDERED = 100, UNION = 101, NO_NAVIGABLE = 102, PUBLIC = 103, 
    PRIVATE = 104, PROTECTED = 105, PACKAGE = 106, SL_COMMENT = 107, ML_COMMENT = 108, 
    INT = 109, REAL = 110, SOIL_OPERATION = 111, STRING = 112, NON_OCL_STRING = 113, 
    ID = 114
  };

  explicit USELexer(antlr4::CharStream *input);

  ~USELexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

