#include <QTest>

#include <metamodel/MetaClass.h>

class MetaClassTest: public QObject
{
    Q_OBJECT

private:
    MetaModel::MetaClass* metaClass;
    std::shared_ptr<MetaModel::MetaType> metaType;

private slots:
    void init();

    void metaClass_getName_returnsCorrectName();
    void metaClass_setName_updatesName();
    void metaClass_getIsAbstract_returnsIsAbstract();
    void metaClass_setIsAbstract_updatesIsAbstract();

    void metaClass_getSuperClasses_returnsCorrectMap();
    void metaClass_getSuperClass_existingSuperClass_returnsCorrectSuperClass();
    void metaClass_getSuperClass_nonExistingSuperClass_returnsNullptr();
    void metaClass_addSuperClass_validSuperClass_updatesSuperClassesMap();
    void metaClass_addSuperClass_nullSuperClass_throwsInvalidArgumentException();
    void metaClass_addSuperClass_repeatedSuperClass_throwsInvalidArgumentException();
    void metaClass_addSuperClass_itself_throwsInvalidArgumentException();
    void metaClass_addSuperClass_inheritanceCycle_throwsInvalidArgumentException();
    void metaClass_addSuperClass_attributeInheritanceConflict_throwsInvalidArgumentException();
    void metaClass_addSuperClass_operationInheritanceConflict_throwsInvalidArgumentException();
    void metaClass_removeSuperClass_existingKey_updatesSuperClassesMap();
    void metaClass_removeSuperClass_nonExistingKey_doesNothing();

    void metaClass_getAttributes_returnsCorrectMap();
    void metaClass_getAllAttributes_returnsMapWithClassAndSuperClassesAttributes();
    void metaClass_getAttribute_existingAttribute_returnsCorrectAttribute();
    void metaClass_getAttribute_nonExistingAttribute_returnsNullptr();
    void metaClass_addAttribute_validAttribute_updatesAttributesMap();
    void metaClass_addAttribute_nullAttribute_throwsInvalidArgumentException();
    void metaClass_addAttribute_repeatedAttribute_throwsInvalidArgumentException();
    void metaClass_addAttribute_attributeAlreadyDefinedInSuperClass_throwsInvalidArgumentException();
    void metaClass_removeAttribute_existingKey_updatesAttributesMap();
    void metaClass_removeAttribute_nonExistingKey_doesNothing();

    void metaClass_getOperations_returnsCorrectMap();
    void metaClass_getAllOperations_returnsMapWithClassAndSuperClassesOperations();
    void metaClass_getOperation_existingOperation_returnsCorrectOperation();
    void metaClass_getOperation_nonExistingOperation_returnsNullptr();
    void metaClass_addOperation_validOperation_updatesOperationsMap();
    void metaClass_addOperation_nullOperation_throwsInvalidArgumentException();
    void metaClass_addOperation_repeatedOperation_throwsInvalidArgumentException();
    void metaClass_addOperation_isNotValidOverrideOfOperationDefinedInSuperClass_throwsInvalidArgumentException();
    void metaClass_addOperation_isValidOverrideOfOperationDefinedInSuperClass_updatesOperationsMap();
    void metaClass_removeOperation_existingKey_updatesOperationsMap();
    void metaClass_removeOperation_nonExistingKey_doesNothing();

    void metaClass_getConstraints_returnsCorrectMap();
    void metaClass_getConstraint_existingConstraint_returnsCorrectConstraint();
    void metaClass_getConstraint_nonExistingConstraint_returnsNullptr();
    void metaClass_addConstraint_validConstraint_updatesConstraintsMap();
    void metaClass_addConstraint_nullConstraint_throwsInvalidArgumentException();
    void metaClass_addConstraint_repeatedConstraint_throwsInvalidArgumentException();
    void metaClass_removeConstraint_existingKey_updatesConstraintsMap();
    void metaClass_removeConstraint_nonExistingKey_doesNothing();

