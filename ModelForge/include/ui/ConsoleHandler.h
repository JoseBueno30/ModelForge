#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include <QTextEdit>
#include <QTime>


class ConsoleHandler{
public:
    ConsoleHandler();

    void setConsole(QTextEdit* console);
    void appendErrorLog(QString errorLog);
    void appendSuccessfulLog(QString successfulLog);
    void clear();

private:
    QTextEdit* console;
};

#endif // CONSOLEHANDLER_H
