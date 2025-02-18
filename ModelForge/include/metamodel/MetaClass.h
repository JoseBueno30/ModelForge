#ifndef METACLASS_H
#define METACLASS_H

#include "MetaAttribute.h"
#include "MetaConstraint.h"
#include "MetaOperation.h"
#include "MetaStateMachine.h"
#include "MetaType.h"

#include <string>
#include <memory>
#include <vector>

namespace MetaModel{

class MetaClass : public SimpleType{

private:
    std::string name;
    bool isAbstract;
    std::vector<std::shared_ptr<MetaClass>> superClasses;
    std::vector<std::unique_ptr<MetaAttribute>> attributes;
    std::vector<std::unique_ptr<MetaOperation>> operations;
    std::vector<std::unique_ptr<MetaConstraint>> constraints;
    std::vector<std::unique_ptr<MetaStateMachine>> stateMachines;

public:
    MetaClass(const std::string& name, bool isAbstract);

    std::string getName() const;
    void setName(const std::string& name);

    bool getIsAbstract() const;
    void setIsAbstract(bool isAbstract);

    std::vector<std::shared_ptr<MetaClass>>& getSuperClasses() const;
    void addSuperClass(const std::shared_ptr<MetaClass>& metaClass);
    void removeSuperClass(int pos);

    std::vector<std::unique_ptr<MetaAttribute>>& getAttributes() const;
    void addAttribute(std::unique_ptr<MetaAttribute> attribute);
    void removeAttribute(int pos);

    std::vector<std::unique_ptr<MetaOperation>>& getOperations() const;
    void addOperation(std::unique_ptr<MetaOperation> operation);
    void removeOperation(int pos);

    std::vector<std::unique_ptr<MetaConstraint>>& getConstraints() const;
    void addConstraint(std::unique_ptr<MetaConstraint> constraint);
    void removeConstraint(int pos);

    std::vector<std::unique_ptr<MetaStateMachine>>& getStateMachines() const;
    void addStateMachine(std::unique_ptr<MetaStateMachine> stateMachine);
    void removeStateMachine(int pos);
};

}

#endif // METACLASS_H
