#include <QTest>

#include <metamodel/MetaOperation.h>

class MetaOperationTest: public QObject
{
    Q_OBJECT

private:
    MetaModel::MetaOperation* metaOperation;
    std::shared_ptr<MetaModel::MetaType> metaType;

private slots:
    void init();

    //PrePostClause Tests
    void metaPrePostClause_getName_returnsCorrectName();
    void metaPrePostClause_setName_updatesName();
    void metaPrePostClause_getExpression_returnsCorrectOCLExpression();
    void metaPrePostClause_setExpression_updatesExpression();
    void metaPrePostClause_getIsPre_returnsIsPre();
    void metaPrePostClause_setIsPre_updatesIsPre();
    void metaPrePostClause_getIsPost_returnsIsPost();
    void metaPrePostClause_setIsPost_updatesIsPost();

    //MetaOperation Tests
    void metaOperation_getName_returnsCorrectName();
    void metaOperation_setName_updatesName();
    void metaOperation_getOperationDefinition_returnsCorrectOperationDefinition();
    void metaOperation_setOperationDefinition_updatesOperationDefinition();
    void metaOperation_getReturnType_returnsCorrectReturnType();
    void metaOperation_setReturnType_updatesReturnType();

    void metaOperation_getVariables_returnsCorrectMap();
    void metaOperation_getVariable_existingVariable_returnsCorrectVariable();
    void metaOperation_getVariable_nonExistingVariable_returnsNullptr();
    void metaOperation_addVariable_validVariable_updatesVariablesMap();
    void metaOperation_addVariable_nullVariable_throwsInvalidArgumentException();
    void metaOperation_addVariable_repeatedVariable_throwsInvalidArgumentException();
    void metaOperation_removeVariable_existingKey_updatesVariablesMap();
    void metaOperation_removeVariable_nonExistingKey_doesNothing();

    void metaOperation_getPreConditions_returnsCorrectMap();
    void metaOperation_getPreCondition_existingPreCondition_returnsCorrectPreCondition();
    void metaOperation_getPreCondition_nonExistingPreCondition_returnsNullptr();
    void metaOperation_addPreCondition_validPreCondition_updatesPreConditionsMap();
    void metaOperation_addPreCondition_nullPreCondition_throwsInvalidArgumentException();
    void metaOperation_addPreCondition_repeatedPreConditionName_throwsInvalidArgumentException();
    void metaOperation_addPreCondition_repeatedPostConditionName_throwsInvalidArgumentException();
    void metaOperation_removePreCondition_existingKey_updatesPreConditionsMap();
    void metaOperation_removePreCondition_nonExistingKey_doesNothing();

    void metaOperation_getPostConditions_returnsCorrectMap();
    void metaOperation_getPostCondition_existingPostCondition_returnsCorrectPostCondition();
    void metaOperation_getPostCondition_nonExistingPostCondition_returnsNullptr();
    void metaOperation_addPostCondition_validPostCondition_updatesPostConditionsMap();
    void metaOperation_addPostCondition_nullPostCondition_throwsInvalidArgumentException();
    void metaOperation_addPostCondition_repeatedPreConditionName_throwsInvalidArgumentException();
    void metaOperation_addPostCondition_repeatedPostConditionName_throwsInvalidArgumentException();
    void metaOperation_removePostCondition_existingKey_updatesPostConditionsMap();
    void metaOperation_removePostCondition_nonExistingKey_doesNothing();

    void metaOperation_isPrePostConditionDefined_definedPreCondition_returnsTrue();
    void metaOperation_isPrePostConditionDefined_definedPostCondition_returnsTrue();
    void metaOperation_isPrePostConditionDefined_undefinedPrePostCondition_returnsFalse();

    void metaOperation_isValidOverrideOf_validOverrideOperation_returnsTrue();
    void metaOperation_isValidOverrideOf_diffentNameOperation_returnsFalse();
    void metaOperation_isValidOverrideOf_diffentReturnTypeOperation_returnsFalse();
    void metaOperation_isValidOverrideOf_diffentVariablesMapSizeOperation_returnsFalse();
    void metaOperation_isValidOverrideOf_diffentVariableTypeOperation_returnsFalse();
};

