#include <QTest>

#include <metamodel/MetaAssociation.h>
#include <metamodel/MetaClass.h>

using std::shared_ptr;

class MetaAssociationTest : public QObject{
    Q_OBJECT

private:
    shared_ptr<MetaModel::MetaClass> classAux;
    shared_ptr<MetaModel::MetaAssociation> association;


private slots:
    void init();

    void addAssociationEnd_nullArgument_throwsException();
    void addAssociationEnd_validArgument_addsTheArgument();
    void addAssociationEnd_argumentAlreadyExists_throwsException();

    void removeAssociationEnd_removesCorrectly();
};

void MetaAssociationTest::init(){
    this->classAux = std::make_shared<MetaModel::MetaClass>("Tests", false);
    this->association = std::make_shared<MetaModel::MetaAssociation>("associationTest", 0);
}

void MetaAssociationTest::addAssociationEnd_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->association->addAssociationEnd(nullptr));
}
void MetaAssociationTest::addAssociationEnd_validArgument_addsTheArgument(){
    shared_ptr<MetaModel::MetaAssociationEnd> end = std::make_shared<MetaModel::MetaAssociationEnd>(this->classAux, this->association, "test", 0, false, false, false, false, nullptr);
    QVERIFY_THROWS_NO_EXCEPTION(this->association->addAssociationEnd(end));
}
void MetaAssociationTest::addAssociationEnd_argumentAlreadyExists_throwsException(){
    shared_ptr<MetaModel::MetaAssociationEnd> end = std::make_shared<MetaModel::MetaAssociationEnd>(this->classAux, this->association, "test", 0, false, false, false, false, nullptr);

    this->association->addAssociationEnd(end);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->association->addAssociationEnd(end));
}

void MetaAssociationTest::removeAssociationEnd_removesCorrectly(){
    QVERIFY_THROWS_NO_EXCEPTION(this->association->removeAssociationEnd("test"));
}

QTEST_MAIN(MetaAssociationTest)
#include "MetaAssociationTest.moc"
