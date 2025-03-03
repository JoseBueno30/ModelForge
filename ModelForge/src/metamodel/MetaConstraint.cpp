#include <metamodel/MetaConstraint.h>


namespace MetaModel{


MetaConstraint::MetaConstraint(const std::shared_ptr<OCLExpr>& expression, const std::string& name, bool isExistential)
    : expression(expression), name(name), isExistential(isExistential){}

std::string MetaConstraint::getName() const{
    return name;
}

void MetaConstraint::setName(const std::string& name){
    this->name = name;
}

bool MetaConstraint::getIsExistential() const{
    return isExistential;
}

void MetaConstraint::setIsExistential(const bool isExistential){
    this->isExistential = isExistential;
}

const OCLExpr* MetaConstraint::getExpression() const{
    return expression.get();
}
void MetaConstraint::setExpression(const std::shared_ptr<OCLExpr>& expression){
    this->expression = expression;
}


}
