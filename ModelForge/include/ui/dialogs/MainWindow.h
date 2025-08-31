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

    void openModelFile();
    void openNewClassDialog();
    void openNewAssociationDialog();
    void openNewAssociationClassDialog();
    void openEditAssociationDialog(AssociationItemView* association);
    void openEditClassDialog(ClassItemView* classView);
    void openNewEnumDialog();
    void openNewGeneralizationDialog();

    void saveModel();

    void exportToJava();

    void newModel();

    void closeModel();

    void itemMoved(QGraphicsItem * item, const QPointF& pos);



private:
    Ui::MainWindow *ui;
    std::shared_ptr<MetaModel::MetaModel> model;
    QString theme;
    ConsoleHandler* consoleHandler;
    ModelGraphicsScene *scene;

    QString path;

    QAction *undoAction = nullptr;
    QAction *redoAction = nullptr;
    void setupUndoStack();
    void enableModelActions();
    void disableModelActions();
};
#endif // MAINWINDOW_H