void MetaOperationTest::init() {
    metaType = MetaModel::String::instance();

    metaOperation = new MetaModel::MetaOperation("TestOperation", "operationDefinition", metaType);
}

void MetaOperationTest::metaPrePostClause_getName_returnsCorrectName(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, true, false);

    QCOMPARE(prePostClause->getName(), "TestPrePostClause");
}

void MetaOperationTest::metaPrePostClause_setName_updatesName(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, true, false);
    std::string newName = "NewName";

    prePostClause->setName(newName);


    QCOMPARE(prePostClause->getName(), newName);
}

void MetaOperationTest::metaPrePostClause_getExpression_returnsCorrectOCLExpression(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, true, false);

    QCOMPARE(prePostClause->getExpression().getExpression(), "TestOCLExpression");
}

void MetaOperationTest::metaPrePostClause_setExpression_updatesExpression(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, true, false);

    auto newExpression = std::make_shared<MetaModel::OCLExpr>("NewOCLExpression");

    prePostClause->setExpression(newExpression);


    QCOMPARE(prePostClause->getExpression().getExpression(), "NewOCLExpression");
}

void MetaOperationTest::metaPrePostClause_getIsPre_returnsIsPre(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    bool isPre = true;
    bool isPost = false;
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, isPre, isPost);

    QCOMPARE(prePostClause->getIsPre(), isPre);
}

void MetaOperationTest::metaPrePostClause_setIsPre_updatesIsPre(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    bool isPre = true;
    bool isPost = false;
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, isPre, isPost);

    bool newIsPre = false;

    prePostClause->setIsPre(newIsPre);

    QCOMPARE(prePostClause->getIsPre(), newIsPre);
}

void MetaOperationTest::metaPrePostClause_getIsPost_returnsIsPost(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    bool isPre = true;
    bool isPost = false;
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, isPre, isPost);

    QCOMPARE(prePostClause->getIsPost(), isPost);
}

void MetaOperationTest::metaPrePostClause_setIsPost_updatesIsPost(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    bool isPre = true;
    bool isPost = false;
    auto prePostClause = new MetaModel::PrePostClause("TestPrePostClause", expression, isPre, isPost);

    bool newIsPost = false;

    prePostClause->setIsPost(newIsPost);

    QCOMPARE(prePostClause->getIsPost(), newIsPost);
}


void MetaOperationTest::metaOperation_getName_returnsCorrectName(){
    QCOMPARE(metaOperation->getName(), "TestOperation");
}

void MetaOperationTest::metaOperation_setName_updatesName(){
    std::string newName = "NewName";

    metaOperation->setName(newName);

    QCOMPARE(metaOperation->getName(), newName);
}

void MetaOperationTest::metaOperation_getOperationDefinition_returnsCorrectOperationDefinition(){
    QCOMPARE(metaOperation->getOperationDefinition(), "operationDefinition");
}

void MetaOperationTest::metaOperation_setOperationDefinition_updatesOperationDefinition(){
    std::string newOperationDefinition = "NewOperationDefinition";

    metaOperation->setOperationDefinition(newOperationDefinition);

    QCOMPARE(metaOperation->getOperationDefinition(), newOperationDefinition);
}

void MetaOperationTest::metaOperation_getReturnType_returnsCorrectReturnType(){
    auto stringType = MetaModel::String::instance();

    QVERIFY(metaOperation->getReturnType().equals(*stringType));
}

void MetaOperationTest::metaOperation_setReturnType_updatesReturnType(){
    auto stringType = MetaModel::String::instance();
    auto newType = MetaModel::Integer::instance();

    metaOperation->setReturnType(newType);

    QVERIFY(metaOperation->getReturnType().equals(*newType));
    QVERIFY(!metaOperation->getReturnType().equals(*stringType));
}

void MetaOperationTest::metaOperation_getVariables_returnsCorrectMap(){
    auto metaVariable = std::make_shared<MetaModel::MetaVariable>("TestVariable", MetaModel::String::instance());
    metaOperation->addVariable(metaVariable);
    auto variables = metaOperation->getVariables();
    auto variable = variables.at("TestVariable");

    QCOMPARE(variable->getName(), metaVariable->getName());
}