    void metaClass_getStateMachines_returnsCorrectMap();
    void metaClass_getStateMachine_existingStateMachine_returnsCorrectStateMachine();
    void metaClass_getStateMachine_nonExistingStateMachine_returnsNullptr();
    void metaClass_addStateMachine_validStateMachine_updatesStateMachinesMap();
    void metaClass_addStateMachine_nullStateMachine_throwsInvalidArgumentException();
    void metaClass_addStateMachine_repeatedStateMachine_throwsInvalidArgumentException();
    void metaClass_removeStateMachine_existingKey_updatesStateMachinesMap();
    void metaClass_removeStateMachine_nonExistingKey_doesNothing();

    void metaClass_getAssociationEnds_returnsCorrectMap();
    void metaClass_getAllAssociationEnds_returnsMapWithClassAndSuperClassesAssociationEnds();
    void metaClass_getAssociationEnd_existingAssociationEnd_returnsCorrectAssociationEnd();
    void metaClass_getAssociationEnd_nonExistingAssociationEnd_returnsNullptr();
    void metaClass_addAssociationEnd_validAssociationEnd_updatesAssociationEndsMap();
    void metaClass_addAssociationEnd_nullAssociationEnd_throwsInvalidArgumentException();
    void metaClass_addAssociationEnd_repeatedAssociationEnd_throwsInvalidArgumentException();
    void metaClass_addAssociationEnd_associationEndAlreadyDefinedInSuperClass_throwsInvalidArgumentException();
    void metaClass_removeAssociationEnd_existingKey_updatesAssociationEndsMap();
    void metaClass_removeAssociationEnd_nonExistingKey_doesNothing();

    void metaClass_isSubClassOf_superClass_returnsTrue();
    void metaClass_isSubClassOf_nonSuperClass_returnsFalse();

    void metaClass_isSuperClassOf_subClass_returnsTrue();
    void metaClass_isSuperClassOf_nonSubClass_returnsFalse();

    void metaClass_hasInheritanceCycle_anyAncestorOfTheGivenClassInheritsFromMetaClass_returnsTrue();
    void metaClass_hasInheritanceCycle_noAncestorOfTheGivenClassInheritsFromMetaClass_returnsTrue();

    void metaClass_equals_sameMetaClass_returnsTrue();
    void metaClass_equals_otherType_returnsFalse();
    void metaClass_equals_diffentNameMetaClass_returnsFalse();
};

void MetaClassTest::init() {
    metaType = MetaModel::String::instance();

    metaClass = new MetaModel::MetaClass("TestClass", false);
}

void MetaClassTest::metaClass_getName_returnsCorrectName(){
    QCOMPARE(metaClass->getName(), "TestClass");
}

void MetaClassTest::metaClass_setName_updatesName(){
    std::string newName = "NewName";

    metaClass->setName(newName);

    QCOMPARE(metaClass->getName(), newName);
}

void MetaClassTest::metaClass_getIsAbstract_returnsIsAbstract(){
    QCOMPARE(metaClass->getIsAbstract(), false);
}

void MetaClassTest::metaClass_setIsAbstract_updatesIsAbstract(){
    bool newIsAbstract = true;

    metaClass->setIsAbstract(newIsAbstract);

    QCOMPARE(metaClass->getIsAbstract(), newIsAbstract);
}

void MetaClassTest::metaClass_getSuperClasses_returnsCorrectMap(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    metaClass->addSuperClass(superClass);
    auto superClasses = metaClass->getSuperClasses();
    auto expectedSuperClass = superClasses.at("TestSuperClass");

    QCOMPARE(superClass->getName(), expectedSuperClass->getName());
}

void MetaClassTest::metaClass_getSuperClass_existingSuperClass_returnsCorrectSuperClass(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    metaClass->addSuperClass(superClass);

    QCOMPARE(metaClass->getSuperClass("TestSuperClass")->getName(), "TestSuperClass");
}

void MetaClassTest::metaClass_getSuperClass_nonExistingSuperClass_returnsNullptr(){
    QCOMPARE(metaClass->getSuperClass("TestSuperClass"), nullptr);
}

