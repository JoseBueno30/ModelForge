#include <QTest>

#include <metamodel/MetaAssociationEnd.h>
#include <metamodel/MetaClass.h>

class MetaAssociationEndTest : public QObject{
    Q_OBJECT
private:
    MetaModel::MetaAssociationEnd * aEnd;
    std::shared_ptr<MetaModel::MetaMultiplicity> multiplicity;
    std::shared_ptr<MetaModel::MetaAssociationEnd> auxEnd;
    std::shared_ptr<MetaModel::MetaVariable> auxVar;


private slots:
    void init();

    void metaMultiplicity_addRange_lowerBoundGreater_throwsException();
    void metaMultiplicity_addRange_negativeBounds_throwsException();
    void metaMultiplicity_addRange_validArguments_doesntThrowException();
    void metaMultiplicity_deleteRange_doesntThrowException();

    void metaAssociationEnd_addRedefinedEnd_nullArgument_throwsException();
    void metaAssociationEnd_addRedefinedEnd_validArgument_insertNewRedefinedEnd();
    void metaAssociationEnd_addRedefinedEnd_existingRedefinedEnd_throwsException();

    void metaAssociationEnd_removeRedefinedEnd_existingArgument_deletesIt();
    void metaAssociationEnd_removeRedefinedEnd_invalidArgument_doesntThrowException();

    void metaAssociationEnd_addSubsettedEnd_nullArgument_throwsException();
    void metaAssociationEnd_addSubsettedEnd_validArgument_insertNewSubsettedEnd();
    void metaAssociationEnd_addSubsettedEnd_existingRedefinedEnd_throwsException();

    void metaAssociationEnd_removeSubsettedEnd_existingArgument_deletesIt();
    void metaAssociationEnd_removeSubsettedEnd_invalidArgument_doesntThrowException();

    void metaAssociationEnd_addQualifier_nullArgument_throwsException();
    void metaAssociationEnd_addQualifier_validArgument_insertNewQualifier();
    void metaAssociationEnd_addQualifier_existingRedefinedEnd_throwsException();

    void metaAssociationEnd_removeQualifier_existingArgument_deletesIt();
    void metaAssociationEnd_removeQualifier_invalidArgument_doesntThrowException();
};

void  MetaAssociationEndTest::init(){
    this->multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(1,-1);
    std::shared_ptr<MetaModel::MetaClass> auxClass = std::make_shared<MetaModel::MetaClass>("aux", false);
    this->aEnd = new MetaModel::MetaAssociationEnd(auxClass, "testRole", 0, false, false, false, false, this->multiplicity);
    this->auxEnd = std::make_shared<MetaModel::MetaAssociationEnd>(auxClass, "testAuxRole", 0, false, false, false, false, this->multiplicity);
    this->auxVar = std::make_shared<MetaModel::MetaVariable>("test", MetaModel::Integer::instance());
}

void MetaAssociationEndTest::metaMultiplicity_addRange_lowerBoundGreater_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->multiplicity->addRange(5,2));
}

void MetaAssociationEndTest::metaMultiplicity_addRange_negativeBounds_throwsException(){
     QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->multiplicity->addRange(-10,-2));
}

void MetaAssociationEndTest::metaMultiplicity_addRange_validArguments_doesntThrowException(){
    QVERIFY_THROWS_NO_EXCEPTION(this->multiplicity->addRange(0,5));
    QVERIFY_THROWS_NO_EXCEPTION(this->multiplicity->addRange(1,1));
}

void MetaAssociationEndTest::metaMultiplicity_deleteRange_doesntThrowException(){
    QVERIFY_THROWS_NO_EXCEPTION(this->multiplicity->deleteRange(2));
    QVERIFY_THROWS_NO_EXCEPTION(this->multiplicity->deleteRange(1));
    QVERIFY_THROWS_NO_EXCEPTION(this->multiplicity->deleteRange(-10));
    QVERIFY_THROWS_NO_EXCEPTION(this->multiplicity->deleteRange(10));
}