void MetaOperationTest::metaOperation_getVariable_existingVariable_returnsCorrectVariable(){
    auto variable = std::make_shared<MetaModel::MetaVariable>("TestVariable", MetaModel::String::instance());
    metaOperation->addVariable(variable);

    QCOMPARE(metaOperation->getVariable("TestVariable")->getName(), "TestVariable");
}

void MetaOperationTest::metaOperation_getVariable_nonExistingVariable_returnsNullptr(){
    QCOMPARE(metaOperation->getVariable("TestVariable"), nullptr);
}

void MetaOperationTest::metaOperation_addVariable_validVariable_updatesVariablesMap(){
    int originalVariablesSize = metaOperation->getVariables().size();
    std::shared_ptr<MetaModel::MetaVariable> newVariable = std::make_shared<MetaModel::MetaVariable>("NewVariable", MetaModel::String::instance());

    metaOperation->addVariable(newVariable);

    QCOMPARE(metaOperation->getVariable("NewVariable")->getName(), "NewVariable");
    QCOMPARE(metaOperation->getVariables().size(), originalVariablesSize + 1);
}

void MetaOperationTest::metaOperation_addVariable_nullVariable_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addVariable(nullptr));
}

void MetaOperationTest::metaOperation_addVariable_repeatedVariable_throwsInvalidArgumentException(){
    std::shared_ptr<MetaModel::MetaVariable> newVariable = std::make_shared<MetaModel::MetaVariable>("NewVariable", MetaModel::String::instance());

    metaOperation->addVariable(newVariable);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addVariable(newVariable));
}

void MetaOperationTest::metaOperation_removeVariable_existingKey_updatesVariablesMap(){
    std::shared_ptr<MetaModel::MetaVariable> newVariable = std::make_shared<MetaModel::MetaVariable>("NewVariable", MetaModel::String::instance());
    metaOperation->addVariable(newVariable);

    int originalVariablesSize = metaOperation->getVariables().size();

    metaOperation->removeVariable("NewVariable");

    int newVariablesSize = metaOperation->getVariables().size();

    QCOMPARE(newVariablesSize, originalVariablesSize - 1);
}

void MetaOperationTest::metaOperation_removeVariable_nonExistingKey_doesNothing(){
    std::shared_ptr<MetaModel::MetaVariable> newVariable = std::make_shared<MetaModel::MetaVariable>("NewVariable", MetaModel::String::instance());
    metaOperation->addVariable(newVariable);

    int originalVariablesSize = metaOperation->getVariables().size();

    metaOperation->removeVariable("NOTNewVariable");

    int newVariablesSize = metaOperation->getVariables().size();

    QCOMPARE(newVariablesSize, originalVariablesSize);
}

void MetaOperationTest::metaOperation_getPreConditions_returnsCorrectMap(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestPreCondition", expression, true, false);
    metaOperation->addPreCondition(preCondition);
    auto preConditions = metaOperation->getPreConditions();
    auto actualPreCondition = preConditions.at("TestPreCondition");

    QCOMPARE(actualPreCondition->getName(), preCondition->getName());
}

void MetaOperationTest::metaOperation_getPreCondition_existingPreCondition_returnsCorrectPreCondition(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestPreCondition", expression, true, false);
    metaOperation->addPreCondition(preCondition);

    QCOMPARE(metaOperation->getPreCondition("TestPreCondition")->getName(), "TestPreCondition");
}

void MetaOperationTest::metaOperation_getPreCondition_nonExistingPreCondition_returnsNullptr(){
    QCOMPARE(metaOperation->getPreCondition("TestPreCondition"), nullptr);
}

void MetaOperationTest::metaOperation_addPreCondition_validPreCondition_updatesPreConditionsMap(){
    int originalPreConditionsSize = metaOperation->getPreConditions().size();
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestPreCondition", expression, true, false);
    metaOperation->addPreCondition(preCondition);

    QCOMPARE(metaOperation->getPreCondition("TestPreCondition")->getName(), "TestPreCondition");
    QCOMPARE(metaOperation->getPreConditions().size(), originalPreConditionsSize + 1);
}

