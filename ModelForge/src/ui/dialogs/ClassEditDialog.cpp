#include "ui/dialogs/OperationEditDialog.h"
#include <ui/dialogs/ClassEditDialog.h>
#include <src/ui/dialogs/ui_ClassEditDialog.h>
#include <utils/Commands.h>
#include <utils/MessageBox.h>

#include <ui/dialogs/AttributeEditDialog.h>
#include <ui/dialogs/MainWindow.h>

#include <QComboBox>
#include <QLabel>

ClassEditDialog::ClassEditDialog(std::shared_ptr<MetaModel::MetaClass> metaClass, ModelGraphicsScene* scene, ClassItemView* classView, std::shared_ptr<MetaModel::MetaModel> model, QWidget *parent) :
    QDialog(parent), metaClass(metaClass), model(model), classView(classView),
    ui(new Ui::ClassEditDialog), scene(scene)
{
    ui->setupUi(this);
    ui->classNameEdit->setText(QString::fromStdString(metaClass->getName()));
    ui->attributeTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->attributeTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->operationTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->operationTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->editedClass = std::make_shared<MetaModel::MetaClass>(*metaClass);

    this->attributeCounter = metaClass->getAttributes().size() + 1;
    this->operationCounter = metaClass->getOperations().size() + 1;

    ui->attributeTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->operationTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    ui->isAbstractCheckBox->setChecked(this->metaClass->getIsAbstract());

    loadAttributes();
    loadOperations();

    connect(ui->addAttributeButton, &QPushButton::clicked, this, &ClassEditDialog::addAttribute);
    connect(ui->removeAttributeButton, &QPushButton::clicked, this, &ClassEditDialog::removeAttribute);
    connect(ui->attributeTableWidget, &QTableWidget::cellDoubleClicked, this, &ClassEditDialog::attributeCellDoubleClicked);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &ClassEditDialog::saveChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &ClassEditDialog::cancelChanges);

    connect(ui->addOperationButton, &QPushButton::clicked, this, &ClassEditDialog::addOperation);
    connect(ui->removeOperationButton, &QPushButton::clicked, this, &ClassEditDialog::removeOperation);
    connect(ui->operationTableWidget, &QTableWidget::cellDoubleClicked, this, &ClassEditDialog::operationCellDoubleClicked);

}

ClassEditDialog::~ClassEditDialog()
{
    delete ui;
}

void ClassEditDialog::loadAttributes() {
    ui->attributeTableWidget->setRowCount(0);  // Limpiar tabla antes de cargar
    int row = 0;

    for (const auto &pair : this->editedClass->getAttributes()) {  // Asumiendo que `getAttributes()` devuelve `std::map<std::string, std::string>`
        ui->attributeTableWidget->insertRow(row);

        // Nombre del atributo (QLineEdit)
        //QLineEdit *nameEdit = new QLineEdit(QString::fromStdString(pair.first));
        QLabel *nameLabel = new QLabel(QString::fromStdString(pair.first));
        nameLabel->setAlignment(Qt::AlignCenter);
        ui->attributeTableWidget->setCellWidget(row, 0, nameLabel);

        // Tipo del atributo (QComboBox)
        // QComboBox *typeCombo = new QComboBox();
        // typeCombo->addItems({"int", "float", "string", "bool"});  // Agrega más tipos según necesidad
        // typeCombo->setCurrentText(QString::fromStdString(pair.second->getType().toString()));
        QLabel *typeLabel = new QLabel(QString::fromStdString(pair.second->getType().toString()));
        typeLabel->setAlignment(Qt::AlignCenter);
        ui->attributeTableWidget->setCellWidget(row, 1, typeLabel);

        row++;
    }
}

void ClassEditDialog::loadOperations(){
    ui->operationTableWidget->setRowCount(0);  // Limpiar tabla antes de cargar
    int row = 0;

    for (const auto &pair : this->editedClass->getOperations()) {  // Asumiendo que `getOperations()` devuelve `std::map<std::string, std::string>`
        ui->operationTableWidget->insertRow(row);

        // Nombre del atributo (QLineEdit)
        //QLineEdit *nameEdit = new QLineEdit(QString::fromStdString(pair.first));
        QLabel *nameLabel = new QLabel(QString::fromStdString(pair.first));
        nameLabel->setAlignment(Qt::AlignCenter);
        ui->operationTableWidget->setCellWidget(row, 0, nameLabel);

        // Tipo del atributo (QComboBox)
        // QComboBox *typeCombo = new QComboBox();
        // typeCombo->addItems({"int", "float", "string", "bool"});  // Agrega más tipos según necesidad
        // typeCombo->setCurrentText(QString::fromStdString(pair.second->getType().toString()));
        QLabel *typeLabel = new QLabel(QString::fromStdString(pair.second->getReturnType().toString()));
        typeLabel->setAlignment(Qt::AlignCenter);
        ui->operationTableWidget->setCellWidget(row, 1, typeLabel);

        row++;
    }
}

void ClassEditDialog::attributeCellDoubleClicked(int row, int column){
    //qDebug()<< "r: "<< row << " c:" << column;
    QLabel * item = dynamic_cast<QLabel*>(ui->attributeTableWidget->cellWidget(row, 0)); //get the attribute name cell
    //qDebug() << "crea el item";
    qDebug() << "Editar atributo: " << item->text();
    std::shared_ptr<MetaModel::MetaAttribute> metaAttribute = this->editedClass->getAttribute(item->text().toStdString());
    AttributeEditDialog *attrEditDialog = new AttributeEditDialog(metaAttribute, editedClass, false, this);
    attrEditDialog->exec();
}

