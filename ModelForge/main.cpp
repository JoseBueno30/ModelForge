#include "antlr4/generated/USELexer.h"
#include "antlr4/generated/USEParser.h"
#include "include/ui/dialogs/MainWindow.h"
#include "antlr4/CustomUSEVisitor.cpp"

#include <QApplication>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include <antlr4-runtime.h>
#include <QStyleFactory>

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

    QPalette defaultPalette = QApplication::palette();

    MainWindow w;

    w.show();
    return a.exec();
}
