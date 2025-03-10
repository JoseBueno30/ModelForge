#include "antlr4/generated/USELexer.h"
#include "antlr4/generated/USEParser.h"
#include "mainwindow.h"
#include "antlr4/CustomUSEVisitor.cpp"

#include <QApplication>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include <antlr4-runtime.h>

void test_grammar(){
    std::string expTest = "self.children->isUnique( name )";
    std::cout<<"Expresion a probar: " << expTest << std::endl;
    antlr4::ANTLRInputStream input(expTest);

    USELexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    USEParser parser(&tokens);

    antlr4::tree::ParseTree * tree = parser.expressionOnly();

    std::cout<<tree->toStringTree(&parser, true) <<std::endl;
}

std::string getModelFromFile(const std::string& path){
    qDebug() << QDir::currentPath();
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::shared_ptr<MetaModel::MetaModel> test_visitor(){
    std::cout<<"PATH: " << QDir::currentPath().toStdString() << std::endl;
    std::string modelTest = getModelFromFile(QDir::currentPath().toStdString() + "/examples/BankAccount.use");
    std::cout<<"Modelo a probar: " << modelTest << std::endl;

    antlr4::ANTLRInputStream input(modelTest);

    USELexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    USEParser parser(&tokens);

    USEParser::ModelContext* tree = parser.model();

    // Crea el visitor y visita el árbol
    CustomUSEVisitor visitor;
    visitor.visit(tree);

    // Verifica que el MetaModel se haya creado correctamente
    auto model = visitor.model;

    if (model) {
        std::cout << "El nombre del MetaModel es: " << model->getName() << std::endl;
    } else {
        std::cerr << "MetaModel no fue inicializado." << std::endl;
    }

    if (model->getEnum("EnumTest")){
        std::cout << "El enum es:" << model->getEnum("EnumTest")->getName() << std::endl;
        for(const auto& pair: model->getEnum("EnumTest")->getElements()){
            std::cout << "El enumElem es:" << pair.second->getName() << std::endl;
        }
    }

    if(model->getClass("TestClass")){
        std::cout << "AAAAAAAAAAA" << std::endl;
    }

    for(const auto& pair: model->getClasses()){
        std::cout << "La clase es:" << pair.second->getName() << std::endl;
    }

    return model;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ModelForge_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    auto model = test_visitor();

    MainWindow w;
    w.setupModelGraphicsView(model);

    w.show();
    return a.exec();
}
