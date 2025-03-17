#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <ui/view/AssociationClassItemView.h>
#include <ui/view/AssociationItemView.h>
#include <ui/view/EnumItemView.h>
#include <ui/view/GeneralizationItemView.h>
#include <antlr4-runtime.h>
#include <QFileDialog>
#include <antlr4/generated/USELexer.h>
#include <antlr4/generated/USEParser.h>
#include <antlr4/CustomUSEVisitor.cpp>
#include <modelToText/VisitorUSE.h>
#include <ui/components/ThemeManager.h>

void toogleColorTheme(){
    ThemeManager::toogleTheme();
    QString theme = ThemeManager::getTheme() ? "light" : "dark";
    QFile file(":/styles/" + theme + ".qss");
    qDebug() << "Tema: " << theme;
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
    theme("dark")
{
    ui->setupUi(this);
    connect(ui->actionOpen_Model, &QAction::triggered, this, &MainWindow::openModelFile);
    connect(ui->actionSwitch_mode, &QAction::triggered, this, &toogleColorTheme);

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;
    modelGraphicsView->setScene(new QGraphicsScene(this));

    toogleColorTheme();


    ConsoleHandler::setConsole(this->ui->consoleTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModelGraphicsView(std::shared_ptr<MetaModel::MetaModel> model){
    // qDebug() << "El nombre del MetaModel es: " << model->getName();

    int xOffset = -450;
    int yOffset = -200;
    int width = 150;
    int height = 150;

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;
    modelGraphicsView->setScene(new QGraphicsScene(this));

    QGraphicsScene *scene = modelGraphicsView->scene();

    for(const auto& modelEnum : model->getEnums()){
        EnumItemView * item = new EnumItemView(modelEnum.second, xOffset, yOffset, width, height);
        this->addModelItemView(modelEnum.second->getName(), item);
        scene->addItem(item);

        xOffset+=200;
    }

    yOffset+=50;

    for(const auto& modelClass : model->getClasses()){
        ClassItemView* item = new ClassItemView(modelClass.second, xOffset, yOffset);
        this->addModelItemView(modelClass.second->getName(), item);
        scene->addItem(item);

        xOffset += 200;
    }

    // Draw generalizations
    for(const auto& modelClass : model->getClasses()){
        if(!modelClass.second->getSuperClasses().empty()){
            ClassItemView* subClass = dynamic_cast<ClassItemView*>(this->getModelItemView(modelClass.second->getName()));
            auto superClassIterator = modelClass.second->getSuperClasses().begin();
            for(; superClassIterator != modelClass.second->getSuperClasses().end(); superClassIterator++){
                ClassItemView* superClass = dynamic_cast<ClassItemView*>(this->getModelItemView(superClassIterator->second->getName()));

                GeneralizationItemView *generalization = new GeneralizationItemView(superClass, subClass);
                scene->addItem(generalization);
            }
        }

    }

    //TODO - use model iterators
    for(const auto& modelAssoc : model->getAssociations()){
        ClassItemView* class1 = dynamic_cast<ClassItemView*>(this->getModelItemView(modelAssoc.second->getAssociationEndsClassesNames().at(0)));
        ClassItemView* class2 = dynamic_cast<ClassItemView*>(this->getModelItemView(modelAssoc.second->getAssociationEndsClassesNames().at(1)));
        AssociationItemView* item = new AssociationItemView(modelAssoc.second, class1, class2);
        this->addModelItemView(modelAssoc.second->getName(), item);
        scene->addItem(item);
    }

    for(const auto& modelAssocClass : model->getAssociationClasses()){
        ClassItemView* class1 = dynamic_cast<ClassItemView*>(this->getModelItemView(modelAssocClass.second->getAssociationEndsClassesNames().at(0)));
        ClassItemView* class2 = dynamic_cast<ClassItemView*>(this->getModelItemView(modelAssocClass.second->getAssociationEndsClassesNames().at(1)));
        AssociationClassItemView* item = new AssociationClassItemView(modelAssocClass.second, class1, class2);
        qDebug() << "AsocClass: " << modelAssocClass.second->getName();
        scene->addItem(item);
        item->addItemsToScene();
    }
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

void MainWindow::openModelFile(){
    try{
        QString path = QFileDialog::getOpenFileName(this, "Select file", "", "USE files (*.use);;All files (*.*)");
        if (path.isEmpty()) {
            throw std::runtime_error("No se seleccionó ningún archivo");
        }

        std::ifstream file(path.toStdString());

        if (!file) {
            throw std::runtime_error("No se pudo abrir el archivo");
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        antlr4::ANTLRInputStream input(buffer.str());

        USELexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        USEParser parser(&tokens);

        USEParser::ModelContext* tree = parser.model();

        // Crea el visitor y visita el árbol
        CustomUSEVisitor visitor;
        visitor.visit(tree);

        // Verifica que el MetaModel se haya creado correctamente
        auto model = visitor.model;
        this->setupModelGraphicsView(model);

        QFileInfo fileInfo(path);
        QString directory = fileInfo.absolutePath();
        ModelToText::VisitorUSE visitorUSE((directory + "/TEST.use").toStdString());

        model->accept(visitorUSE);
    }catch(std::runtime_error error){
        ConsoleHandler::appendErrorLog(error.what());
    }

}

