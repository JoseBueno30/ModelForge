#include <OCL/PrimaryExpr.h>

#include <metamodel/MetaEnum.h>

namespace MetaModel {
PrimaryExpr::PrimaryExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :Expr(expression, isComplex, type){}

ParenthesisExpr::ParenthesisExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::shared_ptr<Expr>& expr)
    :PrimaryExpr(expression, isComplex, type), expr(expr){}

std::string ParenthesisExpr::buildExprString() const {
    return "("+this->expr->toString()+")";
}

std::vector<std::shared_ptr<Expr>> ParenthesisExpr::getChildren() const {
    return {this->expr};
}

ObjectReferenceExpr::ObjectReferenceExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::string& reference)
    :PrimaryExpr(expression, isComplex, type), reference(reference){}

LiteralExpr::LiteralExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type, const std::any& value)
    :PrimaryExpr(expression, isComplex, type), value(value){}

std::string LiteralExpr::buildExprString() const {
    std::string str = "";

    if (std::dynamic_pointer_cast<MetaModel::Integer>(this->type)) {
        str = std::to_string(std::any_cast<int>(this->value));

    } else if (std::dynamic_pointer_cast<MetaModel::Real>(this->type)) {
        str = std::to_string(std::any_cast<double>(this->value));

    } else if (std::dynamic_pointer_cast<MetaModel::Boolean>(this->type)) {
        str = std::any_cast<bool>(this->value) ? "true" : "false";

    } else if (std::dynamic_pointer_cast<MetaModel::String>(this->type)) {
        str = std::any_cast<std::string>(this->value);

    } else if (auto metaEnum = std::dynamic_pointer_cast<MetaModel::MetaEnum>(this->type)) {
        str = metaEnum->getName() + "::" + std::any_cast<std::shared_ptr<MetaModel::MetaEnumElement>>(this->value)->getName();

    } else if (std::dynamic_pointer_cast<MetaModel::CollectionType>(this->type)) {
        str = this->expression;

    } else if (std::dynamic_pointer_cast<MetaModel::TupleType>(this->type)) {
        str = this->expression;

    }   else {
         str = this->expression;
    }

    return str;
}

AllInstancesExpr::AllInstancesExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :PrimaryExpr(expression, isComplex, type){}

ByUseIdExpr::ByUseIdExpr(const std::string& expression, const bool isComplex, const std::shared_ptr<MetaType>& type)
    :PrimaryExpr(expression, isComplex, type){}
}
