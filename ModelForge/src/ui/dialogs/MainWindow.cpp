#include <ui/dialogs/MainWindow.h>
#include "ui/dialogs/EnumEditDialog.h"
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
#include <modelToText/VisitorJava.h>
#include <modelToText/VisitorUSE.h>
#include <ui/components/ThemeManager.h>
#include <QStyleFactory>
#include <utils/Commands.h>
#include <ui/dialogs/AssociationEditDialog.h>
#include <ui/dialogs/ClassEditDialog.h>
#include <metamodel/MetaAssociation.h>
#include <QMessageBox>
#include <QInputDialog>

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
    setupUndoStack();

    //qDebug() << "Palette: " << qApp->palette().window();
    ThemeManager::createPalettes(qApp->palette());
    qApp->setStyle(QStyleFactory::create("fusion"));

    //qApp->setPalette(ui->centralwidget->palette());
    connect(ui->actionOpen_Model, &QAction::triggered, this, &MainWindow::openModelFile);
    connect(ui->actionSwitch_mode, &QAction::triggered, this, &openColorThemeAux);
    connect(undoAction, &QAction::triggered, this, &checkTrigger);
    connect(ui->addClassButton, &QPushButton::clicked, this, &MainWindow::openNewClassDialog);
    connect(ui->addAssociationButton, &QPushButton::clicked, this, &MainWindow::openNewAssociationDialog);
    connect(ui->addEnumButton, &QPushButton::clicked, this, &MainWindow::openNewEnumDialog);
    connect(ui->addAssociationClassButton, &QPushButton::clicked, this, &MainWindow::openNewAssociationClassDialog);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveModel);
    connect(ui->actionNew_Model, &QAction::triggered, this, &MainWindow::newModel);
    connect(ui->actionClose_Model, &QAction::triggered, this, &MainWindow::closeModel);
    connect(ui->actionExportJava, &QAction::triggered, this, &MainWindow::exportToJava);

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;

    scene = new ModelGraphicsScene();
    auto clipboard = new ItemViewClipboard(scene, model);
    scene->setClipboard(clipboard);

    connect(ui->actionCopy, &QAction::triggered, scene, &ModelGraphicsScene::copyItemView);
    connect(ui->actionCut, &QAction::triggered, scene, &ModelGraphicsScene::cutItemView);
    connect(ui->actionPaste, &QAction::triggered, scene, &ModelGraphicsScene::pasteItemView);

    bool succes = connect(scene, &ModelGraphicsScene::itemMoved, this, &MainWindow::itemMoved);
    connect(scene, &ModelGraphicsScene::editAssociation, this, &MainWindow::openEditAssociationDialog);
    qDebug() << "Connect = " << succes;
    modelGraphicsView->setScene(scene);

    ThemeManager::getInitialTheme();
    openColorTheme(false);

    disableModelActions();

    ConsoleHandler::setConsole(this->ui->consoleTextEdit);
}

