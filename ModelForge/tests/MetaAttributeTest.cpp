#include <QTest>

#include <metamodel/MetaAttribute.h>

class MetaAttributeTest: public QObject
{
    Q_OBJECT

private:


private slots:
    void init();

    void metaEnumElement_GetName_returnsCorrectName();

};

void MetaAttributeTest::init() {

}

void MetaAttributeTest::metaEnumElement_GetName_returnsCorrectName()
{
    QCOMPARE("TestEnumElement", "TestEnumElement");
}


QTEST_MAIN(MetaAttributeTest)
#include "MetaAttributeTest.moc"
