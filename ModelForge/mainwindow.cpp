#include "mainwindow.h"
#include "./ui_mainwindow.h"

void toogleColorTheme(QString &theme){
    QFile file(":/styles/" + theme + ".qss");
    qDebug() << "prueba: " << file.exists();
    if(file.open(QFile::ReadOnly)){
        qDebug() << "entra";
        QString stylesheet = file.readAll();
        qApp->setStyleSheet(stylesheet);
        file.close();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    theme("dark"),
    consoleHandler(new ConsoleHandler())
{
    ui->setupUi(this);

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;
    modelGraphicsView->setScene(new QGraphicsScene(this));

    QGraphicsScene *scene = modelGraphicsView->scene();

    std::shared_ptr<MetaModel::MetaClass> class1 = std::make_shared<MetaModel::MetaClass>("ClaseDePrueba", false);
    const std::shared_ptr<MetaModel::MetaType> type = std::make_shared<MetaModel::MetaType>();
    std::unique_ptr<MetaModel::MetaAttribute> att1 = std::make_unique<MetaModel::MetaAttribute>("att", type);
    class1->addAttribute(att1);
    ClassItemView *classItem = new ClassItemView(class1);
    scene->addItem(classItem);

    toogleColorTheme(theme);

    consoleHandler->setConsole(this->ui->consoleTextEdit);
    consoleHandler->appendErrorLog("Esto es un error");
    consoleHandler->appendSuccessfulLog("Esto es un mensaje gucci");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModelGraphicsView(){

}



void MainWindow::on_actionSwitch_mode_triggered()
{

}

