#include <QTest>

#include <metamodel/MetaEnum.h>

class MetaEnumTest: public QObject
{
    Q_OBJECT

private:
    MetaModel::MetaEnum* metaEnum;
    std::shared_ptr<MetaModel::MetaEnumElement> metaEnumElement;

private slots:
    void init();
    void metaEnumElement_GetName_returnsCorrectName();
    void metaEnumElement_SetName_updatesName();
    void metaEnum_GetName_returnsCorrectName();
    void metaEnum_SetName_updatesName();
};

void MetaEnumTest::init() {
    metaEnumElement = std::make_shared<MetaModel::MetaEnumElement>("TestEnumElement");
    metaEnum = new MetaModel::MetaEnum("TestEnum", metaEnumElement);
}

void MetaEnumTest::metaEnumElement_GetName_returnsCorrectName()
{
    QCOMPARE("TestEnumElement", metaEnumElement->getName());
}

void MetaEnumTest::metaEnumElement_SetName_updatesName()
{
    std::string newName = "NewName";

    metaEnumElement->setName(newName);

    QCOMPARE(newName, metaEnumElement->getName());
}

void MetaEnumTest::metaEnum_GetName_returnsCorrectName()
{
    QCOMPARE("TestEnum", metaEnum->getName());
}


void MetaEnumTest::metaEnum_SetName_updatesName()
{
    std::string newName = "NewName";

    metaEnum->setName(newName);

    QCOMPARE(newName, metaEnum->getName());
}


QTEST_MAIN(MetaEnumTest)
#include "MetaEnumTest.moc"
