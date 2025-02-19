#include<ui/components/ConsoleHandler.h>

ConsoleHandler::ConsoleHandler(){}

void ConsoleHandler::setConsole(QTextEdit* console){
    this->console = console;
    this->console->setReadOnly(1);
}

QString getCurrentTime(){
    QTime currentTime = QTime::currentTime();
    return currentTime.toString("HH:mm:ss");
}

void ConsoleHandler::appendErrorLog(QString errorLog){
    QString errorContent = this->console->toHtml() + "<span style='color:#D13030;font-size:17px;'>" + getCurrentTime() + "\t" + errorLog + "</span>";
    this->console->setHtml(errorContent);
}

void ConsoleHandler::appendSuccessfulLog(QString successfulLog){
    QString successfulContent = this->console->toHtml() + "<span style='color:#30A456;font-size:17px;'>" + getCurrentTime() + "\t" + successfulLog + "</span>";
    this->console->setHtml(successfulContent);
}

void ConsoleHandler::clear(){
    this->console->clear();
}