void MetaOperationTest::metaOperation_addPreCondition_nullPreCondition_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addPreCondition(nullptr));
}

void MetaOperationTest::metaOperation_addPreCondition_repeatedPreConditionName_throwsInvalidArgumentException(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestPreCondition", expression, true, false);
    metaOperation->addPreCondition(preCondition);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addPreCondition(preCondition));
}

void MetaOperationTest::metaOperation_addPreCondition_repeatedPostConditionName_throwsInvalidArgumentException(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestCondition", expression, false, true);
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestCondition", expression, true, false);
    metaOperation->addPostCondition(postCondition);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addPreCondition(preCondition));
}

void MetaOperationTest::metaOperation_removePreCondition_existingKey_updatesPreConditionsMap(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestPreCondition", expression, true, false);
    metaOperation->addPreCondition(preCondition);


    int originalPreConditionsSize = metaOperation->getPreConditions().size();

    metaOperation->removePreCondition("TestPreCondition");

    int newPreConditionsSize = metaOperation->getPreConditions().size();

    QCOMPARE(newPreConditionsSize, originalPreConditionsSize - 1);
}

void MetaOperationTest::metaOperation_removePreCondition_nonExistingKey_doesNothing(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestPreCondition", expression, true, false);
    metaOperation->addPreCondition(preCondition);

    int originalPreConditionsSize = metaOperation->getPreConditions().size();

    metaOperation->removePreCondition("NOTTestPreCondition");

    int newPreConditionsSize = metaOperation->getPreConditions().size();

    QCOMPARE(newPreConditionsSize, originalPreConditionsSize);
}

void MetaOperationTest::metaOperation_getPostConditions_returnsCorrectMap(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestPostCondition", expression, false, true);
    metaOperation->addPostCondition(postCondition);
    auto postConditions = metaOperation->getPostConditions();
    auto actualPostCondition = postConditions.at("TestPostCondition");

    QCOMPARE(actualPostCondition->getName(), postCondition->getName());
}

void MetaOperationTest::metaOperation_getPostCondition_existingPostCondition_returnsCorrectPostCondition(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestPostCondition", expression, false, true);
    metaOperation->addPostCondition(postCondition);

    QCOMPARE(metaOperation->getPostCondition("TestPostCondition")->getName(), "TestPostCondition");
}

void MetaOperationTest::metaOperation_getPostCondition_nonExistingPostCondition_returnsNullptr(){
    QCOMPARE(metaOperation->getPostCondition("TestPostCondition"), nullptr);
}

void MetaOperationTest::metaOperation_addPostCondition_validPostCondition_updatesPostConditionsMap(){
    int originalPostConditionsSize = metaOperation->getPostConditions().size();
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestPostCondition", expression, false, true);
    metaOperation->addPostCondition(postCondition);

    QCOMPARE(metaOperation->getPostCondition("TestPostCondition")->getName(), "TestPostCondition");
    QCOMPARE(metaOperation->getPostConditions().size(), originalPostConditionsSize + 1);
}

void MetaOperationTest::metaOperation_addPostCondition_nullPostCondition_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addPostCondition(nullptr));
}

void MetaOperationTest::metaOperation_addPostCondition_repeatedPreConditionName_throwsInvalidArgumentException(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestCondition", expression, true, false);
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestCondition", expression, false, true);
    metaOperation->addPreCondition(preCondition);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addPostCondition(postCondition));
}

void MetaOperationTest::metaOperation_addPostCondition_repeatedPostConditionName_throwsInvalidArgumentException(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestCondition", expression, false, true);
    metaOperation->addPostCondition(postCondition);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaOperation->addPostCondition(postCondition));
}

