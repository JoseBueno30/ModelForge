#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui/components/ConsoleHandler.h"
#include <QMainWindow>
#include <QApplication>
#include <ui/view/ClassItemView.h>
#include <ui/components/ModelGraphicsView.h>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    void on_actionSwitch_mode_triggered();

    void setModel(std::shared_ptr<MetaModel::MetaModel> model);
    std::shared_ptr<MetaModel::MetaModel> getModel();
    void setupModelGraphicsView(std::shared_ptr<MetaModel::MetaModel> model);

private:
    Ui::MainWindow *ui;
    std::shared_ptr<MetaModel::MetaModel> model;
    QString theme;
    ConsoleHandler* consoleHandler;

};
#endif // MAINWINDOW_H
