#include <ui/dialogs/MainWindow.h>
#include "ui/dialogs/EnumEditDialog.h"
#include "ui_MainWindow.h"
#include "utils/MessageBox.h"


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
#include <ui/dialogs/AddGeneraliaztionDialog.h>
#include <ui/dialogs/AssociationEditDialog.h>
#include <ui/dialogs/ClassEditDialog.h>
#include <metamodel/MetaAssociation.h>
#include <QMessageBox>
#include <QInputDialog>
#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonDocument>

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
    connect(ui->actionOpen_Layout, &QAction::triggered, this, &MainWindow::openLayoutFile);
    connect(ui->actionSave_layout, &QAction::triggered, this, &MainWindow::saveLayout);
    connect(ui->addGeneralizationButton, &QPushButton::clicked, this, &MainWindow::openNewGeneralizationDialog);

    QGraphicsView * modelGraphicsView = ui->modelGraphicsView;

    scene = new ModelGraphicsScene();
    auto clipboard = new ItemViewClipboard(scene, model);
    scene->setClipboard(clipboard);

    connect(ui->actionCopy, &QAction::triggered, scene, &ModelGraphicsScene::copyItemView);
    connect(ui->actionCut, &QAction::triggered, scene, &ModelGraphicsScene::cutItemView);
    connect(ui->actionPaste, &QAction::triggered, scene, &ModelGraphicsScene::pasteItemView);

    bool succes = connect(scene, &ModelGraphicsScene::itemMoved, this, &MainWindow::itemMoved);
    connect(scene, &ModelGraphicsScene::editAssociation, this, &MainWindow::openEditAssociationDialog);
    connect(scene, &ModelGraphicsScene::editClass, this, &MainWindow::openEditClassDialog);
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

    for(const auto& modelAssociationClass : model->getAssociationClasses()){
        if(!modelAssociationClass.second->getSuperClasses().empty()){
            AssociationClassItemView* subClass = dynamic_cast<AssociationClassItemView*>(this->scene->getModelItemView(modelAssociationClass.second->getName()));
            auto superClassIterator = modelAssociationClass.second->getSuperClasses().begin();
            for(; superClassIterator != modelAssociationClass.second->getSuperClasses().end(); superClassIterator++){
                AssociationClassItemView* superClass = dynamic_cast<AssociationClassItemView*>(this->scene->getModelItemView(superClassIterator->second->getName()));

                GeneralizationItemView *generalization = new GeneralizationItemView(superClass->getAssociationClassItemView(), subClass->getAssociationClassItemView());
                scene->addItem(generalization);
            }
        }
    }
}

void MainWindow::openCLTLayout(QFile& file){
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ConsoleHandler::appendErrorLog("No se pudo abrir el archivo:" + path);
        return;
    }

    QXmlStreamReader xml(&file);
    bool inStrategy = false;
    QString id = "";
    QString type = "";
    double x = 0, y = 0;

    qDebug() << "Leyendo archivo";
    while (!xml.atEnd() && !xml.hasError()) {
        auto token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            // qDebug() << "Etiqueta: " << xml.name();
            if (xml.name() == "node") {
                // qDebug() << xml.attributes().value("id").toString() << " " << xml.attributes().value("type").toString();
                id = xml.attributes().value("id").toString();
                type = xml.attributes().value("type").toString();
                // qDebug() << "Guarda " << id << " y " << type;
            }
            else if (xml.name() == "strategy") {
                inStrategy = true;
            }
            else if (inStrategy && xml.name() == "x") {
                x = xml.readElementText().toDouble();
            }
            else if (inStrategy && xml.name() == "y") {
                y = xml.readElementText().toDouble();
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            // qDebug() << "sale en " << xml.name();
            if (xml.name() == "strategy") {
                inStrategy = false;
            } else if (xml.name() == "node") {

                // qDebug() << type << " a guardar";
                if (type == "Class" || type == "Enum") {
                    auto item = this->scene->getModelItemView(id.toStdString());

                    if(type == "Class"){
                        if(auto auxAssociationClass = dynamic_cast<AssociationClassItemView*>(item)){
                            auxAssociationClass->getAssociationClassItemView()->setPos(x,y);
                            auxAssociationClass->getAssociationClassItemView()->updateConnectionPositions();
                        }
                        else{
                            item->setPos(x,y);
                            if(auto auxItem = dynamic_cast<ClassItemView*>(item)){
                                auxItem->updateConnectionPositions(); // Fix update association class dot line
                            }
                        }
                    }
                }
            }
        }
    }
    this->scene->update();

    qDebug() << "Cerrando archivo";

    if (xml.hasError()) {
        qWarning() << "Error en XML:" << xml.errorString();
    }

    file.close();

}

