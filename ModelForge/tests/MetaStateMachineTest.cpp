#include <QTest>

#include <metamodel/MetaStateMachine.h>

class MetaStateMachineTest: public QObject
{
    Q_OBJECT

private:
    MetaModel::MetaStateMachine* metaStateMachine;

private slots:
    void init();

    void metaStateMachine_getName_returnsCorrectName();
    void metaStateMachine_setName_updatesName();
    void metaStateMachine_getStateMachineDefinition_returnsCorrectStateMachineDefinition();
    void metaStateMachine_setStateMachineDefinition_updatesStateMachineDefinition();

};

void MetaStateMachineTest::init() {
    metaStateMachine = new MetaModel::MetaStateMachine("TestStateMachine", "psm TestStateMachineDefinition end");
}

void MetaStateMachineTest::metaStateMachine_getName_returnsCorrectName(){
    QCOMPARE(metaStateMachine->getName(), "TestStateMachine");
}

void MetaStateMachineTest::metaStateMachine_setName_updatesName(){
    std::string newName = "NewName";

    metaStateMachine->setName(newName);

    QCOMPARE(metaStateMachine->getName(), newName);
}

void MetaStateMachineTest::metaStateMachine_getStateMachineDefinition_returnsCorrectStateMachineDefinition(){

    QCOMPARE(metaStateMachine->getStateMachineDefinition(), "psm TestStateMachineDefinition end");
}

void MetaStateMachineTest::metaStateMachine_setStateMachineDefinition_updatesStateMachineDefinition(){
    std::string newStateMachineDefinition = "psm NewStateMachineDefinition end";

    metaStateMachine->setStateMachineDefinition(newStateMachineDefinition);

    QCOMPARE(metaStateMachine->getStateMachineDefinition(), newStateMachineDefinition);
}


QTEST_MAIN(MetaStateMachineTest)
#include "MetaStateMachineTest.moc"
