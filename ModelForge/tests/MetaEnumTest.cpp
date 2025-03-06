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

    void metaEnum_getElements_returnsCorrectMap();
    void metaEnum_getElement_returnsCorrectEnumElement();
    void metaEnum_addElement_validEnumElement_updatesEnumElementsMap();
    void metaEnum_addElement_nullEnumElement_throwsInvalidArgumentException();
    void metaEnum_addElement_repeatedenumElement_throwsInvalidArgumentException();
    void metaEnum_removeElement_existingKey_updatesEnumElementsMap();
    void metaEnum_removeElement_nonExistingKey_doesNothing();
    void metaEnum_equals_sameMetaEnum_returnsTrue();
    void metaEnum_equals_differentMetaEnum_returnsFalse();
    void metaEnum_equals_differentMetaType_returnsFalse();
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

void MetaEnumTest::metaEnum_getElements_returnsCorrectMap(){
    auto elements = metaEnum->getElements();
    auto enumElement = elements.at("TestEnumElement");

    QCOMPARE(enumElement->getName(), metaEnumElement->getName());
}

void MetaEnumTest::metaEnum_getElement_returnsCorrectEnumElement(){
    QCOMPARE("TestEnumElement", metaEnum->getElement("TestEnumElement")->getName());
}

void MetaEnumTest::metaEnum_addElement_validEnumElement_updatesEnumElementsMap(){
    std::shared_ptr<MetaModel::MetaEnumElement> newEnumElement = std::make_shared<MetaModel::MetaEnumElement>("NewEnumElement");

    metaEnum->addElement(newEnumElement);

    QCOMPARE("NewEnumElement", metaEnum->getElement("NewEnumElement")->getName());
}

void MetaEnumTest::metaEnum_addElement_nullEnumElement_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaEnum->addElement(nullptr));
}

void MetaEnumTest::metaEnum_addElement_repeatedenumElement_throwsInvalidArgumentException(){
    std::shared_ptr<MetaModel::MetaEnumElement> newEnumElement = std::make_shared<MetaModel::MetaEnumElement>("NewEnumElement");

    metaEnum->addElement(newEnumElement);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaEnum->addElement(newEnumElement));
}

void MetaEnumTest::metaEnum_removeElement_existingKey_updatesEnumElementsMap(){
    std::shared_ptr<MetaModel::MetaEnumElement> newEnumElement = std::make_shared<MetaModel::MetaEnumElement>("NewEnumElement");
    metaEnum->addElement(newEnumElement);

    int originalEnumElementsSize = metaEnum->getElements().size();

    metaEnum->removeElement("NewEnumElement");

    int newEnumElementsSize = metaEnum->getElements().size();

    QCOMPARE(originalEnumElementsSize - 1, newEnumElementsSize);
}

void MetaEnumTest::metaEnum_removeElement_nonExistingKey_doesNothing(){
    std::shared_ptr<MetaModel::MetaEnumElement> newEnumElement = std::make_shared<MetaModel::MetaEnumElement>("NewEnumElement");
    metaEnum->addElement(newEnumElement);

    int originalEnumElementsSize = metaEnum->getElements().size();

    metaEnum->removeElement("NOTNewEnumElement");

    int newEnumElementsSize = metaEnum->getElements().size();

    QCOMPARE(originalEnumElementsSize, newEnumElementsSize);
}

void MetaEnumTest::metaEnum_equals_sameMetaEnum_returnsTrue(){
    QVERIFY(metaEnum->equals(*metaEnum));
}

void MetaEnumTest::metaEnum_equals_differentMetaEnum_returnsFalse(){
    MetaModel::MetaEnum* metaEnum2 = new MetaModel::MetaEnum("TestEnum2", metaEnumElement);

    QCOMPARE(false, metaEnum->equals(*metaEnum2));
}

void MetaEnumTest::metaEnum_equals_differentMetaType_returnsFalse(){
    std::shared_ptr<MetaModel::MetaType> metaType = MetaModel::String::instance();

    QCOMPARE(false, metaEnum->equals(*metaType));
}


QTEST_MAIN(MetaEnumTest)
#include "MetaEnumTest.moc"
