cmake_minimum_required(VERSION 3.5)

project(ModelForge VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets LinguistTools Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets LinguistTools Test)


include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/antlr4)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/generated)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/atn)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/dfa)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/internal)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/misc)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/support)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/tree)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern)
include_directories(${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath)

set(ANTLR4_CPP_RUNTIME
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRErrorListener.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRErrorListener.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRErrorStrategy.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRErrorStrategy.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRFileStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRFileStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRInputStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ANTLRInputStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/BailErrorStrategy.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/BailErrorStrategy.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/BaseErrorListener.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/BaseErrorListener.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/BufferedTokenStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/BufferedTokenStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/CharStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/CharStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/CommonToken.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/CommonToken.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/CommonTokenFactory.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/CommonTokenFactory.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/CommonTokenStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/CommonTokenStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ConsoleErrorListener.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ConsoleErrorListener.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/DefaultErrorStrategy.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/DefaultErrorStrategy.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/DiagnosticErrorListener.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/DiagnosticErrorListener.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/Exceptions.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/Exceptions.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/FailedPredicateException.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/FailedPredicateException.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/FlatHashMap.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/FlatHashSet.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/InputMismatchException.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/InputMismatchException.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/InterpreterRuleContext.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/InterpreterRuleContext.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/IntStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/IntStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/Lexer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/Lexer.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/LexerInterpreter.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/LexerInterpreter.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/LexerNoViableAltException.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/LexerNoViableAltException.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ListTokenSource.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ListTokenSource.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/NoViableAltException.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/NoViableAltException.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/Parser.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/Parser.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ParserInterpreter.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ParserInterpreter.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ParserRuleContext.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ParserRuleContext.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/ProxyErrorListener.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/ProxyErrorListener.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/RecognitionException.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/RecognitionException.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/Recognizer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/Recognizer.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/RuleContext.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/RuleContext.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/RuleContextWithAltNum.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/RuleContextWithAltNum.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/RuntimeMetaData.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/RuntimeMetaData.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/Token.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/Token.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/TokenFactory.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/TokenSource.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/TokenSource.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/TokenStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/TokenStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/TokenStreamRewriter.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/TokenStreamRewriter.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/UnbufferedCharStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/UnbufferedCharStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/UnbufferedTokenStream.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/UnbufferedTokenStream.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/Version.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/Vocabulary.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/Vocabulary.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/WritableToken.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/WritableToken.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/antlr4-common.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/antlr4-runtime.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATN.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATN.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNConfig.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNConfig.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNConfigSet.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNConfigSet.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNDeserializationOptions.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNDeserializationOptions.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNDeserializer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNDeserializer.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNSimulator.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNSimulator.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNState.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNStateType.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNStateType.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ATNType.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ActionTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ActionTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/AmbiguityInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/AmbiguityInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ArrayPredictionContext.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ArrayPredictionContext.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/AtomTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/AtomTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/BasicBlockStartState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/BasicState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/BlockEndState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/BlockStartState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ContextSensitivityInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ContextSensitivityInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/DecisionEventInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/DecisionEventInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/DecisionInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/DecisionInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/DecisionState.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/DecisionState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/EpsilonTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/EpsilonTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ErrorInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ErrorInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/HashUtils.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerActionExecutor.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerActionExecutor.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerActionType.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LL1Analyzer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LL1Analyzer.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerATNConfig.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerATNConfig.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerATNSimulator.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerATNSimulator.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerChannelAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerChannelAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerCustomAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerCustomAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerIndexedCustomAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerIndexedCustomAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerModeAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerModeAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerMoreAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerMoreAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerPopModeAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerPopModeAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerPushModeAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerPushModeAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerSkipAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerSkipAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerTypeAction.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LexerTypeAction.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LookaheadEventInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LookaheadEventInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/LoopEndState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/NotSetTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/NotSetTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/OrderedATNConfigSet.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/OrderedATNConfigSet.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ParseInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ParseInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ParserATNSimulator.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ParserATNSimulator.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ParserATNSimulatorOptions.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PlusBlockStartState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PlusLoopbackState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PrecedencePredicateTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PrecedencePredicateTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredicateEvalInfo.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredicateEvalInfo.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredicateTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredicateTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContext.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContext.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContextCache.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContextCache.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContextMergeCache.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContextMergeCache.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContextMergeCacheOptions.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionContextType.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionMode.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/PredictionMode.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ProfilingATNSimulator.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/ProfilingATNSimulator.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/RangeTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/RangeTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/RuleStartState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/RuleStopState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/RuleTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/RuleTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SemanticContext.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SemanticContext.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SemanticContextType.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SerializedATNView.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SetTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SetTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SingletonPredictionContext.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/SingletonPredictionContext.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/StarBlockStartState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/StarLoopbackState.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/StarLoopbackState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/StarLoopEntryState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/TokensStartState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/Transition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/Transition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/TransitionType.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/TransitionType.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/WildcardTransition.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/atn/WildcardTransition.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/DFA.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/DFA.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/DFASerializer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/DFASerializer.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/DFAState.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/DFAState.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/LexerDFASerializer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/dfa/LexerDFASerializer.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/internal/Synchronization.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/internal/Synchronization.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/InterpreterDataReader.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/InterpreterDataReader.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/Interval.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/Interval.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/IntervalSet.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/IntervalSet.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/MurmurHash.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/MurmurHash.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/Predicate.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/misc/Predicate.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Any.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Any.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Arrays.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Arrays.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/BitSet.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Casts.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/CPPUtils.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/CPPUtils.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Declarations.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/StringUtils.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/StringUtils.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Unicode.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Utf8.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/support/Utf8.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/AbstractParseTreeVisitor.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ErrorNode.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ErrorNodeImpl.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ErrorNodeImpl.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/IterativeParseTreeWalker.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/IterativeParseTreeWalker.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTree.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTree.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeListener.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeListener.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeProperty.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeType.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeVisitor.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeVisitor.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeWalker.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/ParseTreeWalker.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/TerminalNode.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/TerminalNodeImpl.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/TerminalNodeImpl.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/Trees.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/Trees.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/Chunk.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/Chunk.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/ParseTreeMatch.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/ParseTreeMatch.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/ParseTreePattern.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/ParseTreePattern.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/ParseTreePatternMatcher.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/ParseTreePatternMatcher.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/RuleTagToken.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/RuleTagToken.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/TagChunk.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/TagChunk.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/TextChunk.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/TextChunk.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/TokenTagToken.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/pattern/TokenTagToken.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPath.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPath.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathElement.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathElement.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathLexer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathLexer.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathLexerErrorListener.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathLexerErrorListener.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathRuleAnywhereElement.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathRuleAnywhereElement.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathRuleElement.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathRuleElement.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathTokenAnywhereElement.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathTokenAnywhereElement.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathTokenElement.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathTokenElement.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathWildcardAnywhereElement.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathWildcardAnywhereElement.h
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathWildcardElement.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/src/tree/xpath/XPathWildcardElement.h
)



set(ANTLR_GENERATED_SOURCES
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USELexer.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USEParser.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USEBaseVisitor.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USEVisitor.cpp
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USELexer.h
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USEParser.h
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USEBaseVisitor.h
    ${PROJECT_SOURCE_DIR}/antlr4/generated/USEVisitor.h
)



file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")
set(TS_FILES ModelForge_en_150.ts)

add_library(Antlr4Lib SHARED
    ${ANTLR_GENERATED_SOURCES}
    ${ANTLR4_CPP_RUNTIME}
    antlr4/CustomUSEVisitor.cpp
    )

add_library(MetaModelLib SHARED

    include/metamodel/MetaModel.h
    src/metamodel/MetaModel.cpp
    include/metamodel/MetaType.h
    src/metamodel/MetaType.cpp
    include/metamodel/MetaEnum.h
    src/metamodel/MetaEnum.cpp
    include/metamodel/MetaClass.h
    src/metamodel/MetaClass.cpp
    include/metamodel/MetaAttribute.h
    src/metamodel/MetaAttribute.cpp
    include/metamodel/MetaOperation.h
    src/metamodel/MetaOperation.cpp
    include/metamodel/MetaVariable.h
    src/metamodel/MetaVariable.cpp
    include/metamodel/MetaConstraint.h
    src/metamodel/MetaConstraint.cpp
    include/metamodel/MetaStateMachine.h
    src/metamodel/MetaStateMachine.cpp
    include/metamodel/MetaAssociation.h
    src/metamodel/MetaAssociation.cpp
    include/metamodel/MetaAssociationEnd.h
    src/metamodel/MetaAssociationEnd.cpp
    include/metamodel/MetaAssociationClass.h
    src/metamodel/MetaAssociationClass.cpp
    include/metamodel/MetaElement.h



    include/modelToText/VisitorInterface.h
    include/modelToText/VisitorUSE.h
    src/modelToText/VisitorUSE.cpp


    include/OCL/OCLExpr.h
    include/OCL/OCLExpr.cpp
    include/OCL/BinaryExpr.h include/OCL/BinaryExpr.cpp
    include/OCL/LogicalExpr.h include/OCL/LogicalExpr.cpp
    include/OCL/RelationalExpr.h include/OCL/RelationalExpr.cpp
    include/OCL/EqualityExpr.h include/OCL/EqualityExpr.cpp
    include/OCL/FactorExpr.h include/OCL/FactorExpr.cpp
    include/OCL/AdditiveExpr.h include/OCL/AdditiveExpr.cpp
    include/OCL/UnaryExpr.h include/OCL/UnaryExpr.cpp
    include/OCL/LetExpr.h include/OCL/LetExpr.cpp
    include/OCL/ConditionalExpr.h include/OCL/ConditionalExpr.cpp
    include/OCL/PrimaryExpr.h include/OCL/PrimaryExpr.cpp
    include/OCL/PropertyCall.h include/OCL/PropertyCall.cpp
)

set(DIALOGS

    include/ui/dialogs/MainWindow.h src/ui/dialogs/MainWindow.cpp src/ui/dialogs/MainWindow.ui
    include/ui/dialogs/ClassEditDialog.h src/ui/dialogs/ClassEditDialog.cpp src/ui/dialogs/ClassEditDialog.ui
    include/ui/dialogs/AttributeEditDialog.h src/ui/dialogs/AttributeEditDialog.cpp src/ui/dialogs/AttributeEditDialog.ui

)

set(PROJECT_SOURCES
        main.cpp

        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ModelForge
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        ${DIALOGS}

        include/ui/components/ModelGraphicsView.h
        src/ui/components//ModelGraphicsView.cpp
        include/ui/components/ConsoleHandler.h
        src/ui/components/ConsoleHandler.cpp
        include/ui/view/EnumItemView.h
        src/ui/view/EnumItemView.cpp
        include/ui/view/ClassItemView.h
        src/ui/view/ClassItemView.cpp
        include/ui/view/AssociationItemView.h
        src/ui/view/AssociationItemView.cpp
        include/ui/view/AssociationClassItemView.h
        src/ui/view/AssociationClassItemView.cpp
        include/ui/view/BoxItemView.h

        resources.qrc
        include/ui/view/GeneralizationItemView.h
        src/ui/view/GeneralizationItemView.cpp
        include/ui/components/ThemeManager.h
        src/ui/components/ThemeManager.cpp
        include/utils/Commands.h
        src/utils/Commands.cpp
        src/ui/components/ModelGraphicsScene.cpp
        include/ui/components/ModelGraphicsScene.h
    )
    #qt_add_resources(PROJECT_RESOURCES resources.qrc)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ModelForge APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ModelForge SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ModelForge
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ModelForge PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ModelForge PRIVATE MetaModelLib)
target_link_libraries(ModelForge PRIVATE Antlr4Lib)


add_subdirectory(tests)

add_subdirectory(examples)


add_definitions(-DQT_NO_KEYWORDS)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ModelForge)
# endif()
# set_target_properties(ModelForge PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# include(GNUInstallDirs)
# install(TARGETS ModelForge
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(ModelForge)
# endif()