void MainWindow::setupUndoStack(){
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

    ui->modelGraphicsView->setModel(model);
    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;

    QGraphicsScene *scene = modelGraphicsView->scene();

    qDebug() <<"SCENE: "<< scene;

    for(const auto& modelEnum : model->getEnums()){
        EnumItemView * item = new EnumItemView(modelEnum.second, xOffset, yOffset, width, height);
        this->scene->addModelItemView(modelEnum.second->getName(), item);
        scene->addItem(item);

        xOffset+=200;
    }

    yOffset+=50;

    for(const auto& modelClass : model->getClasses()){
        ClassItemView* item = new ClassItemView(modelClass.second, xOffset, yOffset);
        this->scene->addModelItemView(modelClass.second->getName(), item);
        scene->addItem(item);

        xOffset += 200;
    }

    // Draw generalizations
    for(const auto& modelClass : model->getClasses()){
        if(!modelClass.second->getSuperClasses().empty()){
            ClassItemView* subClass = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(modelClass.second->getName()));
            auto superClassIterator = modelClass.second->getSuperClasses().begin();
            for(; superClassIterator != modelClass.second->getSuperClasses().end(); superClassIterator++){
                ClassItemView* superClass = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(superClassIterator->second->getName()));

                GeneralizationItemView *generalization = new GeneralizationItemView(superClass, subClass);
                scene->addItem(generalization);
            }
        }

    }

    //TODO - use model iterators
    for(const auto& modelAssoc : model->getAssociations()){
        ClassItemView* class1 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(modelAssoc.second->getAssociationEndsClassesNames().at(0)));
        ClassItemView* class2 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(modelAssoc.second->getAssociationEndsClassesNames().at(1)));
        AssociationItemView* item = new AssociationItemView(modelAssoc.second, class1, class2);
        this->scene->addModelItemView(modelAssoc.second->getName(), item);
        scene->addItem(item);
    }

    for(const auto& modelAssocClass : model->getAssociationClasses()){
        ClassItemView* class1 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(modelAssocClass.second->getAssociationEndsClassesNames().at(0)));
        ClassItemView* class2 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(modelAssocClass.second->getAssociationEndsClassesNames().at(1)));
        AssociationClassItemView* item = new AssociationClassItemView(modelAssocClass.second, class1, class2);
        qDebug() << "AsocClass: " << modelAssocClass.second->getName();
        this->scene->addModelItemView(modelAssocClass.second->getName(), item);
        scene->addItem(item);
        item->addItemsToScene();
    }
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

void MainWindow::openNewAssociationDialog(){
    if(this->model != nullptr){
        std::string defaultName = "NewAssociation";
        int defaultNameCont = 0;
        for(auto metaAssociationPair : this->model->getAssociations()){
            if(metaAssociationPair.first == defaultName){
                defaultNameCont++;
                defaultName = "NewAssociation" + std::to_string(defaultNameCont);
            }
        }
        std::shared_ptr<MetaModel::MetaAssociation> newAssociation = std::make_shared<MetaModel::MetaAssociation>(defaultName, 0);
        AssociationEditDialog *associationEditDialog = new AssociationEditDialog(newAssociation, this->scene, nullptr, this->model);
        associationEditDialog->exec();
    }
}

void MainWindow::openNewAssociationClassDialog(){
    if(this->model != nullptr){
        std::string defaultName = "NewAssociationClass";
        int defaultNameCont = 0;
        for(auto metaAssociationClassPair : this->model->getAssociationClasses()){
            if(metaAssociationClassPair.first == defaultName){
                defaultNameCont++;
                defaultName = "NewAssociationClass" + std::to_string(defaultNameCont);
            }
        }

        std::shared_ptr<MetaModel::MetaAssociationClass> newAssociationClass = std::make_shared<MetaModel::MetaAssociationClass>(defaultName, false, 0);
        ClassEditDialog* classInfoEdit = new ClassEditDialog(newAssociationClass, scene, nullptr, this->model, this);
        int returnCode = classInfoEdit->exec();

        qDebug() << "Atributos de la nueva  clase asociacion: " << newAssociationClass->getAttributes().size();
        if(returnCode){
            AssociationEditDialog* associationInfoEdit = new AssociationEditDialog(newAssociationClass, scene, nullptr, this->model);
            associationInfoEdit->exec();
        }
    }
}

void MainWindow::openEditAssociationDialog(AssociationItemView* association){
    AssociationEditDialog *associationEditDialog = new AssociationEditDialog(association->getAssociationModel(), this->scene, association, this->model);
    associationEditDialog->exec();
}

void MainWindow::openNewEnumDialog(){
    if(this->model != nullptr){
        std::string defaultName = "NewEnum";
        int defaultNameCont = 0;
        for(auto metaEnumPair : this->model->getEnums()){
            if(metaEnumPair.first == defaultName){
                defaultNameCont++;
                defaultName = "NewEnum" + std::to_string(defaultNameCont);
            }
        }
        std::shared_ptr<MetaModel::MetaEnum> newEnum= std::make_shared<MetaModel::MetaEnum>(defaultName);
        EnumEditDialog *enumEditDialog = new EnumEditDialog(newEnum, this->scene, this->model, nullptr, this);
        enumEditDialog->exec();
    }
}


