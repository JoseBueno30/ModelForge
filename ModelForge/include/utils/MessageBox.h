#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <QString>
#include <QWidget>

void showExceptionMessageBox(QString title, QString msg, QWidget* parent=nullptr);
QMessageBox::StandardButton showQuestionMessageBox(QString title, QString msg, QWidget* parent=nullptr);

#endif // MESSAGEBOX_H