void MetaClassTest::metaClass_addSuperClass_validSuperClass_updatesSuperClassesMap(){
    int originalSuperClassesSize = metaClass->getSuperClasses().size();
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    metaClass->addSuperClass(superClass);

    QCOMPARE(metaClass->getSuperClass("TestSuperClass")->getName(), "TestSuperClass");
    QCOMPARE(metaClass->getSuperClasses().size(), originalSuperClassesSize + 1);
}

void MetaClassTest::metaClass_addSuperClass_nullSuperClass_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addSuperClass(nullptr));
}

void MetaClassTest::metaClass_addSuperClass_repeatedSuperClass_throwsInvalidArgumentException(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    metaClass->addSuperClass(superClass);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addSuperClass(superClass));
}

void MetaClassTest::metaClass_addSuperClass_itself_throwsInvalidArgumentException(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, superClass->addSuperClass(superClass));
}

void MetaClassTest::metaClass_addSuperClass_inheritanceCycle_throwsInvalidArgumentException(){
    auto metaClass1 = std::make_shared<MetaModel::MetaClass>("TestSuperClass1", false);
    auto metaClass2 = std::make_shared<MetaModel::MetaClass>("TestSuperClass2", false);
    auto metaClass3 = std::make_shared<MetaModel::MetaClass>("TestSuperClass3", false);

    metaClass2->addSuperClass(metaClass1);
    metaClass3->addSuperClass(metaClass2);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass1->addSuperClass(metaClass3));

}

void MetaClassTest::metaClass_addSuperClass_attributeInheritanceConflict_throwsInvalidArgumentException(){
    auto superClass1 = std::make_shared<MetaModel::MetaClass>("TestSuperClass1", false);
    auto superClass2 = std::make_shared<MetaModel::MetaClass>("TestSuperClass2", false);

    auto attribute1 = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());
    auto attribute2 = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::Integer::instance());

    superClass1->addAttribute(attribute1);
    superClass2->addAttribute(attribute2);

    metaClass->addSuperClass(superClass1);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addSuperClass(superClass2));
}

void MetaClassTest::metaClass_addSuperClass_operationInheritanceConflict_throwsInvalidArgumentException(){
    auto superClass1 = std::make_shared<MetaModel::MetaClass>("TestSuperClass1", false);
    auto superClass2 = std::make_shared<MetaModel::MetaClass>("TestSuperClass2", false);

    auto operation1 = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());
    auto operation2 = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::Integer::instance());

    superClass1->addOperation(operation1);
    superClass2->addOperation(operation2);

    metaClass->addSuperClass(superClass1);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addSuperClass(superClass2));
}

void MetaClassTest::metaClass_removeSuperClass_existingKey_updatesSuperClassesMap(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    metaClass->addSuperClass(superClass);

    int originalSuperClassesSize = metaClass->getSuperClasses().size();

    metaClass->removeSuperClass("TestSuperClass");

    int newSuperClassesSize = metaClass->getSuperClasses().size();

    QCOMPARE(newSuperClassesSize, originalSuperClassesSize - 1);
}

void MetaClassTest::metaClass_removeSuperClass_nonExistingKey_doesNothing(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    metaClass->addSuperClass(superClass);

    int originalSuperClassesSize = metaClass->getSuperClasses().size();

    metaClass->removeSuperClass("NOTTestSuperClass");

    int newSuperClassesSize = metaClass->getSuperClasses().size();

    QCOMPARE(newSuperClassesSize, originalSuperClassesSize);
}

void MetaClassTest::metaClass_getAttributes_returnsCorrectMap(){
    auto attribute = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());
    metaClass->addAttribute(attribute);
    auto attributes = metaClass->getAttributes();
    auto expectedAttribute = attributes.at("TestAttribute");

    QCOMPARE(attribute->getName(), expectedAttribute->getName());
}

void MetaClassTest::metaClass_getAllAttributes_returnsMapWithClassAndSuperClassesAttributes(){
    auto attribute1 = std::make_shared<MetaModel::MetaAttribute>("TestAttribute1", MetaModel::String::instance());
    auto attribute2 = std::make_shared<MetaModel::MetaAttribute>("TestAttribute2", MetaModel::Real::instance());

    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    superClass->addAttribute(attribute1);

    metaClass->addAttribute(attribute2);

    metaClass->addSuperClass(superClass);

    auto allAttributes = metaClass->getAllAttributes();

    QCOMPARE(allAttributes.at("TestAttribute1")->getName(), "TestAttribute1");
    QCOMPARE(allAttributes.at("TestAttribute2")->getName(), "TestAttribute2");
}

