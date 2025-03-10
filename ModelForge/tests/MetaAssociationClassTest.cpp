#include "metamodel/MetaAssociationClass.h"
#include <QTest>

class MetaAssociationClassTest : public QObject{
    Q_OBJECT

private:
    MetaModel::MetaAssociationClass *associationClass;

private slots:
    void init();

    void addSuperClass_nullArgument_throwsException();
    void addSuperClass_invalidArgument_throwsException();
    void addSuperClass_validArgument_doesntThrowException();
};
void MetaAssociationClassTest::init(){
    this->associationClass = new MetaModel::MetaAssociationClass("test", false, 0);
}
void MetaAssociationClassTest::addSuperClass_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->associationClass->addSuperClass(nullptr));
}
void MetaAssociationClassTest::addSuperClass_invalidArgument_throwsException(){
    std::shared_ptr<MetaModel::MetaClass> auxClass = std::make_shared<MetaModel::MetaClass>("test", false);
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->associationClass->addSuperClass(auxClass));
}
void MetaAssociationClassTest::addSuperClass_validArgument_doesntThrowException(){
    std::shared_ptr<MetaModel::MetaAssociationClass> auxClass = std::make_shared<MetaModel::MetaAssociationClass>("testPadre", false, 0);
    QVERIFY_THROWS_NO_EXCEPTION(this->associationClass->addSuperClass(auxClass));
}

QTEST_MAIN(MetaAssociationClassTest)
#include "MetaAssociationClassTest.moc"