void MetaOperationTest::metaOperation_removePostCondition_existingKey_updatesPostConditionsMap(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestPostCondition", expression, false, true);
    metaOperation->addPostCondition(postCondition);


    int originalPostConditionsSize = metaOperation->getPostConditions().size();

    metaOperation->removePostCondition("TestPostCondition");

    int newPostConditionsSize = metaOperation->getPostConditions().size();

    QCOMPARE(newPostConditionsSize, originalPostConditionsSize - 1);
}

void MetaOperationTest::metaOperation_removePostCondition_nonExistingKey_doesNothing(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestPostCondition", expression, false, true);
    metaOperation->addPostCondition(postCondition);

    int originalPostConditionsSize = metaOperation->getPostConditions().size();

    metaOperation->removePostCondition("NOTTestPostCondition");

    int newPostConditionsSize = metaOperation->getPostConditions().size();

    QCOMPARE(newPostConditionsSize, originalPostConditionsSize);
}

void MetaOperationTest::metaOperation_isPrePostConditionDefined_definedPreCondition_returnsTrue(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto preCondition = std::make_shared<MetaModel::PrePostClause>("TestPreCondition", expression, true, false);
    metaOperation->addPostCondition(preCondition);

    QCOMPARE(metaOperation->isPrePostConditionDefined("TestPreCondition"), true);
}

void MetaOperationTest::metaOperation_isPrePostConditionDefined_definedPostCondition_returnsTrue(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");
    auto postCondition = std::make_shared<MetaModel::PrePostClause>("TestPostCondition", expression, false, true);
    metaOperation->addPostCondition(postCondition);

    QCOMPARE(metaOperation->isPrePostConditionDefined("TestPostCondition"), true);
}

void MetaOperationTest::metaOperation_isPrePostConditionDefined_undefinedPrePostCondition_returnsFalse(){
    QCOMPARE(metaOperation->isPrePostConditionDefined("TestPostCondition"), false);
}


void MetaOperationTest::metaOperation_isValidOverrideOf_validOverrideOperation_returnsTrue(){
    QCOMPARE(metaOperation->isValidOverrideOf(*metaOperation), true);
}

void MetaOperationTest::metaOperation_isValidOverrideOf_diffentNameOperation_returnsFalse(){
    auto metaOperation2 = new MetaModel::MetaOperation("TestOperation2", "operationDefinition", metaType);

    QCOMPARE(metaOperation->isValidOverrideOf(*metaOperation2), false);
}

void MetaOperationTest::metaOperation_isValidOverrideOf_diffentReturnTypeOperation_returnsFalse(){
    auto metaType2 = MetaModel::Integer::instance();
    auto metaOperation2 = new MetaModel::MetaOperation(metaOperation->getName(), "operationDefinition", metaType2);

    QCOMPARE(metaOperation->isValidOverrideOf(*metaOperation2), false);
}

void MetaOperationTest::metaOperation_isValidOverrideOf_diffentVariablesMapSizeOperation_returnsFalse(){
    auto metaOperation2 = new MetaModel::MetaOperation(metaOperation->getName(), "operationDefinition", metaType);

    std::shared_ptr<MetaModel::MetaVariable> newVariable = std::make_shared<MetaModel::MetaVariable>("NewVariable", MetaModel::String::instance());

    metaOperation->addVariable(newVariable);

    QCOMPARE(metaOperation->isValidOverrideOf(*metaOperation2), false);
}

void MetaOperationTest::metaOperation_isValidOverrideOf_diffentVariableTypeOperation_returnsFalse(){
    auto metaOperation2 = new MetaModel::MetaOperation(metaOperation->getName(), "operationDefinition", metaType);

    std::shared_ptr<MetaModel::MetaVariable> newVariable1 = std::make_shared<MetaModel::MetaVariable>("NewVariable1", MetaModel::String::instance());
    std::shared_ptr<MetaModel::MetaVariable> newVariable2 = std::make_shared<MetaModel::MetaVariable>("NewVariable2", MetaModel::Integer::instance());

    metaOperation->addVariable(newVariable1);
    metaOperation2->addVariable(newVariable2);

    QCOMPARE(metaOperation->isValidOverrideOf(*metaOperation2), false);
}


QTEST_MAIN(MetaOperationTest)
#include "MetaOperationTest.moc"