void MetaClassTest::metaClass_getAttribute_existingAttribute_returnsCorrectAttribute(){
    auto attribute = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());
    metaClass->addAttribute(attribute);

    QCOMPARE(metaClass->getAttribute("TestAttribute")->getName(), "TestAttribute");
}

void MetaClassTest::metaClass_getAttribute_nonExistingAttribute_returnsNullptr(){
    QCOMPARE(metaClass->getAttribute("TestAttribute"), nullptr);
}

void MetaClassTest::metaClass_addAttribute_validAttribute_updatesAttributesMap(){
    int originalAttributesSize = metaClass->getAttributes().size();
    auto attribute = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());

    metaClass->addAttribute(attribute);

    QCOMPARE(metaClass->getAttribute("TestAttribute")->getName(), "TestAttribute");
    QCOMPARE(metaClass->getAttributes().size(), originalAttributesSize + 1);
}

void MetaClassTest::metaClass_addAttribute_nullAttribute_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addAttribute(nullptr));
}

void MetaClassTest::metaClass_addAttribute_repeatedAttribute_throwsInvalidArgumentException(){
    auto attribute = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());

    metaClass->addAttribute(attribute);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addAttribute(attribute));
}

void MetaClassTest::metaClass_addAttribute_attributeAlreadyDefinedInSuperClass_throwsInvalidArgumentException(){
    auto attribute1 = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());
    auto attribute2 = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::Real::instance());

    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    superClass->addAttribute(attribute1);

    metaClass->addSuperClass(superClass);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addAttribute(attribute2));
}

void MetaClassTest::metaClass_removeAttribute_existingKey_updatesAttributesMap(){
    auto attribute = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());
    metaClass->addAttribute(attribute);

    int originalAttributesSize = metaClass->getAttributes().size();

    metaClass->removeAttribute("TestAttribute");

    int newAttributesSize = metaClass->getAttributes().size();

    QCOMPARE(newAttributesSize, originalAttributesSize - 1);
}

void MetaClassTest::metaClass_removeAttribute_nonExistingKey_doesNothing(){
    auto attribute = std::make_shared<MetaModel::MetaAttribute>("TestAttribute", MetaModel::String::instance());
    metaClass->addAttribute(attribute);

    int originalAttributesSize = metaClass->getAttributes().size();

    metaClass->removeAttribute("NOTTestAttribute");

    int newAttributesSize = metaClass->getAttributes().size();

    QCOMPARE(newAttributesSize, originalAttributesSize);
}

void MetaClassTest::metaClass_getOperations_returnsCorrectMap(){
    auto operation = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());
    metaClass->addOperation(operation);
    auto operations = metaClass->getOperations();
    auto expectedOperation = operations.at("TestOperation");

    QCOMPARE(operation->getName(), expectedOperation->getName());
}

void MetaClassTest::metaClass_getAllOperations_returnsMapWithClassAndSuperClassesOperations(){
    auto operation1 = std::make_shared<MetaModel::MetaOperation>("TestOperation1", "OperationDefinition", MetaModel::String::instance());
    auto operation2 = std::make_shared<MetaModel::MetaOperation>("TestOperation2", "OperationDefinition", MetaModel::String::instance());

    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    superClass->addOperation(operation1);

    metaClass->addOperation(operation2);

    metaClass->addSuperClass(superClass);

    auto allOperations = metaClass->getAllOperations();

    QCOMPARE(allOperations.at("TestOperation1")->getName(), "TestOperation1");
    QCOMPARE(allOperations.at("TestOperation2")->getName(), "TestOperation2");
}

void MetaClassTest::metaClass_getOperation_existingOperation_returnsCorrectOperation(){
    auto operation = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());
    metaClass->addOperation(operation);

    QCOMPARE(metaClass->getOperation("TestOperation")->getName(), "TestOperation");
}

