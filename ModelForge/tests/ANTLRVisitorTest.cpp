#include <ANTLRInputStream.h>
#include <USELexer.h>
#include <QTest>
#include <USEParser.h>
#include <CustomUSEVisitor.cpp>



class ANTLRVisitorTest: public QObject
{
    Q_OBJECT

    //THIS TEST CLASS WILL LIMIT IT'S SCOPE TO SEMANTIC ERRORS NOT CONTROLLED IN THE METAMODEL (e.g: attribute of undefined type)

private:
    void visitModel(std::string fileName);

private slots:

    void visitClassDefinition_undefinedSuperClass_throwsInvalidArgumentException();

    void visitInvariant_undefinedScopeClass_throwsInvalidArgumentException();

    void visitPrePostDefinition_undefinedScopeClass_throwsInvalidArgumentException();
    void visitPrePostDefinition_undefinedScopeOperation_throwsInvalidArgumentException();
    void visitPrePostDefinition_differentReturnTypeThanScopeOperation_throwsInvalidArgumentException();
    void visitPrePostDefinition_differentNumberOfParametersThanScopeOperation_throwsInvalidArgumentException();
    void visitPrePostDefinition_differentNameOfParameterThanScopeOperation_throwsInvalidArgumentException();
    void visitPrePostDefinition_differentTypeOfParameterThanScopeOperation_throwsInvalidArgumentException();


    void visitSimpleType_undefinedTypeName_throwsInvalidArgumentException();

    void visitAssociationClassDefinition_undefinedSuperClass_throwsInvalidArgumentException();

    void visitRedefinesAssociationEnd_undefinedRedefinedAssociationEnd_throwsInvalidArgumentException();
    void visitSubsetsAssociationEnd_undefinedSubsettedAssociationEnd_throwsInvalidArgumentException();
    void visitAssociationEndDefinition_undefinedClass_throwsInvalidArgumentException();

    void repeatedClassDefinition_throwsRuntimeException();

};

void ANTLRVisitorTest::visitModel(std::string fileName){
    std::string filePath = "ANTLRVisitorUSETestFiles/" + fileName + ".use";
    std::ifstream file(filePath);

    std::ostringstream buffer;
    buffer << file.rdbuf();
    antlr4::ANTLRInputStream input(buffer.str());

    USELexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    USEParser parser(&tokens);

    USEParser::ModelContext* parseTree= parser.model();

    CustomUSEVisitor visitor;
    visitor.visit(parseTree);
}

void ANTLRVisitorTest::visitClassDefinition_undefinedSuperClass_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("classDefinition_undefinedSuperClass"));
}

void ANTLRVisitorTest::visitInvariant_undefinedScopeClass_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("invariant_undefinedScopeClass"));
}

void ANTLRVisitorTest::visitPrePostDefinition_undefinedScopeClass_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("prePostDefinition_undefinedScopeClass"));
}

void ANTLRVisitorTest::visitPrePostDefinition_undefinedScopeOperation_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("prePostDefinition_undefinedScopeOperation"));
}

void ANTLRVisitorTest::visitPrePostDefinition_differentReturnTypeThanScopeOperation_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("prePostDefinition_differentReturnTypeThanScopeOperation"));
}

void ANTLRVisitorTest::visitPrePostDefinition_differentNumberOfParametersThanScopeOperation_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("prePostDefinition_differentNumberOfParametersThanScopeOperation"));
}

void ANTLRVisitorTest::visitPrePostDefinition_differentNameOfParameterThanScopeOperation_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("prePostDefinition_differentNameOfParameterThanScopeOperation"));
}

void ANTLRVisitorTest::visitPrePostDefinition_differentTypeOfParameterThanScopeOperation_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("prePostDefinition_differentTypeOfParameterThanScopeOperation"));
}

void ANTLRVisitorTest::visitSimpleType_undefinedTypeName_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("simpleType_undefinedTypeName"));
}

void ANTLRVisitorTest::visitAssociationClassDefinition_undefinedSuperClass_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("associationClassDefinition_undefinedSuperClass"));
}

void ANTLRVisitorTest::visitRedefinesAssociationEnd_undefinedRedefinedAssociationEnd_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("redefinesAssociationEnd_undefinedRedefinedAssociationEnd"));
}

void ANTLRVisitorTest::visitSubsetsAssociationEnd_undefinedSubsettedAssociationEnd_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("subsetsAssociationEnd_undefinedSubsettedAssociationEnd"));
}

void ANTLRVisitorTest::visitAssociationEndDefinition_undefinedClass_throwsInvalidArgumentException(){
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, visitModel("associationEndDefinition_undefinedClass"));
}

void ANTLRVisitorTest::repeatedClassDefinition_throwsRuntimeException(){
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, visitModel("duplicateClassDefinition"));
}


QTEST_MAIN(ANTLRVisitorTest)
#include "ANTLRVisitorTest.moc"