void MainWindow::openJSONLayout(QFile& file){
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "No se pudo abrir el archivo JSON";
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Error al parsear JSON:" << parseError.errorString();
        return ;
    }

    if (!doc.isObject()) {
        qWarning() << "El JSON raíz no es un objeto";
        return;
    }

    QJsonObject root = doc.object();
    for (auto it = root.begin(); it != root.end(); ++it) {
        QString nodeName = it.key();
        QJsonObject posObj = it.value().toObject();

        double x = posObj["x"].toDouble();
        double y = posObj["y"].toDouble();

        auto item = this->scene->getModelItemView(nodeName.toStdString());

        if(!dynamic_cast<AssociationItemView*>(item)){
            if(auto auxAssocClass = dynamic_cast<AssociationClassItemView*>(item)){
                auxAssocClass->getAssociationClassItemView()->setPos(x,y);
                auxAssocClass->getAssociationClassItemView()->updateConnectionPositions();
            }else{
                item->setPos(x,y);
                if(auto classItem = dynamic_cast<ClassItemView*>(item)){
                    classItem->updateConnectionPositions();
                }
            }
        }
    }
    this->scene->update();
}

void MainWindow::openLayoutFile(){

    path = QFileDialog::getOpenFileName(this, "Select file", "", "USE Layout files (*.clt);;JSON Layout files (*.json);;All files (*.*)");
    if (path.isEmpty()) {
        return;
    }

    QFile file(path);
    QFileInfo info(path);
    try{
        if(info.suffix() == "clt"){
            openCLTLayout(file);
        }else if(info.suffix() == "json"){
            openJSONLayout(file);
        }
    }catch(std::exception e){
        ConsoleHandler::appendErrorLog("Ha habido un error inesperado al intentar abrir el layout");
    }
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

void MainWindow::openEditClassDialog(ClassItemView* classView){
    ClassEditDialog *classEdit = new ClassEditDialog(classView->getClassModel(), scene, classView, model, this);
    classEdit->exec();
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

void MainWindow::openNewGeneralizationDialog(){
    AddGeneralizationDialog* addGeneralizationDialog = new AddGeneralizationDialog(this->model, this->scene, this);
    addGeneralizationDialog->exec();
}

std::shared_ptr<MetaModel::MetaModel> MainWindow::loadModel(std::ifstream& file){
    std::ostringstream buffer;
    buffer << file.rdbuf();
    antlr4::ANTLRInputStream input(buffer.str());

    USELexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    USEParser parser(&tokens);

    USEParser::ModelContext* tree = parser.model();

    CustomUSEVisitor visitor;
    visitor.visit(tree);

    return visitor.model;
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

        auto model = loadModel(file);

        this->setupModelGraphicsView(model);
        ui->modelNameLineEdit->setText(QString::fromStdString(model->getName()));
        ConsoleHandler::appendSuccessfulLog(QString::fromStdString("Model '" + model->getName() + "' was succesfully loaded."));

        enableModelActions();
    }catch(std::runtime_error error){
        ConsoleHandler::appendErrorLog(error.what());
    }
}

void MainWindow::saveLayout(){
    path = QFileDialog::getSaveFileName(
        this,                         // QWidget padre
        "Save file",              // Título del diálogo
        QString::fromStdString(this->model->getName() + ".json"),                             // Ruta inicial (puedes poner una por defecto)
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
    }else {
        QJsonObject root;

        for(auto itemPair : this->scene->getModelItemViewElementsMap()){
            if(!dynamic_cast<AssociationItemView*>(itemPair.second)){
                QJsonObject pos;
                if(auto assocClass = dynamic_cast<AssociationClassItemView*>(itemPair.second)){
                    pos["x"] = assocClass->getAssociationClassItemView()->pos().x();
                    pos["y"] = assocClass->getAssociationClassItemView()->pos().y();
                }else{
                    pos["x"] = itemPair.second->pos().x();
                    pos["y"] = itemPair.second->pos().y();
                }
                root[QString::fromStdString(itemPair.first)] = pos;
            }
        }

        QJsonDocument doc(root);
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning() << "No se pudo abrir el archivo para escribir:" << path;
            return;
        }

        file.write(doc.toJson(QJsonDocument::Indented)); // formato bonito
        file.close();
    }
}

