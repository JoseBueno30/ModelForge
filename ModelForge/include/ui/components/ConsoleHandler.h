#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include <QTextEdit>
#include <QTime>


class ConsoleHandler{
public:
    ConsoleHandler();

    static void setConsole(QTextEdit* console);
    static void appendErrorLog(QString errorLog);
    static void appendSuccessfulLog(QString successfulLog);
    static void appendStandardLog(QString log);
    static void clear();

protected:
    static QTextEdit* console;
};

#endif // CONSOLEHANDLER_H
