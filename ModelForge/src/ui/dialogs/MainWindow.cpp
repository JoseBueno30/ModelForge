#include <ui/dialogs/MainWindow.h>
#include "ui_MainWindow.h"


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
#include <QStyleFactory>
#include <utils/Commands.h>
#include <ui/dialogs/ClassEditDialog.h>

QUndoStack* MainWindow::undoStack = new QUndoStack();

void openColorTheme(bool toogle = true){
    if(toogle) ThemeManager::toogleTheme();
    else qDebug() << "no toogle" << toogle;

    QString theme = ThemeManager::getTheme() ? "light" : "dark";
    QFile file(":/styles/" + theme + ".qss");
    qDebug() << "Tema: " << theme;
    qApp->setPalette(theme == "light" ? ThemeManager::getLightPalette() : ThemeManager::getDarkPalette());

    QPalette defaultPalette = QApplication::palette();

    qDebug() << "Color de fondo:" << defaultPalette.color(QPalette::Window);
    qDebug() << "Color de texto:" << defaultPalette.color(QPalette::WindowText);
    qDebug() << "Color de fondo del botón:" << defaultPalette.color(QPalette::Button);
    qDebug() << "Color de texto del botón:" << defaultPalette.color(QPalette::ButtonText);

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

void checkTrigger(){
    qDebug() << "Ctrl + z";
}
void openColorThemeAux(){
    openColorTheme();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    theme("dark")
{
    ui->setupUi(this);
    //qDebug() << ui->actionOpen_Model->icon().name() << "\t" << ui->actionOpen_Model->icon().themeName();
    setupActions();

    //qDebug() << "Palette: " << qApp->palette().window();
    ThemeManager::createPalettes(qApp->palette());
    qApp->setStyle(QStyleFactory::create("fusion"));

    //qApp->setPalette(ui->centralwidget->palette());
    connect(ui->actionOpen_Model, &QAction::triggered, this, &MainWindow::openModelFile);
    connect(ui->actionSwitch_mode, &QAction::triggered, this, &openColorThemeAux);
    connect(undoAction, &QAction::triggered, this, &checkTrigger);
    connect(ui->addClassButton, &QPushButton::clicked, this, &MainWindow::openNewClassDialog);

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;
    scene = new ModelGraphicsScene();
    bool succes = connect(scene, &ModelGraphicsScene::itemMoved, this, &MainWindow::itemMoved);
    qDebug() << "Connect = " << succes;
    modelGraphicsView->setScene(scene);

    ThemeManager::getInitialTheme();
    openColorTheme(false);


    ConsoleHandler::setConsole(this->ui->consoleTextEdit);
}

void MainWindow::setupActions(){
    undoStack = new QUndoStack(this);
    undoStack->setUndoLimit(20);

    undoAction = undoStack->createUndoAction(this, tr("Undo"));
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setIcon(QIcon::fromTheme("edit-undo"));
    ui->menuEdit->addAction(undoAction);

    redoAction = undoStack->createRedoAction(this, tr("Redo"));
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setIcon(QIcon::fromTheme("edit-redo"));
    ui->menuEdit->addAction(redoAction);
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

    QGraphicsScene *scene = modelGraphicsView->scene();

    qDebug() <<"SCENE: "<< scene;

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

std::string base_name(std::string const & path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

void MainWindow::openNewClassDialog(){
    qDebug() << "lol";
    if(this->model != nullptr){
        std::string defaultName = "NewClass";
        int defaultNameCont = 0;
        for(auto metaClassPair : this->model->getClasses()){
            if(metaClassPair.first == defaultName){
                defaultNameCont++;
                defaultName = "NewClass" + std::to_string(defaultNameCont);
            }
        }
        std::shared_ptr<MetaModel::MetaClass> newMetaClass = std::make_shared<MetaModel::MetaClass>(defaultName, false);
        ClassEditDialog *classEdit = new ClassEditDialog(newMetaClass, this->scene, nullptr, this->model, this);
        classEdit->exec();
    }
}


void MainWindow::openModelFile(){
    try{
        QString path = QFileDialog::getOpenFileName(this, "Select file", "", "USE files (*.use);;All files (*.*)");
        if (path.isEmpty()) {
            return;
        }

        std::ifstream file(path.toStdString());

        if (!file) {
            throw std::runtime_error("(0/)ModelForge didn't find the file.");
        }
        ConsoleHandler::appendStandardLog(QString::fromStdString("Loading '" + base_name(path.toStdString()) + "'"));
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
        model = visitor.model;
        this->setupModelGraphicsView(model);
        ConsoleHandler::appendSuccessfulLog(QString::fromStdString("Model '" + model->getName() + "' was succesfully loaded."));

        QFileInfo fileInfo(path);
        QString directory = fileInfo.absolutePath();
        ModelToText::VisitorUSE visitorUSE((directory + "/TEST.use").toStdString());

        model->accept(visitorUSE);
    }catch(std::runtime_error error){
        ConsoleHandler::appendErrorLog(error.what());
    }
}

void MainWindow::itemMoved(QGraphicsItem * movedItem, const QPointF& oldPos)
{
    qDebug() << "MoveCommand: " << oldPos;
    undoStack->push(new MoveCommand(movedItem, oldPos));
}

