#include <QTest>

#include <metamodel/MetaVariable.h>

class MetaVariableTest: public QObject
{
    Q_OBJECT

private:
    MetaModel::MetaVariable* metaVariable;
    std::shared_ptr<MetaModel::MetaType> metaType;

private slots:
    void init();

    void metaVariable_getName_returnsCorrectName();
    void metaVariable_setName_updatesName();
    void metaVariable_getType_returnsCorrectType();
    void metaVariable_setType_updatesType();

};

void MetaVariableTest::init() {
    metaType = MetaModel::String::instance();

    metaVariable = new MetaModel::MetaVariable("TestVariable", metaType);
}

void MetaVariableTest::metaVariable_getName_returnsCorrectName(){
    QCOMPARE(metaVariable->getName(), "TestVariable");
}

void MetaVariableTest::metaVariable_setName_updatesName(){
    std::string newName = "NewName";

    metaVariable->setName(newName);

    QCOMPARE(metaVariable->getName(), newName);
}

void MetaVariableTest::metaVariable_getType_returnsCorrectType(){
    auto stringType = MetaModel::String::instance();

    QVERIFY(metaVariable->getType().equals(*stringType));
}

void MetaVariableTest::metaVariable_setType_updatesType(){
    auto stringType = MetaModel::String::instance();
    auto newType = MetaModel::Integer::instance();

    metaVariable->setType(newType);

    QVERIFY(metaVariable->getType().equals(*newType));
    QVERIFY(!metaVariable->getType().equals(*stringType));
}


QTEST_MAIN(MetaVariableTest)
#include "MetaVariableTest.moc"
