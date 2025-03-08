#include <QTest>

#include <metamodel/MetaType.h>

class MetaTypeTest: public QObject
{
    Q_OBJECT

private:


private slots:

    //String tests
    void string_instance_returnsStringSharedPointer();
    void string_equals_string_returnsTrue();
    void string_equals_otherType_returnsFalse();
    void string_equals_nullType_returnsFalse();

    //Integer tests
    void integer_instance_returnsIntegerSharedPointer();
    void integer_equals_integer_returnsTrue();
    void integer_equals_otherType_returnsFalse();
    void integer_equals_nullType_returnsFalse();

    //Real tests
    void real_instance_returnsRealSharedPointer();
    void real_equals_real_returnsTrue();
    void real_equals_otherType_returnsFalse();
    void real_equals_nullType_returnsFalse();

    //Boolean tests
    void boolean_instance_returnsBooleanSharedPointer();
    void boolean_equals_boolean_returnsTrue();
    void boolean_equals_otherType_returnsFalse();
    void boolean_equals_nullType_returnsFalse();

    //Void tests
    void void_instance_returnsVoidSharedPointer();
    void void_equals_void_returnsTrue();
    void void_equals_otherType_returnsFalse();
    void void_equals_nullType_returnsFalse();

    //Collection tests
    void collectionType_getIsOrdered_returnsIsOrdered();
    void collectionType_setIsOrdered_updatesIsOrdered();
    void collectionType_getIsUnique_returnsIsUnique();
    void collectionType_setIsUnique_updatesIsUnique();
    void collectionType_getMultiplicity_returnsMultiplicity();
    void collectionType_setMultiplicity_updatesMultiplicity();
    void collectionType_getType_returnsCorrectType();
    void collectionType_setType_updatesType();
    void collectionType_equals_sameCollectionType_returnsTrue();
    void collectionType_equals_otherType_returnsFalse();
    void collectionType_equals_nullType_returnsFalse();
    void collectionType_equals_differentIsOrderedCollection_returnsFalse();
    void collectionType_equals_differentIsUniqueCollection_returnsFalse();
    void collectionType_equals_differentMulticiplicityCollection_returnsFalse();
    void collectionType_equals_differentTypeCollection_returnsFalse();

    //TuplePart tests
    void tuplePart_getName_returnsCorrectName();
    void tuplePart_setName_updatesName();
    void tuplePart_getType_returnsCorrectType();
    void tuplePart_setType_updatesType();

    //TupleType tests
    void tupleType_getElements_returnsCorrectMap();
    void tupleType_getElement_existingElement_returnsCorrectEnumElement();
    void tupleType_getElement_nonExistingElement_returnsNullptr();
    void tupleType_addElement_validElement_updatesEnumElementsMap();
    void tupleType_addElement_nullElement_throwsInvalidArgumentException();
    void tupleType_addElement_repeatedElement_throwsInvalidArgumentException();
    void tupleType_removeElement_existingKey_updatesElementsMap();
    void tupleType_removeElement_nonExistingKey_doesNothing();
    void tupleType_equals_sameTupleType_returnsTrue();
    void tupleType_equals_otherType_returnsFalse();
    void tupleType_equals_differentElementsMapSizeTupleType_returnsFalse();
    void tupleType_equals_differentTuplePartTupleType_returnsFalse();


};


//String tests
void MetaTypeTest::string_instance_returnsStringSharedPointer(){
    auto stringType1 = MetaModel::String::instance();

    QVERIFY(stringType1 != nullptr);
    QCOMPARE(stringType1, MetaModel::String::instance());
}

void MetaTypeTest::string_equals_string_returnsTrue(){
    auto stringType1 = MetaModel::String::instance();
    auto stringType2 = MetaModel::String::instance();

    QCOMPARE(stringType1->equals(*stringType2), true);
}

void MetaTypeTest::string_equals_otherType_returnsFalse(){
    auto stringType = MetaModel::String::instance();
    auto integerType = MetaModel::Integer::instance();

    QCOMPARE(stringType->equals(*integerType), false);
}

void MetaTypeTest::string_equals_nullType_returnsFalse(){
    auto stringType = MetaModel::String::instance();
    std::shared_ptr<MetaModel::String> null = nullptr;

    QCOMPARE(stringType->equals(*null), false);
}

//Integer tests
void MetaTypeTest::integer_instance_returnsIntegerSharedPointer(){
    auto integerType1 = MetaModel::Integer::instance();

    QVERIFY(integerType1 != nullptr);
    QCOMPARE(integerType1, MetaModel::Integer::instance());
}

void MetaTypeTest::integer_equals_integer_returnsTrue(){
    auto integerType1 = MetaModel::Integer::instance();
    auto integerType2 = MetaModel::Integer::instance();

    QCOMPARE(integerType1->equals(*integerType2), true);
}

