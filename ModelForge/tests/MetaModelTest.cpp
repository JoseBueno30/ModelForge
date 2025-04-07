#include <QTest>

#include <metamodel/MetaModel.h>
#include <metamodel/MetaClass.h>

using std::shared_ptr;

class MetaModelTest : public QObject{
    Q_OBJECT
private:
    MetaModel::MetaModel *model;
    shared_ptr<MetaModel::MetaClass> auxClass;
    shared_ptr<MetaModel::MetaAssociationClass> auxAssociationClass;
    shared_ptr<MetaModel::MetaAssociation> auxAssociation;
    shared_ptr<MetaModel::MetaEnum> auxEnum;

private slots:
    void init();

    void addEnum_nullArgument_throwsException();
    void addEnum_validArgument_addsEnum();
    void addEnum_existingEnum_throwsException();

    void addClass_nullArgument_throwsException();
    void addClass_validArgument_addsClass();
    void addClass_existingEnum_throwsException();
    // void removeClass_classInAssociation_removes_association();

    void addAssociationClass_nullArgument_throwsException();
    void addAssociationClass_validArgument_addsAssociationClass();
    void addAssociationClass_existingEnum_throwsException();

    void addAssociation_nullArgument_throwsException();
    void addAssociation_validArgument_addsAssociation();
    void addAssociation_existingEnum_throwsException();

    void modelContainsKey_keyContained_returnsTrue();
    void modelContainsKey_keyNotContained_returnsFalse();

};

void MetaModelTest::init(){
    this->model = new MetaModel::MetaModel("TestModel");
    this->auxAssociation = std::make_shared<MetaModel::MetaAssociation>("testAssociation", 1);
    this->auxAssociationClass = std::make_shared<MetaModel::MetaAssociationClass>("testAssociationClass", false, 1);
    this->auxClass = std::make_shared<MetaModel::MetaClass>("testClass", true);
    shared_ptr<MetaModel::MetaEnumElement> auxElement = std::make_shared<MetaModel::MetaEnumElement>("TestElement");
    this->auxEnum = std::make_shared<MetaModel::MetaEnum>("TestEnum", auxElement);
}

void MetaModelTest::addEnum_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->model->addEnum(nullptr));
}
void MetaModelTest::addEnum_existingEnum_throwsException(){
    this->model->addEnum(this->auxEnum);
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->model->addEnum(this->auxEnum));
}
void MetaModelTest::addEnum_validArgument_addsEnum(){

    this->model->addEnum(this->auxEnum);

    QCOMPARE(this->model->modelContainsKey(this->auxEnum->getName()), true);
}

void MetaModelTest::addClass_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->model->addClass(nullptr));
}
void MetaModelTest::addClass_existingEnum_throwsException(){
    this->model->addClass(this->auxClass);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->model->addClass(this->auxClass));
}
void MetaModelTest::addClass_validArgument_addsClass(){
    this->model->addClass(this->auxClass);

    QCOMPARE(this->model->modelContainsKey(this->auxClass->getName()), true);
}

void MetaModelTest::addAssociationClass_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->model->addAssociationClass(nullptr));
}
void MetaModelTest::addAssociationClass_existingEnum_throwsException(){
    this->model->addAssociationClass(this->auxAssociationClass);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->model->addAssociationClass(this->auxAssociationClass));
}
void MetaModelTest::addAssociationClass_validArgument_addsAssociationClass(){

    this->model->addAssociationClass(this->auxAssociationClass);

    QCOMPARE(this->model->modelContainsKey(this->auxAssociationClass->getName()), true);

}

void MetaModelTest::addAssociation_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->model->addAssociation(nullptr));
}
void MetaModelTest::addAssociation_existingEnum_throwsException(){
     this->model->addAssociation(this->auxAssociation);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->model->addAssociation(this->auxAssociation));
}
void MetaModelTest::addAssociation_validArgument_addsAssociation(){
    this->model->addAssociation(this->auxAssociation);

    QCOMPARE(this->model->modelContainsKey(this->auxAssociation->getName()), true);
}

void MetaModelTest::modelContainsKey_keyContained_returnsTrue(){
    this->model->addEnum(this->auxEnum);

    QCOMPARE(this->model->modelContainsKey(this->auxEnum->getName()), true);
}
void MetaModelTest::modelContainsKey_keyNotContained_returnsFalse(){
    QCOMPARE(this->model->modelContainsKey("falseKeyTest"), false);
}

QTEST_MAIN(MetaModelTest);
#include "MetaModelTest.moc"
