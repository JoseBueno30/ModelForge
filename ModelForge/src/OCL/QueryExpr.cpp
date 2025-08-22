#include <OCL/QueryExpr.h>
#include <iostream>

namespace MetaModel {
QueryExpr::QueryExpr(const std::string& expression,
                     const bool isComplex,
                     const std::shared_ptr<MetaType>& type,
                     const bool arrow,
                     const std::shared_ptr<Expr>& source,
                     const std::string& varsDeclarationString,
                     const std::shared_ptr<Expr>& queryExpr)
    :PropertyCallExpr(expression, isComplex, type, arrow, source), varsDeclarationString(varsDeclarationString), queryExpr(queryExpr){}

std::string QueryExpr::buildExprString() const {
    std::cout << "BUILDING QUERY EXPR STR <" << this << ">" << std::endl;
    std::cout << "EXPR <" << this << ">: " << this->getExpression() << std::endl;
    std::cout << "SRC EXPR <" << this << ">: " << this->source << std::endl;
    std::cout << "IS SRC COMPLEX <" << this << ">: " << this->source->isComplexExpr() << std::endl;
    std::cout << "SRC EXPR <" << this << ">: " << this->source->getExpression() << std::endl;
    std::cout << "SRC STR <" << this << ">: " << this->source->toString() << std::endl;


    std::string res = "";

    if (this->varsDeclarationString.empty()){
        std::cout << "NO DECLARATION??" <<  std::endl;
        res = this->source->toString() + (this->arrow ? " -> " : ".") + this->getExpression();
    }else{
        std::cout << "VISING QUERY -----<" << this << ">" <<  std::endl;
        std::cout << "QUERY EXPR TYPE<" << this << ">: " << queryExpr->getType()->toString() << std::endl;
        std::string queryString = queryExpr->toString();
        std::cout << "QUERY STR <" << this << ">: " << queryString << std::endl;
        res = this->source->toString() + (this->arrow ? " -> " : ".") + this->queryType + "(" + (this->varsDeclarationString.empty() ? "" : this->varsDeclarationString + " | ") + queryExpr->toString() + ")";
    }

    std::cout << "TO STR RESULT <" << this << ">: " << res << std::endl;
    return res;
}

const std::shared_ptr<Expr>& QueryExpr::getSource() const{
    return this->source;
}

CollectExpr::CollectExpr(const std::string& expression,
                         const bool isComplex,
                         const std::shared_ptr<MetaType>& type,
                         const bool arrow,
                         const std::shared_ptr<Expr>& source,
                         const std::string& varsDeclarationString,
                         const std::shared_ptr<Expr>& queryExpr)
    :QueryExpr(expression, isComplex, type, arrow, source, varsDeclarationString, queryExpr){
    queryType = "collect";
}

RejectExpr::RejectExpr(const std::string& expression,
                       const bool isComplex,
                       const std::shared_ptr<MetaType>& type,
                       const bool arrow,
                       const std::shared_ptr<Expr>& source,
                       const std::string& varsDeclarationString,
                       const std::shared_ptr<Expr>& queryExpr)
    :QueryExpr(expression, isComplex, type, arrow, source, varsDeclarationString, queryExpr){
    queryType = "reject";
}

SelectExpr::SelectExpr(const std::string& expression,
                       const bool isComplex,
                       const std::shared_ptr<MetaType>& type,
                       const bool arrow,
                       const std::shared_ptr<Expr>& source,
                       const std::string& varsDeclarationString,
                       const std::shared_ptr<Expr>& queryExpr)
    :QueryExpr(expression, isComplex, type, arrow, source, varsDeclarationString, queryExpr){
    queryType = "select";
}

ExistsExpr::ExistsExpr(const std::string& expression,
                       const bool isComplex,
                       const std::shared_ptr<MetaType>& type,
                       const bool arrow,
                       const std::shared_ptr<Expr>& source,
                       const std::string& varsDeclarationString,
                       const std::shared_ptr<Expr>& queryExpr)
    :QueryExpr(expression, isComplex, type, arrow, source, varsDeclarationString, queryExpr){
    queryType = "exists";
}

ForAllExpr::ForAllExpr(const std::string& expression,
                       const bool isComplex,
                       const std::shared_ptr<MetaType>& type,
                       const bool arrow,
                       const std::shared_ptr<Expr>& source,
                       const std::string& varsDeclarationString,
                       const std::shared_ptr<Expr>& queryExpr)
    :QueryExpr(expression, isComplex, type, arrow, source, varsDeclarationString, queryExpr){
    queryType = "forAll";
}

IsUniqueExpr::IsUniqueExpr(const std::string& expression,
                           const bool isComplex,
                           const std::shared_ptr<MetaType>& type,
                           const bool arrow,
                           const std::shared_ptr<Expr>& source,
                           const std::string& varsDeclarationString,
                           const std::shared_ptr<Expr>& queryExpr)
    :QueryExpr(expression, isComplex, type, arrow, source, varsDeclarationString, queryExpr){
    queryType = "isUnique";
}

SortedByExpr::SortedByExpr(const std::string& expression,
                           const bool isComplex,
                           const std::shared_ptr<MetaType>& type,
                           const bool arrow,
                           const std::shared_ptr<Expr>& source,
                           const std::string& varsDeclarationString,
                           const std::shared_ptr<Expr>& queryExpr)
    :QueryExpr(expression, isComplex, type, arrow, source, varsDeclarationString, queryExpr){
    queryType = "sortedBy";
}

}
