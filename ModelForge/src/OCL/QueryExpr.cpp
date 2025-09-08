#include <OCL/QueryExpr.h>

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
    std::string res = "";

    if (this->varsDeclarationString.empty()){
        res = this->source->toString() + (this->arrow ? " -> " : ".") + this->getExpression();
    }else{
        std::string queryString = queryExpr->toString();
        res = this->source->toString() + (this->arrow ? " -> " : ".") + this->queryType + "(" + (this->varsDeclarationString.empty() ? "" : this->varsDeclarationString + " | ") + queryExpr->toString() + ")";
    }
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
