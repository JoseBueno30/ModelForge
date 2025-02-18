#ifndef METACONSTRAINT_H
#define METACONSTRAINT_H

#include "OCLExpression.h"

#include<string>
#include<memory>


namespace MetaModel{

class MetaConstraint{

private:
    std::string name;
    bool isExistential;
    std::unique_ptr<OCLExpr> expression;

public:
    MetaConstraint(std::unique_ptr<OCLExpr> expression, const std::string& name="", bool isExistential=false);

    std::string getName() const;
    void setName(const std::string& name);

    bool getIsExistential() const;
    void setIsExistential(const bool isExistential);

    std::unique_ptr<OCLExpr> getExpression() const;
    void setExpression(std::unique_ptr<OCLExpr> expression);
};

}

#endif // METACONSTRAINT_H
