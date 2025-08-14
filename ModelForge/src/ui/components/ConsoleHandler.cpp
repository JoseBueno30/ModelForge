#include "ui/components/ThemeManager.h"
#include<ui/components/ConsoleHandler.h>
#include <string>

QTextEdit* ConsoleHandler::console = nullptr;

ConsoleHandler::ConsoleHandler(){}

void ConsoleHandler::setConsole(QTextEdit* console){
    ConsoleHandler::console = console;
    ConsoleHandler::console->setReadOnly(1);
}

QString getCurrentTime(){
    QTime currentTime = QTime::currentTime();
    return currentTime.toString("HH:mm:ss");
}

void ConsoleHandler::appendErrorLog(QString errorLog){
    QString errorContent = ConsoleHandler::console->toHtml() + "<span style='color:#D13030;font-size:17px;'>" + getCurrentTime() + "\t" + errorLog + "</span>";
    ConsoleHandler::console->setHtml(errorContent);
    ConsoleHandler::console->moveCursor(QTextCursor::End);
}

void ConsoleHandler::appendSuccessfulLog(QString successfulLog){
    QString successfulContent = ConsoleHandler::console->toHtml() + "<span style='color:#30A456;font-size:17px;'>" + getCurrentTime() + "\t" + successfulLog + "</span>";
    ConsoleHandler::console->setHtml(successfulContent);
    ConsoleHandler::console->moveCursor(QTextCursor::End);
}

void ConsoleHandler::appendStandardLog(QString log){
    QString content = ConsoleHandler::console->toHtml() + "<span style='color:#2AA1DC;font-size:17px;'>" + getCurrentTime() + "\t" + log + "</span>";
    ConsoleHandler::console->setHtml(content);
    ConsoleHandler::console->moveCursor(QTextCursor::End);
}

void ConsoleHandler::clear(){
    ConsoleHandler::console->clear();
}
