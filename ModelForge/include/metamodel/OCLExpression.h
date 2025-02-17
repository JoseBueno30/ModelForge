#ifndef OCLEXPRESSION_H
#define OCLEXPRESSION_H
#include <string>

namespace MetaModel{
class OCLExpr{};

// Binary Expressions -> formed by 2 OCLExpressions
class BinaryExpr : OCLExpr{
private:
    MetaModel::OCLExpr* expr1;
    MetaModel::OCLExpr* expr2;
};

// Logical Expressions
class LogicalExpr : BinaryExpr{};
class AndExpr : LogicalExpr{};
class OrExpr : LogicalExpr{};
class ImpliesExpr : LogicalExpr{};
class XOrExpr : LogicalExpr{};

class EqualityExpr : LogicalExpr{};
class EqualExpr : EqualityExpr{};
class NotEqualExpr : EqualityExpr{};

class RelationalExpr : LogicalExpr{};
class LessThanExpr : RelationalExpr{};
class GreaterThanExpr : RelationalExpr{};
class LessThanOrEqualExpr : RelationalExpr{};
class GreaterThanOrEqualExpr : RelationalExpr{};

// Factor Expresions
class FactorExpr : BinaryExpr{};
class MultiplicationExpr : FactorExpr{};
class DivisionExpr : FactorExpr{};

// Additive Expressions
class AdditiveExpr : BinaryExpr{};
class AdditionExpr : AdditiveExpr{};
class SubstractionExpr : AdditiveExpr{};


// Unary Expressions
class UnaryExpr : OCLExpr{
private:
    MetaModel::OCLExpr* expr;
};

class MinMetaModelxpr : UnaryExpr{};
class PlMetaModelxpr : UnaryExpr{};
class NotExpr : UnaryExpr{};

// OCL evaluation oriented expressions
class PostFixExpr : OCLExpr{};

// Let declarations
class LetExpr : OCLExpr{
private:
    std::string name;
    //type : MetaType
    MetaModel::OCLExpr* expr1;
    MetaModel::OCLExpr* expr2;
};

// If-then-else structure
class ConditionalExpr : OCLExpr{
private:
    MetaModel::OCLExpr exprIf;
    MetaModel::OCLExpr exprThen;
    MetaModel::OCLExpr exprElse;
};

// Lambda expressions
class LambdaExpr : OCLExpr{
    std::string name;
    //type : MetaType
    MetaModel::OCLExpr expr1;
};

}


#endif // OCLEXPRESSION_H
