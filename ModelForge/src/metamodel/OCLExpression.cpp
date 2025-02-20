#include <metamodel/OCLExpression.h>

namespace MetaModel{

OCLExpr::OCLExpr(const std::string& expression)
    :expression(expression){}

std::string OCLExpr::getExpression() const{
    return expression;
}

void OCLExpr::setExpression(const std::string& expression){
    this->expression = expression;
}

}