void MainWindow::saveModel(){
    try{
        this->model->setName(ui->modelNameLineEdit->text().toStdString());
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

        QString tempPath = QDir::temp().filePath("modelforge_tmp.use");
        {
            ModelToText::VisitorUSE tempVisitor(tempPath.toStdString());
            model->accept(tempVisitor);
        }

        std::shared_ptr<MetaModel::MetaModel> testModel;
        try {
            std::ifstream tempFile(tempPath.toStdString());
            testModel = loadModel(tempFile);
            tempFile.close();
        } catch (const std::exception &ex) {
            ConsoleHandler::appendErrorLog("Validation failed: the model can't be saved.");
            QFile::remove(tempPath);
            return;
        }

        if (!testModel) {
            ConsoleHandler::appendErrorLog("Validation failed: the model can't be saved.");
            QFile::remove(tempPath);
            return;
        } else {
            ModelToText::VisitorUSE visitorUSE(path.toStdString());
            model->accept(visitorUSE);
        }

        QFile::remove(tempPath);
        ConsoleHandler::appendSuccessfulLog("The file was successfully saved.");
    }
    catch (const std::runtime_error& e) {
        ConsoleHandler::appendErrorLog(QString("The file couldn't be saved: ") + QString::fromUtf8(e.what()));
    }

}

void MainWindow::exportToJava(){
    try{
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
    catch (const std::runtime_error& e) {
        ConsoleHandler::appendErrorLog(QString("Java code couldn't be generated: ") + QString::fromUtf8(e.what()));
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

    if (!ok){
        return;
    }else if(modelName.isEmpty()) {
        modelName = "NewModel";
    }

    model = std::make_shared<MetaModel::MetaModel>(modelName.toStdString());
    this->setupModelGraphicsView(model);

    ConsoleHandler::appendSuccessfulLog(QString::fromStdString("Model '" + model->getName() + "' was succesfully created."));

    enableModelActions();
}

void MainWindow::closeModel(){
    if(model){
        auto response = showQuestionMessageBox("Close Model", "Are you sure you want to close the model?");

        if(response == QMessageBox::No){
            return;
        }
    }

    ui->modelNameLineEdit->setText("");
    this->model = nullptr;
    this->scene->clear();
    this->scene->update();
    this->path = "";

    MainWindow::undoStack->clear();

    disableModelActions();
}

void MainWindow::enableModelActions(){
    ui->modelNameLineEdit->setEnabled(true);

    ui->actionCopy->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->actionPaste->setEnabled(true);
    redoAction->setEnabled(true);
    undoAction->setEnabled(true);

    ui->addAssociationButton->setEnabled(true);
    ui->addClassButton->setEnabled(true);
    ui->addAssociationClassButton->setEnabled(true);
    ui->addEnumButton->setEnabled(true);
    ui->addGeneralizationButton->setEnabled(true);

    ui->actionClose_Model->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionExportJava->setEnabled(true);
}

void MainWindow::disableModelActions(){
    ui->modelNameLineEdit->setEnabled(false);

    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    redoAction->setEnabled(false);
    undoAction->setEnabled(false);

    ui->addAssociationButton->setEnabled(false);
    ui->addClassButton->setEnabled(false);
    ui->addAssociationClassButton->setEnabled(false);
    ui->addEnumButton->setEnabled(false);
    ui->addGeneralizationButton->setEnabled(false);

    ui->actionClose_Model->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionExportJava->setEnabled(false);
}

void MainWindow::itemMoved(QGraphicsItem * movedItem, const QPointF& oldPos)
{
    qDebug() << "MoveCommand: " << oldPos;
    undoStack->push(new MoveCommand(movedItem, oldPos));
}