void MetaClassTest::metaClass_getOperation_nonExistingOperation_returnsNullptr(){
    QCOMPARE(metaClass->getOperation("TestOperation"), nullptr);
}

void MetaClassTest::metaClass_addOperation_validOperation_updatesOperationsMap(){
    int originalOperationsSize = metaClass->getOperations().size();
    auto operation = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());

    metaClass->addOperation(operation);

    QCOMPARE(metaClass->getOperation("TestOperation")->getName(), "TestOperation");
    QCOMPARE(metaClass->getOperations().size(), originalOperationsSize + 1);
}

void MetaClassTest::metaClass_addOperation_nullOperation_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addOperation(nullptr));
}

void MetaClassTest::metaClass_addOperation_repeatedOperation_throwsInvalidArgumentException(){
    auto operation = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());

    metaClass->addOperation(operation);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addOperation(operation));
}

void MetaClassTest::metaClass_addOperation_isNotValidOverrideOfOperationDefinedInSuperClass_throwsInvalidArgumentException(){
    auto operation1 = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());
    auto operation2 = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::Real::instance());

    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    superClass->addOperation(operation1);

    metaClass->addSuperClass(superClass);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addOperation(operation2));
}

void MetaClassTest::metaClass_addOperation_isValidOverrideOfOperationDefinedInSuperClass_updatesOperationsMap(){
    int originalOperationsSize = metaClass->getOperations().size();

    auto operation = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());

    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);
    superClass->addOperation(operation);

    metaClass->addSuperClass(superClass);

    metaClass->addOperation(operation);

    QCOMPARE(metaClass->getOperation("TestOperation")->getName(), "TestOperation");
    QCOMPARE(metaClass->getOperations().size(), originalOperationsSize + 1);
}

void MetaClassTest::metaClass_removeOperation_existingKey_updatesOperationsMap(){
    auto operation = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());
    metaClass->addOperation(operation);

    int originalOperationsSize = metaClass->getOperations().size();

    metaClass->removeOperation("TestOperation");

    int newOperationsSize = metaClass->getOperations().size();

    QCOMPARE(newOperationsSize, originalOperationsSize - 1);
}

void MetaClassTest::metaClass_removeOperation_nonExistingKey_doesNothing(){
    auto operation = std::make_shared<MetaModel::MetaOperation>("TestOperation", "OperationDefinition", MetaModel::String::instance());
    metaClass->addOperation(operation);

    int originalOperationsSize = metaClass->getOperations().size();

    metaClass->removeOperation("NOTTestOperation");

    int newOperationsSize = metaClass->getOperations().size();

    QCOMPARE(newOperationsSize, originalOperationsSize);
}

void MetaClassTest::metaClass_getConstraints_returnsCorrectMap(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto expression = std::make_shared<MetaModel::Expr>("TestOCLExpression");
    auto constraint = std::make_shared<MetaModel::MetaConstraint>(testClass, expression, "TestConstraint", false);
    testClass->addConstraint(constraint);

    auto constraints = testClass->getConstraints();
    auto expectedConstraint = constraints.at("TestConstraint");

    QCOMPARE(constraint->getName(), expectedConstraint->getName());
}

void MetaClassTest::metaClass_getConstraint_existingConstraint_returnsCorrectConstraint(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto expression = std::make_shared<MetaModel::Expr>("TestOCLExpression");
    auto constraint = std::make_shared<MetaModel::MetaConstraint>(testClass, expression, "TestConstraint", false);
    testClass->addConstraint(constraint);

    QCOMPARE(testClass->getConstraint("TestConstraint")->getName(), "TestConstraint");
}

void MetaClassTest::metaClass_getConstraint_nonExistingConstraint_returnsNullptr(){
    QCOMPARE(metaClass->getConstraint("TestConstraint"), nullptr);
}

