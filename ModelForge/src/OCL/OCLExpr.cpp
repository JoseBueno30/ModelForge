#include <OCL/OCLExpr.h>
#include <iostream>

namespace MetaModel{

Expr::Expr(){}

Expr::Expr(const std::string& expression)
    :expression(expression){}

Expr::Expr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :expression(expression), isComplex(isComplex), type(type){

    // DELETE THIS
    std::cout<<"Expr: " << this->toString() << std::endl;
}

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

bool Expr::hasParenthesis(){
    return this->parenthesis;
}
void Expr::setHasParenthesis(bool parenthesis){
    this->parenthesis = parenthesis;
}

std::string Expr::buildExprString() const {
    return this->expression;
};

std::string Expr::wrapWithParentheses(const std::string& str, bool parenthesis) const {
    if (parenthesis) {
        return "(" + str + ")";
    }
    return str;
}

std::string Expr::toString() const{
    return wrapWithParentheses(buildExprString(), parenthesis);
}

}