void MetaTypeTest::integer_equals_otherType_returnsFalse(){
    auto integerType = MetaModel::Integer::instance();
    auto stringType = MetaModel::String::instance();

    QCOMPARE(integerType->equals(*stringType), false);
}

void MetaTypeTest::integer_equals_nullType_returnsFalse(){
    auto integerType = MetaModel::Integer::instance();
    std::shared_ptr<MetaModel::Integer> null = nullptr;

    QCOMPARE(integerType->equals(*null), false);
}

//Real tests
void MetaTypeTest::real_instance_returnsRealSharedPointer(){
    auto realType1 = MetaModel::Real::instance();

    QVERIFY(realType1 != nullptr);
    QCOMPARE(realType1, MetaModel::Real::instance());
}

void MetaTypeTest::real_equals_real_returnsTrue(){
    auto realType1 = MetaModel::Real::instance();
    auto realType2 = MetaModel::Real::instance();

    QCOMPARE(realType1->equals(*realType2), true);
}

void MetaTypeTest::real_equals_otherType_returnsFalse(){
    auto realType = MetaModel::Real::instance();
    auto integerType = MetaModel::Integer::instance();

    QCOMPARE(realType->equals(*integerType), false);
}

void MetaTypeTest::real_equals_nullType_returnsFalse(){
    auto realType = MetaModel::Real::instance();
    std::shared_ptr<MetaModel::Real> null = nullptr;

    QCOMPARE(realType->equals(*null), false);
}

//Boolean tests
void MetaTypeTest::boolean_instance_returnsBooleanSharedPointer(){
    auto booleanType1 = MetaModel::Boolean::instance();

    QVERIFY(booleanType1 != nullptr);
    QCOMPARE(booleanType1, MetaModel::Boolean::instance());
}

void MetaTypeTest::boolean_equals_boolean_returnsTrue(){
    auto booleanType1 = MetaModel::Boolean::instance();
    auto booleanType2 = MetaModel::Boolean::instance();

    QCOMPARE(booleanType1->equals(*booleanType2), true);
}

void MetaTypeTest::boolean_equals_otherType_returnsFalse(){
    auto booleanType = MetaModel::Boolean::instance();
    auto integerType = MetaModel::Integer::instance();

    QCOMPARE(booleanType->equals(*integerType), false);
}

void MetaTypeTest::boolean_equals_nullType_returnsFalse(){
    auto booleanType = MetaModel::Boolean::instance();
    std::shared_ptr<MetaModel::Boolean> null = nullptr;

    QCOMPARE(booleanType->equals(*null), false);
}

//Void tests
void MetaTypeTest::void_instance_returnsVoidSharedPointer(){
    auto voidType1 = MetaModel::Void::instance();

    QVERIFY(voidType1 != nullptr);
    QCOMPARE(voidType1, MetaModel::Void::instance());
}

void MetaTypeTest::void_equals_void_returnsTrue(){
    auto voidType1 = MetaModel::Void::instance();
    auto voidType2 = MetaModel::Void::instance();

    QCOMPARE(voidType1->equals(*voidType2), true);
}

void MetaTypeTest::void_equals_otherType_returnsFalse(){
    auto voidType = MetaModel::Void::instance();
    auto integerType = MetaModel::Integer::instance();

    QCOMPARE(voidType->equals(*integerType), false);
}

void MetaTypeTest::void_equals_nullType_returnsFalse(){
    auto voidType = MetaModel::Void::instance();
    std::shared_ptr<MetaModel::Void> null = nullptr;

    QCOMPARE(voidType->equals(*null), false);
}

//Collection tests
void MetaTypeTest::collectionType_getIsOrdered_returnsIsOrdered(){
    bool isOrdered = true;
    auto collectionType = new MetaModel::CollectionType(isOrdered, false, 1, MetaModel::Integer::instance());

    QCOMPARE(collectionType->getIsOrdered(), isOrdered);
}

void MetaTypeTest::collectionType_setIsOrdered_updatesIsOrdered(){
    bool isOrdered = true;
    auto collectionType = new MetaModel::CollectionType(isOrdered, false, 1, MetaModel::Integer::instance());

    bool newIsOrdered = false;
    collectionType->setIsOrdered(newIsOrdered);

    QCOMPARE(collectionType->getIsOrdered(), newIsOrdered);
}

void MetaTypeTest::collectionType_getIsUnique_returnsIsUnique(){
    bool isUnique = true;
    auto collectionType = new MetaModel::CollectionType(false, isUnique, 1, MetaModel::Integer::instance());

    QCOMPARE(collectionType->getIsUnique(), isUnique);
}

void MetaTypeTest::collectionType_setIsUnique_updatesIsUnique(){
    bool isUnique = true;
    auto collectionType = new MetaModel::CollectionType(false, isUnique, 1, MetaModel::Integer::instance());

    bool newIsUnique = false;
    collectionType->setIsUnique(newIsUnique);

    QCOMPARE(collectionType->getIsUnique(), newIsUnique);
}

