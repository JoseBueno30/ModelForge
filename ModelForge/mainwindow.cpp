#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <ui/view/EnumItemView.h>

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
    const std::shared_ptr<MetaModel::Integer> type = MetaModel::Integer::instance();
    std::unique_ptr<MetaModel::MetaAttribute> att1 = std::make_unique<MetaModel::MetaAttribute>("att", type);
    std::string key = att1->getName();
    class1->addAttribute(key,std::move(att1));

    std::unique_ptr<MetaModel::MetaOperation> op = std::make_unique<MetaModel::MetaOperation>("operation", "i + 1", type);
    key = op->getName();
    class1->addOperation(key, std::move(op));

    ClassItemView *classItem = new ClassItemView(class1);
    scene->addItem(classItem);

    // std::unique_ptr<MetaModel::MetaEnumElement> enumElement = std::make_unique<MetaModel::MetaEnumElement>("Adriduty");
    // std::unique_ptr<MetaModel::MetaEnumElement> enumElement2 = std::make_unique<MetaModel::MetaEnumElement>("MrDeif");
    // std::unique_ptr<MetaModel::MetaEnumElement> enumElement3 = std::make_unique<MetaModel::MetaEnumElement>("Kirito");
    // std::shared_ptr<MetaModel::MetaEnum> enumModel = std::make_shared<MetaModel::MetaEnum>("Rukai", std::move(enumElement));
    // std::string key = enumElement2->getName();
    // enumModel->addElement(key, std::move(enumElement2));
    // key = enumElement3->getName();
    // enumModel->addElement(key, std::move(enumElement3));
    // EnumItemView *enum1 = new EnumItemView(enumModel);
    // scene->addItem(enum1);

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

