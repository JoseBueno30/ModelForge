#include "antlr4/generated/USELexer.h"
#include "antlr4/generated/USEParser.h"
#include <mainwindow.h>

#include <QApplication>
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

    //test_grammar();

    MainWindow w;
    w.show();
    return a.exec();
}
