#include <utils/MessageBox.h>

#include <QMessageBox>

void showExceptionMessageBox(QString title, QString msg, QWidget* parent){
    QMessageBox::critical(parent, title, msg);
}

QMessageBox::StandardButton showQuestionMessageBox(QString title, QString msg, QWidget* parent){
    auto reply = QMessageBox::warning(parent, title, msg, QMessageBox::Yes | QMessageBox::No);
    return reply;
}
