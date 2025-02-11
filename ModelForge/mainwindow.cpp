#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <ui/ModelGraphicsView.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   // ModelGraphicsView *modelGraphicsView = new ModelGraphicsView(this);
    //graphicsView->setScene()
    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;
    //ui->modelGraphicsView = modelGraphicsView;
    modelGraphicsView->setScene(new QGraphicsScene(this));

    QGraphicsScene *scene = modelGraphicsView->scene();
    scene->addRect(-50, -50, 100, 100, QPen(Qt::black), QBrush(Qt::blue));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModelGraphicsView(){

}
