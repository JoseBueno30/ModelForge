#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <ui/ClassItemView.h>
#include <ui/ModelGraphicsView.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;
    modelGraphicsView->setScene(new QGraphicsScene(this));

    QGraphicsScene *scene = modelGraphicsView->scene();

    ClassItemView *classItem = new ClassItemView(nullptr);
    scene->addItem(classItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModelGraphicsView(){

}
