#include <OCL/OCLExpr.h>

namespace MetaModel{

Expr::Expr(){}

Expr::Expr(const std::string& expression)
    :expression(expression){}

Expr::Expr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :expression(expression), isComplex(isComplex), type(type){}

const std::shared_ptr<MetaType> Expr::getType() const{
    return type;
}

std::string Expr::getExpression() const{
    return expression;
}

void Expr::setExpression(const std::string& expression){
    this->expression = expression;
}

bool Expr::isComplexExpr(){
    return this->isComplex;
}

}