void  MetaAssociationEndTest::metaAssociationEnd_addRedefinedEnd_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->aEnd->addRedefinedEnd(nullptr));
}
void  MetaAssociationEndTest::metaAssociationEnd_addRedefinedEnd_existingRedefinedEnd_throwsException(){
    this->aEnd->addRedefinedEnd(auxEnd);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->aEnd->addRedefinedEnd(auxEnd));
}
void  MetaAssociationEndTest::metaAssociationEnd_addRedefinedEnd_validArgument_insertNewRedefinedEnd(){

    this->aEnd->addRedefinedEnd(auxEnd);

    QCOMPARE(this->aEnd->getRedefinedEnd(auxEnd->getRole())->getRole(), auxEnd->getRole());
}

void MetaAssociationEndTest::metaAssociationEnd_removeRedefinedEnd_existingArgument_deletesIt(){

    this->aEnd->removeRedefinedEnd(auxEnd->getRole());

    QCOMPARE(this->aEnd->getRedefinedEnd(auxEnd->getRole()), nullptr);
}
void MetaAssociationEndTest::metaAssociationEnd_removeRedefinedEnd_invalidArgument_doesntThrowException(){

    QVERIFY_THROWS_NO_EXCEPTION(this->aEnd->removeRedefinedEnd(this->auxEnd->getRole()));
}


void MetaAssociationEndTest::metaAssociationEnd_addSubsettedEnd_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->aEnd->addSubsettedEnd(nullptr));
}
void MetaAssociationEndTest::metaAssociationEnd_addSubsettedEnd_validArgument_insertNewSubsettedEnd(){
    QVERIFY_THROWS_NO_EXCEPTION(this->aEnd->addSubsettedEnd(auxEnd));

    QCOMPARE(this->aEnd->getSubsettedEnd(auxEnd->getRole())->getRole(), auxEnd->getRole());

}
void MetaAssociationEndTest::metaAssociationEnd_addSubsettedEnd_existingRedefinedEnd_throwsException(){
    this->aEnd->addSubsettedEnd(auxEnd);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->aEnd->addSubsettedEnd(auxEnd));
}

void MetaAssociationEndTest::metaAssociationEnd_removeSubsettedEnd_existingArgument_deletesIt(){

    this->aEnd->removeSubsettedEnd(auxEnd->getRole());

    QCOMPARE(this->aEnd->getSubsettedEnd(auxEnd->getRole()), nullptr);
}
void MetaAssociationEndTest::metaAssociationEnd_removeSubsettedEnd_invalidArgument_doesntThrowException(){
    QVERIFY_THROWS_NO_EXCEPTION(this->aEnd->removeSubsettedEnd(this->auxEnd->getRole()));
}


void MetaAssociationEndTest::metaAssociationEnd_addQualifier_nullArgument_throwsException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, this->aEnd->addQualifier(nullptr));
}
void MetaAssociationEndTest::metaAssociationEnd_addQualifier_validArgument_insertNewQualifier(){
    QVERIFY_THROWS_NO_EXCEPTION(this->aEnd->addQualifier(auxVar));

    QCOMPARE(this->aEnd->getQualifier(auxVar->getName())->getName(), auxVar->getName());
}
void MetaAssociationEndTest::metaAssociationEnd_addQualifier_existingRedefinedEnd_throwsException(){
    this->aEnd->addQualifier(auxVar);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, this->aEnd->addQualifier(auxVar));
}

void MetaAssociationEndTest::metaAssociationEnd_removeQualifier_existingArgument_deletesIt(){
    this->aEnd->removeSubsettedEnd(auxVar->getName());

    QCOMPARE(this->aEnd->getSubsettedEnd(auxVar->getName()), nullptr);
}
void MetaAssociationEndTest::metaAssociationEnd_removeQualifier_invalidArgument_doesntThrowException(){
    QVERIFY_THROWS_NO_EXCEPTION(this->aEnd->removeSubsettedEnd(this->auxVar->getName()));
}

QTEST_MAIN(MetaAssociationEndTest);
#include <MetaAssociationEndTest.moc>


