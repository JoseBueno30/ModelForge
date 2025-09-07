#include <ANTLRInputStream.h>
#include <USELexer.h>
#include <QTest>
#include <USEParser.h>
#include <CustomUSEVisitor.cpp>

#include <modelToText/VisitorUSE.h>



class RoundtripTransformationsTest: public QObject
{
    Q_OBJECT

private:
    std::shared_ptr<MetaModel::MetaModel> loadModel(std::string fileName);

private slots:

    void test_roundtrip_transformations();


};

std::shared_ptr<MetaModel::MetaModel> RoundtripTransformationsTest::loadModel(std::string inputPath){
    std::ifstream file(inputPath);

    std::ostringstream buffer;
    buffer << file.rdbuf();
    antlr4::ANTLRInputStream input(buffer.str());

    USELexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    USEParser parser(&tokens);

    USEParser::ModelContext* parseTree= parser.model();

    CustomUSEVisitor visitor;
    visitor.visit(parseTree);

    return visitor.model;
}

void RoundtripTransformationsTest::test_roundtrip_transformations(){
    std::string inputPath= "ANTLRVisitorUSETestFiles/BankAccount.use";
    std::string outputPath = "ANTLRVisitorUSETestFiles/roundtrip_output.use";

    auto model = loadModel(inputPath);
    ModelToText::VisitorUSE visitorUSE(outputPath);

    model->accept(visitorUSE);

    QFile f1(QString::fromStdString(inputPath));
    QFile f2(QString::fromStdString(outputPath));
    QVERIFY2(f1.open(QIODevice::ReadOnly), "Cannot open input file");
    QVERIFY2(f2.open(QIODevice::ReadOnly), "Cannot open output file");

    QByteArray data1 = f1.readAll();
    QByteArray data2 = f2.readAll();

    QCOMPARE(data1, data2);

}




QTEST_MAIN(RoundtripTransformationsTest)
#include "RoundtripTransformationsTest.moc"
