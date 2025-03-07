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

    //MetaEnumElement Tests
    void metaEnumElement_getName_returnsCorrectName();
    void metaEnumElement_setName_updatesName();

    //MetaEnum Tests
    void metaEnum_getName_returnsCorrectName();
    void metaEnum_setName_updatesName();

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

void MetaEnumTest::metaEnumElement_getName_returnsCorrectName(){
    QCOMPARE(metaEnumElement->getName(), "TestEnumElement");
}

void MetaEnumTest::metaEnumElement_setName_updatesName(){
    std::string newName = "NewName";

    metaEnumElement->setName(newName);

    QCOMPARE(metaEnumElement->getName(), newName);
}

void MetaEnumTest::metaEnum_getName_returnsCorrectName(){
    QCOMPARE(metaEnum->getName(), "TestEnum");
}


void MetaEnumTest::metaEnum_setName_updatesName(){
    std::string newName = "NewName";

    metaEnum->setName(newName);

    QCOMPARE(metaEnum->getName(), newName);
}

void MetaEnumTest::metaEnum_getElements_returnsCorrectMap(){
    auto elements = metaEnum->getElements();
    auto enumElement = elements.at("TestEnumElement");

    QCOMPARE(enumElement->getName(), metaEnumElement->getName());
}

void MetaEnumTest::metaEnum_getElement_returnsCorrectEnumElement(){
    QCOMPARE(metaEnum->getElement("TestEnumElement")->getName(), "TestEnumElement");
}

void MetaEnumTest::metaEnum_addElement_validEnumElement_updatesEnumElementsMap(){
    int originalEnumElementsSize = metaEnum->getElements().size();
    std::shared_ptr<MetaModel::MetaEnumElement> newEnumElement = std::make_shared<MetaModel::MetaEnumElement>("NewEnumElement");

    metaEnum->addElement(newEnumElement);

    QCOMPARE(metaEnum->getElement("NewEnumElement")->getName(), "NewEnumElement");
    QCOMPARE(metaEnum->getElements().size(), originalEnumElementsSize + 1);
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

    QCOMPARE(newEnumElementsSize, originalEnumElementsSize - 1);
}

void MetaEnumTest::metaEnum_removeElement_nonExistingKey_doesNothing(){
    std::shared_ptr<MetaModel::MetaEnumElement> newEnumElement = std::make_shared<MetaModel::MetaEnumElement>("NewEnumElement");
    metaEnum->addElement(newEnumElement);

    int originalEnumElementsSize = metaEnum->getElements().size();

    metaEnum->removeElement("NOTNewEnumElement");

    int newEnumElementsSize = metaEnum->getElements().size();

    QCOMPARE(newEnumElementsSize, originalEnumElementsSize);
}

void MetaEnumTest::metaEnum_equals_sameMetaEnum_returnsTrue(){
    QCOMPARE(metaEnum->equals(*metaEnum), true);
}

void MetaEnumTest::metaEnum_equals_differentMetaEnum_returnsFalse(){
    MetaModel::MetaEnum* metaEnum2 = new MetaModel::MetaEnum("TestEnum2", metaEnumElement);

    QCOMPARE(metaEnum->equals(*metaEnum2), false);
}

void MetaEnumTest::metaEnum_equals_differentMetaType_returnsFalse(){
    std::shared_ptr<MetaModel::MetaType> metaType = MetaModel::String::instance();

    QCOMPARE(metaEnum->equals(*metaType), false);
}


QTEST_MAIN(MetaEnumTest)
#include "MetaEnumTest.moc"
