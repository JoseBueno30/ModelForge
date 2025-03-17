#include<ui/components/ConsoleHandler.h>

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
}

void ConsoleHandler::appendSuccessfulLog(QString successfulLog){
    QString successfulContent = ConsoleHandler::console->toHtml() + "<span style='color:#30A456;font-size:17px;'>" + getCurrentTime() + "\t" + successfulLog + "</span>";
    ConsoleHandler::console->setHtml(successfulContent);
}

void ConsoleHandler::clear(){
    ConsoleHandler::console->clear();
}