void MetaClassTest::metaClass_addConstraint_validConstraint_updatesConstraintsMap(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    int originalConstraintsSize = testClass->getConstraints().size();

    auto expression = std::make_shared<MetaModel::Expr>("TestOCLExpression");
    auto constraint = std::make_shared<MetaModel::MetaConstraint>(testClass, expression, "TestConstraint", false);
    testClass->addConstraint(constraint);


    QCOMPARE(testClass->getConstraint("TestConstraint")->getName(), "TestConstraint");
    QCOMPARE(testClass->getConstraints().size(), originalConstraintsSize + 1);
}

void MetaClassTest::metaClass_addConstraint_nullConstraint_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addConstraint(nullptr));
}

void MetaClassTest::metaClass_addConstraint_repeatedConstraint_throwsInvalidArgumentException(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto expression = std::make_shared<MetaModel::Expr>("TestOCLExpression");
    auto constraint = std::make_shared<MetaModel::MetaConstraint>(testClass, expression, "TestConstraint", false);
    testClass->addConstraint(constraint);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, testClass->addConstraint(constraint));
}

void MetaClassTest::metaClass_removeConstraint_existingKey_updatesConstraintsMap(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto expression = std::make_shared<MetaModel::Expr>("TestOCLExpression");
    auto constraint = std::make_shared<MetaModel::MetaConstraint>(testClass, expression, "TestConstraint", false);
    testClass->addConstraint(constraint);

    int originalConstraintsSize = testClass->getConstraints().size();

    testClass->removeConstraint("TestConstraint");

    int newConstraintsSize = testClass->getConstraints().size();

    QCOMPARE(newConstraintsSize, originalConstraintsSize - 1);
}

void MetaClassTest::metaClass_removeConstraint_nonExistingKey_doesNothing(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto expression = std::make_shared<MetaModel::Expr>("TestOCLExpression");
    auto constraint = std::make_shared<MetaModel::MetaConstraint>(testClass, expression, "TestConstraint", false);
    testClass->addConstraint(constraint);

    int originalConstraintsSize = testClass->getConstraints().size();

    testClass->removeConstraint("NOTTestConstraint");

    int newConstraintsSize = testClass->getConstraints().size();

    QCOMPARE(newConstraintsSize, originalConstraintsSize);
}

void MetaClassTest::metaClass_getStateMachines_returnsCorrectMap(){
    auto stateMachine = std::make_shared<MetaModel::MetaStateMachine>("TestStateMachine", "psm TestStateMachineDefinition end");
    metaClass->addStateMachine(stateMachine);

    auto stateMachines = metaClass->getStateMachines();
    auto expectedStateMachine = stateMachines.at("TestStateMachine");

    QCOMPARE(stateMachine->getName(), expectedStateMachine->getName());
}

void MetaClassTest::metaClass_getStateMachine_existingStateMachine_returnsCorrectStateMachine(){
    auto stateMachine = std::make_shared<MetaModel::MetaStateMachine>("TestStateMachine", "psm TestStateMachineDefinition end");
    metaClass->addStateMachine(stateMachine);

    QCOMPARE(metaClass->getStateMachine("TestStateMachine")->getName(), "TestStateMachine");
}

void MetaClassTest::metaClass_getStateMachine_nonExistingStateMachine_returnsNullptr(){
    QCOMPARE(metaClass->getConstraint("TestStateMachine"), nullptr);
}

void MetaClassTest::metaClass_addStateMachine_validStateMachine_updatesStateMachinesMap(){
    int originalStateMachinesSize = metaClass->getStateMachines().size();

    auto stateMachine = std::make_shared<MetaModel::MetaStateMachine>("TestStateMachine", "psm TestStateMachineDefinition end");
    metaClass->addStateMachine(stateMachine);

    QCOMPARE(metaClass->getStateMachine("TestStateMachine")->getName(), "TestStateMachine");
    QCOMPARE(metaClass->getStateMachines().size(), originalStateMachinesSize + 1);
}

void MetaClassTest::metaClass_addStateMachine_nullStateMachine_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addStateMachine(nullptr));
}

void MetaClassTest::metaClass_addStateMachine_repeatedStateMachine_throwsInvalidArgumentException(){
    auto stateMachine = std::make_shared<MetaModel::MetaStateMachine>("TestStateMachine", "psm TestStateMachineDefinition end");
    metaClass->addStateMachine(stateMachine);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addStateMachine(stateMachine));
}