void ClassEditDialog::operationCellDoubleClicked(int row, int column){
    QLabel * item = dynamic_cast<QLabel*>(ui->operationTableWidget->cellWidget(row, 0));

    std::shared_ptr<MetaModel::MetaOperation> metaOperation = this->editedClass->getOperation(item->text().toStdString());
    OperationEditDialog* opEditDialog = new OperationEditDialog(metaOperation, editedClass, false, this);
    opEditDialog->exec();
}

void ClassEditDialog::addOperation(){
    std::string operationName = "operation" + std::to_string(this->operationCounter);

    while(this->editedClass->getOperation(operationName) != nullptr){
        this->operationCounter++;
        operationName = "operation" + std::to_string(this->operationCounter);
    }

    auto metaOperation = std::make_shared<MetaModel::MetaOperation>(operationName, "", MetaModel::Integer::instance());
    OperationEditDialog *opEditDialog = new OperationEditDialog(metaOperation, editedClass, true, this);
    int opEditDialogReturnCode = opEditDialog->exec();

    if(opEditDialogReturnCode == 1){
        this->editedClass->addOperation(metaOperation);
        this->loadOperations();
    }
}
void ClassEditDialog::removeOperation(){
    if(ui->operationTableWidget->currentRow() == -1){
        return;
    }

    auto *operationLabel = dynamic_cast<QLabel*>(this->ui->operationTableWidget->cellWidget(this->ui->operationTableWidget->currentRow(), 0));
    auto operationName = operationLabel->text().toStdString();

    auto reply = showQuestionMessageBox("Remove operation", QString::fromStdString("Do you want to remove the operation '" + operationName + "'?"), this);
    if(reply == QMessageBox::No){
        return;
    }

    this->editedClass->removeOperation(operationName);
    this->loadOperations();
}

void ClassEditDialog::addAttribute() {
    std::string attributeName = "attribute" + std::to_string(this->attributeCounter);

    while(this->editedClass->getAttribute(attributeName) != nullptr){
        this->attributeCounter++;
        attributeName = "attribute" + std::to_string(this->attributeCounter);
    }

    auto metaAttribute = std::make_shared<MetaModel::MetaAttribute>(attributeName , MetaModel::Integer::instance());

    AttributeEditDialog *attrEditDialog = new AttributeEditDialog(metaAttribute, editedClass, true, this);

    int attrEditDialogReturnCode = attrEditDialog->exec();

    if(attrEditDialogReturnCode == 1){
        this->editedClass->addAttribute(metaAttribute);
        this->loadAttributes();
    }

}

void ClassEditDialog::removeAttribute() {
    if(ui->attributeTableWidget->currentRow() == -1){
        return;
    }

    auto *attributeLabel = dynamic_cast<QLabel*>(this->ui->attributeTableWidget->cellWidget(this->ui->attributeTableWidget->currentRow(), 0));
    auto attributeName = attributeLabel->text().toStdString();

    auto reply = showQuestionMessageBox("Remove attribute", QString::fromStdString("Do you want to remove the attribute '" + attributeName + "'?"), this);
    if(reply == QMessageBox::No){
        return;
    }

    this->editedClass->removeAttribute(attributeName);
    this->loadAttributes();
}

void ClassEditDialog::saveChanges() {
    try{
        std::map<std::string, std::string> newAttributes;

        for (int row = 0; row < ui->attributeTableWidget->rowCount(); ++row) {
            QLineEdit *nameEdit = qobject_cast<QLineEdit *>(ui->attributeTableWidget->cellWidget(row, 0));
            QComboBox *typeCombo = qobject_cast<QComboBox *>(ui->attributeTableWidget->cellWidget(row, 1));

            if (nameEdit && typeCombo) {
                newAttributes[nameEdit->text().toStdString()] = typeCombo->currentText().toStdString();
            }
        }

        this->editedClass->setIsAbstract(ui->isAbstractCheckBox->isChecked());
        this->editedClass->setName(ui->classNameEdit->text().toStdString());


        //ACTUALIZAR MAPA DE MAINWINDOW EN LOS COMANDOS
        if(model == nullptr){
            MainWindow::undoStack->push(new EditMetaClassCommand(this->metaClass, this->editedClass, classView, this->scene));
        }else{
            classView = new ClassItemView(this->editedClass);
            MainWindow::undoStack->push(new AddMetaClassCommand(this->model, this->editedClass, classView, this->scene));
        }

        //qDebug() << "Nombre: " << this->metaClass->getName();

        this->scene->update();

        accept();  // Cierra el diálogo y guarda cambios
    }catch(const std::runtime_error& exception){
        showExceptionMessageBox("Error", "There was an error saving the class. Check the console for more information");
        ConsoleHandler::appendErrorLog(exception.what());
    }


}

void ClassEditDialog::cancelChanges(){
    auto reply = showQuestionMessageBox("Edit class", "Changes have not been saved. Do you want to cancel?", this);

    if(reply == QMessageBox::No){
        return;
    }

    reject();
}

bool ClassEditDialog::isValidClass(){
    bool isValid = true;

    return isValid;
}
