#include <QTest>

#include <metamodel/MetaClass.h>
#include <metamodel/MetaConstraint.h>

class MetaConstraintTest: public QObject
{
    Q_OBJECT

private:
    MetaModel::MetaConstraint* metaConstraint;
    std::shared_ptr<MetaModel::MetaClass> metaClass;
    std::shared_ptr<MetaModel::Expr> expression;

private slots:
    void init();

    void metaConstraint_getName_returnsCorrectName();
    void metaConstraint_setName_updatesName();

    void metaConstraint_getClass_returnsCorrectClass();
    void metaConstraint_setClass_updatesClass();

    void metaConstraint_getIsExistential_returnsIsExistential();
    void metaConstraint_setIsExistential_updatesIsExistential();

    void metaConstraint_getExpression_returnsCorrectExpression();
    void metaConstraint_setExpression_updatesExpression();

    void metaConstraint_getVariables_returnsCorrectMap();
    void metaConstraint_getVariable_existingVariable_returnsCorrectVariable();
    void metaConstraint_getVariable_nonExistingVariable_returnsNullptr();
    void metaConstraint_addVariable_validVariable_updatesVariablesMap();
    void metaConstraint_addVariable_nullVariable_throwsInvalidArgumentException();
    void metaConstraint_addVariable_repeatedVariable_throwsInvalidArgumentException();
    void metaConstraint_removeVariable_existingKey_updatesVariablesMap();
    void metaConstraint_removeVariable_nonExistingKey_doesNothing();

};

void MetaConstraintTest::init() {
    metaClass = std::make_shared<MetaModel::MetaClass>("TestClass", false);
    expression = std::make_shared<MetaModel::Expr>("OCLExpression");

    metaConstraint = new MetaModel::MetaConstraint(metaClass, expression, "TestConstraint", false);
}

void MetaConstraintTest::metaConstraint_getName_returnsCorrectName(){
    QCOMPARE(metaConstraint->getName(), "TestConstraint");
}

void MetaConstraintTest::metaConstraint_setName_updatesName(){
    std::string newName = "NewName";

    metaConstraint->setName(newName);

    QCOMPARE(metaConstraint->getName(), newName);
}

void MetaConstraintTest::metaConstraint_getClass_returnsCorrectClass(){
    QCOMPARE(metaConstraint->getClass().getName(), "TestClass");
}

void MetaConstraintTest::metaConstraint_setClass_updatesClass(){
    auto newClass = std::make_shared<MetaModel::MetaClass>("NewClass", false);

    metaConstraint->setClass(newClass);

    QCOMPARE(metaConstraint->getClass().getName(), "NewClass");
}

void MetaConstraintTest::metaConstraint_getIsExistential_returnsIsExistential(){
    QCOMPARE(metaConstraint->getIsExistential(), false);
}

void MetaConstraintTest::metaConstraint_setIsExistential_updatesIsExistential(){
    bool newIsExistential = true;

    metaConstraint->setIsExistential(newIsExistential);

    QCOMPARE(metaConstraint->getIsExistential(), newIsExistential);
}

void MetaConstraintTest::metaConstraint_getExpression_returnsCorrectExpression(){
    QCOMPARE(metaConstraint->getExpression().getExpression(), "OCLExpression");
}

void MetaConstraintTest::metaConstraint_setExpression_updatesExpression(){
    auto newExpression = std::make_shared<MetaModel::Expr>("NewOCLExpression");

    metaConstraint->setExpression(newExpression);

    QCOMPARE(metaConstraint->getExpression().getExpression(), newExpression->getExpression());
}

void MetaConstraintTest::metaConstraint_getVariables_returnsCorrectMap(){
    std::string variable = "variable";
    metaConstraint->addVariable(variable);
    auto variables = metaConstraint->getVariables();
    auto metaVariable = variables.at("variable");

    QCOMPARE(metaVariable->getName(), variable);
}

void MetaConstraintTest::metaConstraint_getVariable_existingVariable_returnsCorrectVariable(){
    std::string variable = "variable";
    metaConstraint->addVariable(variable);

    QCOMPARE(metaConstraint->getVariable("variable")->getName(), "variable");
}

void MetaConstraintTest::metaConstraint_getVariable_nonExistingVariable_returnsNullptr(){
    QCOMPARE(metaConstraint->getVariable("variable"), nullptr);
}

void MetaConstraintTest::metaConstraint_addVariable_validVariable_updatesVariablesMap(){
    int originalVariablesSize = metaConstraint->getVariables().size();
    std::string variable = "variable";

    metaConstraint->addVariable(variable);

    QCOMPARE(metaConstraint->getVariable("variable")->getName(), "variable");
    QCOMPARE(metaConstraint->getVariable("variable")->getType().equals(metaConstraint->getClass()), true);
    QCOMPARE(metaConstraint->getVariables().size(), originalVariablesSize + 1);
}

void MetaConstraintTest::metaConstraint_addVariable_nullVariable_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaConstraint->addVariable(""));
}

void MetaConstraintTest::metaConstraint_addVariable_repeatedVariable_throwsInvalidArgumentException(){
    std::string variable = "variable";

    metaConstraint->addVariable(variable);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaConstraint->addVariable(variable));
}

void MetaConstraintTest::metaConstraint_removeVariable_existingKey_updatesVariablesMap(){
    std::string variable = "variable";
    metaConstraint->addVariable(variable);

    int originalVariablesSize = metaConstraint->getVariables().size();

    metaConstraint->removeVariable("variable");

    int newVariablesSize = metaConstraint->getVariables().size();

    QCOMPARE(newVariablesSize, originalVariablesSize - 1);
}

void MetaConstraintTest::metaConstraint_removeVariable_nonExistingKey_doesNothing(){
    std::string variable = "variable";
    metaConstraint->addVariable(variable);

    int originalVariablesSize = metaConstraint->getVariables().size();

    metaConstraint->removeVariable("NOTvariable");

    int newVariablesSize = metaConstraint->getVariables().size();

    QCOMPARE(newVariablesSize, originalVariablesSize);
}

QTEST_MAIN(MetaConstraintTest)
#include "MetaConstraintTest.moc"