void MetaClassTest::metaClass_removeStateMachine_existingKey_updatesStateMachinesMap(){
    auto stateMachine = std::make_shared<MetaModel::MetaStateMachine>("TestStateMachine", "psm TestStateMachineDefinition end");
    metaClass->addStateMachine(stateMachine);

    int originalStateMachinesSize = metaClass->getStateMachines().size();

    metaClass->removeStateMachine("TestStateMachine");

    int newStateMachinesSize = metaClass->getStateMachines().size();

    QCOMPARE(newStateMachinesSize, originalStateMachinesSize - 1);
}

void MetaClassTest::metaClass_removeStateMachine_nonExistingKey_doesNothing(){
    auto stateMachine = std::make_shared<MetaModel::MetaStateMachine>("TestStateMachine", "psm TestStateMachineDefinition end");
    metaClass->addStateMachine(stateMachine);

    int originalStateMachinesSize = metaClass->getStateMachines().size();

    metaClass->removeStateMachine("NOTTestStateMachine");

    int newStateMachinesSize = metaClass->getStateMachines().size();

    QCOMPARE(newStateMachinesSize, originalStateMachinesSize);
}

void MetaClassTest::metaClass_getAssociationEnds_returnsCorrectMap(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);

    testClass->addAssociationEnd(associationEnd);
    auto associationEnds = testClass->getAssociationEnds();
    auto expectedassociationEnd = associationEnds.at("rolename");

    QCOMPARE(associationEnd->getRole(), expectedassociationEnd->getRole());
}

void MetaClassTest::metaClass_getAllAssociationEnds_returnsMapWithClassAndSuperClassesAssociationEnds(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd1 = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename1", 0, false, false, false, false, multiplicity);
    auto associationEnd2 = std::make_shared<MetaModel::MetaAssociationEnd>(superClass, nullptr, "rolename2", 0, false, false, false, false, multiplicity);

    superClass->addAssociationEnd(associationEnd2);

    testClass->addAssociationEnd(associationEnd1);

    testClass->addSuperClass(superClass);

    auto allAssociationEnds = testClass->getAllAssociationEnds();

    QCOMPARE(allAssociationEnds.at("rolename1")->getRole(), "rolename1");
    QCOMPARE(allAssociationEnds.at("rolename2")->getRole(), "rolename2");
}

void MetaClassTest::metaClass_getAssociationEnd_existingAssociationEnd_returnsCorrectAssociationEnd(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);

    testClass->addAssociationEnd(associationEnd);

    QCOMPARE(testClass->getAssociationEnd("rolename")->getRole(), "rolename");
}

void MetaClassTest::metaClass_getAssociationEnd_nonExistingAssociationEnd_returnsNullptr(){
    QCOMPARE(metaClass->getAssociationEnd("rolename"), nullptr);
}

void MetaClassTest::metaClass_addAssociationEnd_validAssociationEnd_updatesAssociationEndsMap(){
    int originalAssociationEndsSize = metaClass->getAssociationEnds().size();

    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);

    testClass->addAssociationEnd(associationEnd);

    QCOMPARE(testClass->getAssociationEnd("rolename")->getRole(), "rolename");
    QCOMPARE(testClass->getAssociationEnds().size(), originalAssociationEndsSize + 1);
}

void MetaClassTest::metaClass_addAssociationEnd_nullAssociationEnd_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaClass->addAssociationEnd(nullptr));
}

void MetaClassTest::metaClass_addAssociationEnd_repeatedAssociationEnd_throwsInvalidArgumentException(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);

    testClass->addAssociationEnd(associationEnd);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, testClass->addAssociationEnd(associationEnd));
}

void MetaClassTest::metaClass_addAssociationEnd_associationEndAlreadyDefinedInSuperClass_throwsInvalidArgumentException(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd1 = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);
    auto associationEnd2 = std::make_shared<MetaModel::MetaAssociationEnd>(superClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);

    superClass->addAssociationEnd(associationEnd2);

    testClass->addSuperClass(superClass);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, testClass->addAssociationEnd(associationEnd1));
}

