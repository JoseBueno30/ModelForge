#include <ui/dialogs/ClassEditDialog.h>
#include <src/ui/dialogs/ui_ClassEditDialog.h>
#include <utils/Commands.h>

#include <ui/dialogs/AttributeEditDialog.h>
#include <ui/dialogs/MainWindow.h>

#include <QComboBox>
#include <QLabel>

ClassEditDialog::ClassEditDialog(std::shared_ptr<MetaModel::MetaClass> metaClass, QGraphicsScene* scene, ClassItemView* classView, std::shared_ptr<MetaModel::MetaModel> model, QWidget *parent) :
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

    ui->attributeTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->operationTableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->isAbstractCheckBox->setChecked(this->metaClass->getIsAbstract());

    loadAttributes();
    loadOperations();

    connect(ui->addAttributeButton, &QPushButton::clicked, this, &ClassEditDialog::addAttribute);
    connect(ui->removeAttributeButton, &QPushButton::clicked, this, &ClassEditDialog::removeAttribute);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &ClassEditDialog::saveChanges);
    connect(ui->attributeTableWidget, &QTableWidget::cellDoubleClicked, this, &ClassEditDialog::cellDoubleClicked);

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
        ui->attributeTableWidget->setCellWidget(row, 0, nameLabel);

        // Tipo del atributo (QComboBox)
        // QComboBox *typeCombo = new QComboBox();
        // typeCombo->addItems({"int", "float", "string", "bool"});  // Agrega más tipos según necesidad
        // typeCombo->setCurrentText(QString::fromStdString(pair.second->getType().toString()));
        QLabel *typeLabel = new QLabel(QString::fromStdString(pair.second->getType().toString()));
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
        ui->operationTableWidget->setCellWidget(row, 0, nameLabel);

        // Tipo del atributo (QComboBox)
        // QComboBox *typeCombo = new QComboBox();
        // typeCombo->addItems({"int", "float", "string", "bool"});  // Agrega más tipos según necesidad
        // typeCombo->setCurrentText(QString::fromStdString(pair.second->getType().toString()));
        QLabel *typeLabel = new QLabel(QString::fromStdString(pair.second->getReturnType().toString()));
        ui->operationTableWidget->setCellWidget(row, 1, typeLabel);

        row++;
    }
}

void ClassEditDialog::cellDoubleClicked(int row, int column){
    //qDebug()<< "r: "<< row << " c:" << column;
    QLabel * item = dynamic_cast<QLabel*>(ui->attributeTableWidget->cellWidget(row, column)); //get the attribute name cell
    //qDebug() << "crea el item";
    qDebug() << "Editar atributo: " << item->text();
    std::shared_ptr<MetaModel::MetaAttribute> metaAttribute = this->editedClass->getAttribute(item->text().toStdString());
    AttributeEditDialog *attrEditDialog = new AttributeEditDialog(metaAttribute, true, this);
    attrEditDialog->exec();
}


void ClassEditDialog::addAttribute() {
    std::string attributeName = "attribute" + std::to_string(this->attributeCounter);

    while(this->editedClass->getAttribute(attributeName) != nullptr){
        this->attributeCounter++;
        attributeName = "attribute" + std::to_string(this->attributeCounter);
    }

    auto metaAttribute = std::make_shared<MetaModel::MetaAttribute>(attributeName , MetaModel::Integer::instance());

    AttributeEditDialog *attrEditDialog = new AttributeEditDialog(metaAttribute, false, this);

    int attrEditDialogReturnCode = attrEditDialog->exec();

    // Add attribute to editedClass (as an action in UndoStack)
    if(attrEditDialogReturnCode == 1){
        this->editedClass->addAttribute(metaAttribute);
        this->loadAttributes();
    }

}

void ClassEditDialog::removeAttribute() {
    auto *attributeLabel = dynamic_cast<QLabel*>(this->ui->attributeTableWidget->cellWidget(this->ui->attributeTableWidget->currentRow(), 0));
    auto attributeName = attributeLabel->text().toStdString();

    this->editedClass->removeAttribute(attributeName);
    this->loadAttributes();
}

void ClassEditDialog::saveChanges() {
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

    if(model == nullptr){
        MainWindow::undoStack->push(new EditMetaClassCommand(this->metaClass, this->editedClass, classView, this->scene));
    }else{
        classView = new ClassItemView(this->editedClass);
        MainWindow::undoStack->push(new AddMetaClassCommand(this->model, this->editedClass, classView, this->scene));
    }

    //qDebug() << "Nombre: " << this->metaClass->getName();

    this->scene->update();

    accept();  // Cierra el diálogo y guarda cambios
}