void MetaTypeTest::collectionType_getMultiplicity_returnsMultiplicity(){
    int multiplicity = 1;
    auto collectionType = new MetaModel::CollectionType(false, false, multiplicity, MetaModel::Integer::instance());

    QCOMPARE(collectionType->getMultiplicity(), multiplicity);
}

void MetaTypeTest::collectionType_setMultiplicity_updatesMultiplicity(){
    int multiplicity = 1;
    auto collectionType = new MetaModel::CollectionType(false, false, multiplicity, MetaModel::Integer::instance());

    int newMultiplicity = 2;
    collectionType->setMultiplicity(newMultiplicity);

    QCOMPARE(collectionType->getMultiplicity(), newMultiplicity);
}

void MetaTypeTest::collectionType_getType_returnsCorrectType(){
    auto type = MetaModel::Integer::instance();
    auto collectionType = new MetaModel::CollectionType(false, false, 1, type);

    QVERIFY(collectionType->getType().equals(*type));
}

void MetaTypeTest::collectionType_setType_updatesType(){
    auto type = MetaModel::Integer::instance();
    auto collectionType = new MetaModel::CollectionType(false, false, 1, type);

    auto newType = MetaModel::String::instance();
    collectionType->setType(newType);

    QVERIFY(collectionType->getType().equals(*newType));

}

void MetaTypeTest::collectionType_equals_sameCollectionType_returnsTrue(){
    bool isOrdered = true;
    bool isUnique = true;
    int multiciplicity = 1;
    auto type = MetaModel::Integer::instance();

    auto collectionType1 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);
    auto collectionType2 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);

    QCOMPARE(collectionType1->equals(*collectionType2), true);
}

void MetaTypeTest::collectionType_equals_otherType_returnsFalse(){
    bool isOrdered = true;
    bool isUnique = true;
    int multiciplicity = 1;
    auto type = MetaModel::Integer::instance();

    auto collectionType1 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);

    QCOMPARE(collectionType1->equals(*MetaModel::Integer::instance()), false);
}

void MetaTypeTest::collectionType_equals_nullType_returnsFalse(){
    bool isOrdered = true;
    bool isUnique = true;
    int multiciplicity = 1;
    auto type = MetaModel::Integer::instance();

    auto collectionType1 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);
    std::shared_ptr<MetaModel::Void> null = nullptr;

    QCOMPARE(collectionType1->equals(*null), false);
}

void MetaTypeTest::collectionType_equals_differentIsOrderedCollection_returnsFalse(){
    bool isOrdered = true;
    bool isUnique = true;
    int multiciplicity = 1;
    auto type = MetaModel::Integer::instance();

    auto collectionType1 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);

    bool otherOrdered = false;
    auto collectionType2 = new MetaModel::CollectionType(otherOrdered, isUnique, multiciplicity, type);

    QCOMPARE(collectionType1->equals(*collectionType2), false);
}

void MetaTypeTest::collectionType_equals_differentIsUniqueCollection_returnsFalse(){
    bool isOrdered = true;
    bool isUnique = true;
    int multiciplicity = 1;
    auto type = MetaModel::Integer::instance();

    auto collectionType1 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);

    bool otherUnique = false;
    auto collectionType2 = new MetaModel::CollectionType(isOrdered, otherUnique, multiciplicity, type);

    QCOMPARE(collectionType1->equals(*collectionType2), false);
}

void MetaTypeTest::collectionType_equals_differentMulticiplicityCollection_returnsFalse(){
    bool isOrdered = true;
    bool isUnique = true;
    int multiciplicity = 1;
    auto type = MetaModel::Integer::instance();

    auto collectionType1 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);

    int otherMulticiplicity = 2;
    auto collectionType2 = new MetaModel::CollectionType(isOrdered, isUnique, otherMulticiplicity, type);

    QCOMPARE(collectionType1->equals(*collectionType2), false);
}

void MetaTypeTest::collectionType_equals_differentTypeCollection_returnsFalse(){
    bool isOrdered = true;
    bool isUnique = true;
    int multiciplicity = 1;
    auto type = MetaModel::Integer::instance();

    auto collectionType1 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, type);

    auto otherType = MetaModel::String::instance();
    auto collectionType2 = new MetaModel::CollectionType(isOrdered, isUnique, multiciplicity, otherType);

    QCOMPARE(collectionType1->equals(*collectionType2), false);
}

//TuplePart test
void MetaTypeTest::tuplePart_getName_returnsCorrectName(){
    std::string name = "TuplePart";
    auto tuplePart = new MetaModel::TuplePart(name, MetaModel::String::instance());

    QCOMPARE(tuplePart->getName(), name);
}