void MetaClassTest::metaClass_removeAssociationEnd_existingKey_updatesAssociationEndsMap(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);

    testClass->addAssociationEnd(associationEnd);

    int originalAssociationEndsSize = testClass->getAssociationEnds().size();

    testClass->removeAssociationEnd("rolename");

    int newAssociationEndsSize = testClass->getAssociationEnds().size();

    QCOMPARE(newAssociationEndsSize, originalAssociationEndsSize - 1);
}

void MetaClassTest::metaClass_removeAssociationEnd_nonExistingKey_doesNothing(){
    auto testClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0, 1);
    auto associationEnd = std::make_shared<MetaModel::MetaAssociationEnd>(testClass, nullptr, "rolename", 0, false, false, false, false, multiplicity);

    testClass->addAssociationEnd(associationEnd);

    int originalAssociationEndsSize = testClass->getAssociationEnds().size();

    testClass->removeAttribute("NOTrolename");

    int newAssociationEndsSize = testClass->getAssociationEnds().size();

    QCOMPARE(newAssociationEndsSize, originalAssociationEndsSize);
}

void MetaClassTest::metaClass_isSubClassOf_superClass_returnsTrue(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    metaClass->addSuperClass(superClass);

    QCOMPARE(metaClass->isSubClassOf(*superClass), true);
}

void MetaClassTest::metaClass_isSubClassOf_nonSuperClass_returnsFalse(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    QCOMPARE(metaClass->isSubClassOf(*superClass), false);
}

void MetaClassTest::metaClass_isSuperClassOf_subClass_returnsTrue() {
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    metaClass->addSuperClass(superClass);

    QCOMPARE(superClass->isSuperClassOf(*metaClass), true);
}

void MetaClassTest::metaClass_isSuperClassOf_nonSubClass_returnsFalse(){
    auto superClass = std::make_shared<MetaModel::MetaClass>("TestSuperClass", false);

    QCOMPARE(superClass->isSuperClassOf(*metaClass), false);
}

void MetaClassTest::metaClass_hasInheritanceCycle_anyAncestorOfTheGivenClassInheritsFromMetaClass_returnsTrue(){
    auto metaClass1 = std::make_shared<MetaModel::MetaClass>("TestSuperClass1", false);
    auto metaClass2 = std::make_shared<MetaModel::MetaClass>("TestSuperClass2", false);
    auto metaClass3 = std::make_shared<MetaModel::MetaClass>("TestSuperClass3", false);

    metaClass2->addSuperClass(metaClass1);
    metaClass3->addSuperClass(metaClass2);

    QCOMPARE(metaClass1->hasInheritanceCycle(*metaClass3), true);
}

void MetaClassTest::metaClass_hasInheritanceCycle_noAncestorOfTheGivenClassInheritsFromMetaClass_returnsTrue(){
    auto metaClass1 = std::make_shared<MetaModel::MetaClass>("TestSuperClass1", false);
    auto metaClass2 = std::make_shared<MetaModel::MetaClass>("TestSuperClass2", false);
    auto metaClass3 = std::make_shared<MetaModel::MetaClass>("TestSuperClass3", false);

    metaClass2->addSuperClass(metaClass1);

    QCOMPARE(metaClass1->hasInheritanceCycle(*metaClass3), false);
}

void MetaClassTest::metaClass_equals_sameMetaClass_returnsTrue(){
    QVERIFY(metaClass->equals(*metaClass));
}

void MetaClassTest::metaClass_equals_otherType_returnsFalse(){
    QCOMPARE(metaClass->equals(*MetaModel::Real::instance()), false);
}

void MetaClassTest::metaClass_equals_diffentNameMetaClass_returnsFalse(){
    auto metaClass1 = std::make_shared<MetaModel::MetaClass>("TestClass1", false);
    QCOMPARE(metaClass->equals(*metaClass1), false);
}

QTEST_MAIN(MetaClassTest)
#include "MetaClassTest.moc"
