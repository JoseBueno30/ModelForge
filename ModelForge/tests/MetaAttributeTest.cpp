#include <QTest>

#include <metamodel/MetaAttribute.h>

class MetaAttributeTest: public QObject
{
    Q_OBJECT

private:
    MetaModel::MetaAttribute* metaAttribute;
    std::shared_ptr<MetaModel::MetaType> metaType;

private slots:
    void init();

    void metaAttribute_getName_returnsCorrectName();
    void metaAttribute_setName_updatesName();
    void metaAttribute_getType_returnsCorrectType();
    void metaAttribute_setType_notVoidType_updatesType();
    void metaAttribute_setType_voidType_throwsInvalidArgumentException();

    void metaAttribute_getInitExpr_returnsCorrectOCLExpression();
    void metaAttribute_setInitExpr_updatesInitExpr();
    void metaAttribute_getDeriveExpr_returnsCorrectOCLExpression();
    void metaAttribute_setDeriveExpr_updatesDeriveExpr();

};

void MetaAttributeTest::init() {
    metaType = MetaModel::String::instance();

    metaAttribute = new MetaModel::MetaAttribute("TestAttribute", metaType);
}

void MetaAttributeTest::metaAttribute_getName_returnsCorrectName(){
    QCOMPARE(metaAttribute->getName(), "TestAttribute");
}

void MetaAttributeTest::metaAttribute_setName_updatesName(){
    std::string newName = "NewName";

    metaAttribute->setName(newName);

    QCOMPARE(metaAttribute->getName(), newName);
}

void MetaAttributeTest::metaAttribute_getType_returnsCorrectType(){
    auto stringType = MetaModel::String::instance();

    QVERIFY(metaAttribute->getType().equals(*stringType));
}

void MetaAttributeTest::metaAttribute_setType_notVoidType_updatesType(){
    auto stringType = MetaModel::String::instance();
    auto newType = MetaModel::Integer::instance();

    metaAttribute->setType(newType);

    QVERIFY(metaAttribute->getType().equals(*newType));
    QVERIFY(!metaAttribute->getType().equals(*stringType));
}

void MetaAttributeTest::metaAttribute_setType_voidType_throwsInvalidArgumentException(){
    auto voidType = MetaModel::Void::instance();

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, metaAttribute->setType(voidType));
}

void MetaAttributeTest::metaAttribute_getInitExpr_returnsCorrectOCLExpression(){
    QCOMPARE(metaAttribute->getInitExpr(), nullptr);
}

void MetaAttributeTest::metaAttribute_setInitExpr_updatesInitExpr(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");

    metaAttribute->setInitExpr(expression);


    QCOMPARE(metaAttribute->getInitExpr()->getExpression(), "TestOCLExpression");
}

void MetaAttributeTest::metaAttribute_getDeriveExpr_returnsCorrectOCLExpression(){
    QCOMPARE(metaAttribute->getDeriveExpr(), nullptr);
}

void MetaAttributeTest::metaAttribute_setDeriveExpr_updatesDeriveExpr(){
    auto expression = std::make_shared<MetaModel::OCLExpr>("TestOCLExpression");

    metaAttribute->setDeriveExpr(expression);


    QCOMPARE(metaAttribute->getDeriveExpr()->getExpression(), "TestOCLExpression");
}


QTEST_MAIN(MetaAttributeTest)
#include "MetaAttributeTest.moc"