void MainWindow::openModelFile(){
    closeModel();

    try{
        path = QFileDialog::getOpenFileName(this, "Select file", "", "USE files (*.use);;All files (*.*)");
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

        enableModelActions();
    }catch(std::runtime_error error){
        ConsoleHandler::appendErrorLog(error.what());
    }
}

void MainWindow::saveModel(){
    try{
        if(path == nullptr){
            path = QFileDialog::getSaveFileName(
                this,                         // QWidget padre
                "Save file",              // Título del diálogo
                "",                             // Ruta inicial (puedes poner una por defecto)
                "USE files (*.use)" // Filtros
                );

            if (QFile::exists(path)) {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "The file already exists",
                                              "Do you want to overwrite it?",
                                              QMessageBox::Yes | QMessageBox::No);

                if (reply != QMessageBox::Yes) {
                    return; // No guardamos nada
                }

            }else{
                QFile file(path);
                file.open(QIODevice::WriteOnly);
                file.close();
            }
        }

        QFileInfo fileInfo(path);
        qDebug() << "Archivo a guardar: " << path;
        // QString directory = fileInfo.absolutePath();
        ModelToText::VisitorUSE visitorUSE(path.toStdString());

        model->accept(visitorUSE);

        ConsoleHandler::appendSuccessfulLog("The file was succesfully saved.");
    }
    catch(std::runtime_error){
        ConsoleHandler::appendErrorLog("The file couldn't be saved.");
    }

}

void MainWindow::exportToJava(){
    if(path == nullptr){
        QString  path = QFileDialog::getSaveFileName(
            this,                         // QWidget padre
            "Save file",              // Título del diálogo
            "",                             // Ruta inicial (puedes poner una por defecto)
            "USE files (*.use)" // Filtros
            );
        }

    if (!path.isEmpty()) {
        QFileInfo fileInfo(path);
        QString directoryPath = fileInfo.absolutePath();
        qDebug() << "Directory path:" << directoryPath;

        ModelToText::VisitorJava visitorJava(directoryPath.toStdString());

        model->accept(visitorJava);

        ConsoleHandler::appendSuccessfulLog("Java code succesfully generated.");
    }

}

void MainWindow::newModel(){
    closeModel();

    bool ok;
    QString modelName = QInputDialog::getText(
        this,                   // QWidget* parent
        "Create model",               // Título de la ventana
        "Insert the model name:", // Texto del mensaje
        QLineEdit::Normal,      // Tipo de entrada
        "",                     // Texto por defecto
        &ok                     // Si se pulsó OK o Cancelar
        );

    if (!ok || modelName.isEmpty()) {
        modelName = "NewModel";
    }

    model = std::make_shared<MetaModel::MetaModel>(modelName.toStdString());
    this->setupModelGraphicsView(model);

    ConsoleHandler::appendSuccessfulLog(QString::fromStdString("Model '" + model->getName() + "' was succesfully created."));

    enableModelActions();
}

void MainWindow::closeModel(){
    this->model = nullptr;
    this->scene->clear();
    this->scene->update();
    this->path = "";

    MainWindow::undoStack->clear();

    disableModelActions();
}

void MainWindow::enableModelActions(){
    ui->actionCopy->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->actionPaste->setEnabled(true);
    redoAction->setEnabled(true);
    undoAction->setEnabled(true);

    ui->addAssociationButton->setEnabled(true);
    ui->addClassButton->setEnabled(true);
    ui->addAssociationClassButton->setEnabled(true);
    ui->addEnumButton->setEnabled(true);

    ui->actionClose_Model->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionExportJava->setEnabled(true);
}

void MainWindow::disableModelActions(){
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    redoAction->setEnabled(false);
    undoAction->setEnabled(false);

    ui->addAssociationButton->setEnabled(false);
    ui->addClassButton->setEnabled(false);
    ui->addAssociationClassButton->setEnabled(false);
    ui->addEnumButton->setEnabled(false);

    ui->actionClose_Model->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionExportJava->setEnabled(false);
}

void MainWindow::itemMoved(QGraphicsItem * movedItem, const QPointF& oldPos)
{
    qDebug() << "MoveCommand: " << oldPos;
    undoStack->push(new MoveCommand(movedItem, oldPos));
}

