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
#include <map>

namespace MetaModel{

class MetaClass : public SimpleType{

private:
    std::string name;
    bool isAbstract;
    std::map<std::string, std::shared_ptr<MetaClass>> superClasses;
    std::map<std::string, std::shared_ptr<MetaClass>> childrenClasses;
    std::map<std::string, std::unique_ptr<MetaAttribute>> attributes;
    std::map<std::string, std::unique_ptr<MetaOperation>> operations;
    std::map<std::string, std::unique_ptr<MetaConstraint>> constraints;
    std::map<std::string, std::unique_ptr<MetaStateMachine>> stateMachines;

public:
    MetaClass(const std::string& name, bool isAbstract);

    std::string getName() const;
    void setName(const std::string& name);

    bool getIsAbstract() const;
    void setIsAbstract(bool isAbstract);

    const std::map<std::string, std::shared_ptr<MetaClass>>& getSuperClasses() const;
    const MetaClass* getSuperClass(const std::string& key) const;
    void addSuperClass(const std::string& key, std::unique_ptr<MetaClass> metaClass);
    void removeSuperClass(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaClass>>& getChildrenClasses() const;
    const MetaClass* getChildrenClass(const std::string& key) const;
    void addChildrenClass(const std::string& key, std::unique_ptr<MetaClass> metaClass);
    void removeChildrenClass(const std::string& key);

    const std::map<std::string, std::unique_ptr<MetaAttribute>>& getAttributes() const;
    const MetaAttribute* getAttribute(const std::string& key) const;
    void addAttribute(const std::string& key, std::unique_ptr<MetaAttribute> attribute);
    void removeAttribute(const std::string& key);

    const std::map<std::string, std::unique_ptr<MetaOperation>>& getOperations() const;
    const MetaOperation* getOperation(const std::string& key) const;
    void addOperation(const std::string& key, std::unique_ptr<MetaOperation> operation);
    void removeOperation(const std::string& key);

    const std::map<std::string, std::unique_ptr<MetaConstraint>>& getConstraints() const;
    const MetaConstraint* getConstraint(const std::string& key) const;
    void addConstraint(const std::string& key, std::unique_ptr<MetaConstraint> constraint);
    void removeConstraint(const std::string& key);

    const std::map<std::string, std::unique_ptr<MetaStateMachine>>& getStateMachines() const;
    const MetaStateMachine* getStateMachine(const std::string& key) const;
    void addStateMachine(const std::string& key, std::unique_ptr<MetaStateMachine> stateMachine);
    void removeStateMachine(const std::string& key);
};

}

#endif // METACLASS_H
