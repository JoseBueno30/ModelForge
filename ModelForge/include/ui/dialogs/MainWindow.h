#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui/components/ConsoleHandler.h"
#include <QMainWindow>
#include <QApplication>
#include <ui/view/ClassItemView.h>
#include <ui/components/ModelGraphicsScene.h>
#include <ui/components/ModelGraphicsView.h>
#include <QFile>
#include <QUndoStack>

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

    static QUndoStack *undoStack;

public Q_SLOTS:
    void on_actionSwitch_mode_triggered();

    void setModel(std::shared_ptr<MetaModel::MetaModel> model);
    std::shared_ptr<MetaModel::MetaModel> getModel();
    void setupModelGraphicsView(std::shared_ptr<MetaModel::MetaModel> model);

    QGraphicsItem* getModelItemView(const std::string& key);
    void addModelItemView(const std::string& key, QGraphicsItem *item);
    void removeModelItemView(const std::string& key);

    void openModelFile();
    void openNewClassDialog();
    void itemMoved(QGraphicsItem * item, const QPointF& pos);



private:
    Ui::MainWindow *ui;
    std::shared_ptr<MetaModel::MetaModel> model;
    QString theme;
    ConsoleHandler* consoleHandler;
    std::map<std::string, QGraphicsItem*> modelItemViewElementsMap;
    ModelGraphicsScene *scene;

    QAction *undoAction = nullptr;
    QAction *redoAction = nullptr;
    void setupActions();
};
#endif // MAINWINDOW_H
