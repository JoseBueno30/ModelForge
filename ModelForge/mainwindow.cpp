#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <ui/view/AssociationClassItemView.h>
#include <ui/view/AssociationItemView.h>
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

void MainWindow::setModel(std::shared_ptr<MetaModel::MetaModel> model){
    this->model = model;
}

std::shared_ptr<MetaModel::MetaModel> MainWindow::getModel(){
    return this->model;
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
    class1->addAttribute(std::move(att1));

    std::unique_ptr<MetaModel::MetaOperation> op = std::make_unique<MetaModel::MetaOperation>("operation", "i + 1", type);
    key = op->getName();
    class1->addOperation(std::move(op));

    ClassItemView *classItem = new ClassItemView(class1);
    scene->addItem(classItem);

    std::shared_ptr<MetaModel::MetaClass> class2 = std::make_shared<MetaModel::MetaClass>("ClaseDePrueba2", true);
    ClassItemView *classItem2 = new ClassItemView(class2, 350, 0);
    scene->addItem(classItem2);

    // qDebug() << classItem->scenePos() << "\t" <<classItem2->scenePos();

    // std::shared_ptr<MetaModel::MetaAssociation> association = std::make_shared<MetaModel::MetaAssociation>("prueba", 2);
    // AssociationItemView * associationItemView = new AssociationItemView(association, classItem, classItem2);
    std::shared_ptr<MetaModel::MetaAssociationClass> associationClass = std::make_shared<MetaModel::MetaAssociationClass>("ClaseDePrueba3", false, 2);
    AssociationClassItemView * associationClassItemView = new AssociationClassItemView(associationClass, classItem, classItem2);
    scene->addItem(associationClassItemView);
    associationClassItemView->addItemsToScene();

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

void MainWindow::setupModelGraphicsView(std::shared_ptr<MetaModel::MetaModel> model){
    // qDebug() << "El nombre del MetaModel es: " << model->getName();

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;

    QGraphicsScene *scene = modelGraphicsView->scene();

    for(const auto& modelEnum : model->getEnums()){
        EnumItemView * item = new EnumItemView(modelEnum.second);
        this->addModelItemView(modelEnum.second->getName(), item);
        scene->addItem(item);
    }

    for(const auto& modelClass : model->getClasses()){
        ClassItemView* item = new ClassItemView(modelClass.second);
        this->addModelItemView(modelClass.second->getName(), item);
        scene->addItem(item);
    }

    // for(const auto& modelAssoc : model->getAssociations()){
    //     scene->addItem(new AssociationItemView(modelAssoc.second));
    // }

    // for(const auto& modelAssocClass : model->getAssociationClasses()){
    //     scene->addItem(new AssociationClassItemView(modelAssocClass.second));
    // }
}

QGraphicsItem* MainWindow::getModelItemView(const std::string& key){
    auto iterator = this->modelItemViewElementsMap.find(key);
    if(iterator != this->modelItemViewElementsMap.end()){
        return (iterator->second);
    }
    return nullptr;
}

void MainWindow::addModelItemView(const std::string& key, QGraphicsItem *item){
    this->modelItemViewElementsMap[key] = item;
}

void MainWindow::removeModelItemView(const std::string& key){
    this->modelItemViewElementsMap.erase(key);
}

void MainWindow::on_actionSwitch_mode_triggered()
{

}