void MetaTypeTest::tuplePart_setName_updatesName(){
    std::string name = "TuplePart";
    auto tuplePart = new MetaModel::TuplePart(name, MetaModel::String::instance());

    std::string newName = "NewTuplePart";
    tuplePart->setName(newName);

    QCOMPARE(tuplePart->getName(), newName);
}

void MetaTypeTest::tuplePart_getType_returnsCorrectType(){
    auto type = MetaModel::String::instance();
    auto tuplePart = new MetaModel::TuplePart("TuplePart", type);

    QVERIFY(tuplePart->getType().equals(*type));
}

void MetaTypeTest::tuplePart_setType_updatesType(){
    auto type = MetaModel::String::instance();
    auto tuplePart = new MetaModel::TuplePart("TuplePart", type);

    auto newType = MetaModel::Integer::instance();
    tuplePart->setType(newType);

    QVERIFY(tuplePart->getType().equals(*newType));
}

//TupleType tests
void MetaTypeTest::tupleType_getElements_returnsCorrectMap(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    auto elements = tupleType->getElements();
    auto element = elements.at("TuplePart");

    QCOMPARE(element->getName(), tuplePart->getName());
}

void MetaTypeTest::tupleType_getElement_existingElement_returnsCorrectEnumElement(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    QCOMPARE(tupleType->getElement("TuplePart")->getName(), tuplePart->getName());
}

void MetaTypeTest::tupleType_getElement_nonExistingElement_returnsNullptr(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    QCOMPARE(tupleType->getElement("NOTTuplePart"), nullptr);
}

void MetaTypeTest::tupleType_addElement_validElement_updatesEnumElementsMap(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);
    int originalElementsSize = tupleType->getElements().size();
    auto tuplePart2 = std::make_shared<MetaModel::TuplePart>("NewTuplePart", MetaModel::String::instance());

    tupleType->addElement(tuplePart2);

    QCOMPARE(tupleType->getElement("NewTuplePart")->getName(), "NewTuplePart");
    QCOMPARE(tupleType->getElements().size(), originalElementsSize + 1);
}

void MetaTypeTest::tupleType_addElement_nullElement_throwsInvalidArgumentException(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, tupleType->addElement(nullptr));
}

void MetaTypeTest::tupleType_addElement_repeatedElement_throwsInvalidArgumentException(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, tupleType->addElement(tuplePart));
}

void MetaTypeTest::tupleType_removeElement_existingKey_updatesElementsMap(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    int originalElementsSize = tupleType->getElements().size();

    tupleType->removeElement("TuplePart");

    int newElementsSize = tupleType->getElements().size();

    QCOMPARE(newElementsSize, originalElementsSize - 1);

}

void MetaTypeTest::tupleType_removeElement_nonExistingKey_doesNothing(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    int originalElementsSize = tupleType->getElements().size();

    tupleType->removeElement("NOTTuplePart");

    int newElementsSize = tupleType->getElements().size();

    QCOMPARE(newElementsSize, originalElementsSize);

}

void MetaTypeTest::tupleType_equals_sameTupleType_returnsTrue(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    QCOMPARE(tupleType->equals(*tupleType), true);
}

void MetaTypeTest::tupleType_equals_otherType_returnsFalse(){
    auto tuplePart = std::make_shared<MetaModel::TuplePart>("TuplePart", MetaModel::String::instance());
    auto tupleType = new MetaModel::TupleType(tuplePart);

    QCOMPARE(tupleType->equals(*MetaModel::Integer::instance()), false);
}

void MetaTypeTest::tupleType_equals_differentElementsMapSizeTupleType_returnsFalse(){
    auto tuplePart1 = std::make_shared<MetaModel::TuplePart>("TuplePart1", MetaModel::String::instance());
    auto tuplePart2 = std::make_shared<MetaModel::TuplePart>("TuplePart2", MetaModel::String::instance());
    auto tupleType1 = new MetaModel::TupleType(tuplePart1);
    auto tupleType2 = new MetaModel::TupleType(tuplePart1);
    tupleType2->addElement(tuplePart2);

    QCOMPARE(tupleType1->equals(*tupleType2), false);
}

void MetaTypeTest::tupleType_equals_differentTuplePartTupleType_returnsFalse(){
    auto tuplePart1 = std::make_shared<MetaModel::TuplePart>("TuplePart1", MetaModel::String::instance());
    auto tuplePart2 = std::make_shared<MetaModel::TuplePart>("TuplePart2", MetaModel::Integer::instance());
    auto tupleType1 = new MetaModel::TupleType(tuplePart1);
    auto tupleType2 = new MetaModel::TupleType(tuplePart2);

    QCOMPARE(tupleType1->equals(*tupleType2), false);
}

QTEST_MAIN(MetaTypeTest)
#include "MetaTypeTest.moc"
