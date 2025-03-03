#ifndef METACLASS_H
#define METACLASS_H

#include "MetaAttribute.h"
#include "MetaConstraint.h"
#include "MetaOperation.h"
#include "MetaStateMachine.h"
#include "MetaType.h"

#include <string>
#include <memory>
#include <map>
#include <unordered_set>

namespace MetaModel{

class MetaClass : public SimpleType{

private:
    std::string name;
    bool isAbstract;
    std::map<std::string, std::shared_ptr<MetaClass>> superClasses;
    std::map<std::string, std::shared_ptr<MetaClass>> childrenClasses;
    std::map<std::string, std::shared_ptr<MetaAttribute>> attributes;
    std::map<std::string, std::shared_ptr<MetaOperation>> operations;
    std::map<std::string, std::shared_ptr<MetaConstraint>> constraints;
    std::map<std::string, std::shared_ptr<MetaStateMachine>> stateMachines;

    bool hasAncestor(const MetaClass& ancestor, std::unordered_set<std::string>& visited) const;

public:
    MetaClass(const std::string& name, bool isAbstract);

    std::string getName() const;
    void setName(const std::string& name);

    bool getIsAbstract() const;
    void setIsAbstract(bool isAbstract);

    const std::map<std::string, std::shared_ptr<MetaClass>>& getSuperClasses() const;
    const MetaClass* getSuperClass(const std::string& key) const;
    virtual void addSuperClass(std::shared_ptr<MetaClass> metaClass);
    void removeSuperClass(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaClass>>& getChildrenClasses() const;
    const MetaClass* getChildrenClass(const std::string& key) const;
    void addChildrenClass(std::shared_ptr<MetaClass> metaClass);
    void removeChildrenClass(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaAttribute>>& getAttributes() const;
    std::map<std::string, const MetaAttribute*> getAllAttributes() const;
    std::shared_ptr<MetaAttribute> getAttribute(const std::string& key);
    void addAttribute(std::shared_ptr<MetaAttribute> attribute);
    void removeAttribute(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaOperation>>& getOperations() const;
    std::map<std::string, const MetaOperation*> getAllOperations() const;
    std::shared_ptr<MetaOperation> getOperation(const std::string& key);
    void addOperation(std::shared_ptr<MetaOperation> operation);
    void removeOperation(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaConstraint>>& getConstraints() const;
    std::shared_ptr<MetaConstraint> getConstraint(const std::string& key);
    void addConstraint(std::shared_ptr<MetaConstraint> constraint);
    void removeConstraint(const std::string& key);

    const std::map<std::string, std::shared_ptr<MetaStateMachine>>& getStateMachines() const;
    std::shared_ptr<MetaStateMachine> getStateMachine(const std::string& key);
    void addStateMachine(std::shared_ptr<MetaStateMachine> stateMachine);
    void removeStateMachine(const std::string& key);

    bool isSubClassOf(const MetaClass& metaClass) const;
    bool isSuperClassOf(const MetaClass& metaClass) const;

    bool hasInheritanceCycle(const MetaClass& metaClass) const;

    virtual bool equals(const MetaType& type) const override;
};

}

#endif // METACLASS_H
