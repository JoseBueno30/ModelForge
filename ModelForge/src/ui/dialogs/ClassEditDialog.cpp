#include <ui/dialogs/ClassEditDialog.h>
#include <src/ui/dialogs/ui_ClassEditDialog.h>

#include <ui/dialogs/AttributeEditDialog.h>

#include <QComboBox>
#include <QLabel>

ClassEditDialog::ClassEditDialog(QWidget *parent, std::shared_ptr<MetaModel::MetaClass> metaClass) :
    QDialog(parent), metaClass(metaClass),
    ui(new Ui::ClassEditDialog)
{
    ui->setupUi(this);
    ui->classNameEdit->setText(QString::fromStdString(metaClass->getName()));

    ui->attributeTableWidget->horizontalHeader()->setStretchLastSection(true);

    loadAttributes();

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

    for (const auto &pair : metaClass->getAttributes()) {  // Asumiendo que `getAttributes()` devuelve `std::map<std::string, std::string>`
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

void ClassEditDialog::cellDoubleClicked(int row, int column){
    //qDebug()<< "r: "<< row << " c:" << column;
    QLabel * item = dynamic_cast<QLabel*>(ui->attributeTableWidget->cellWidget(row, column/2)); //get the attribute name cell
    //qDebug() << "crea el item";
    qDebug() << "Editar atributo: " << item->text();
    std::shared_ptr<MetaModel::MetaAttribute> metaAttribute = metaClass->getAttribute(item->text().toStdString());
    AttributeEditDialog *attrEditDialog = new AttributeEditDialog(metaAttribute, true, this);
    attrEditDialog->exec();
}


void ClassEditDialog::addAttribute() {
    std::shared_ptr<MetaModel::MetaAttribute> metaAttribute = std::make_shared<MetaModel::MetaAttribute>("attribute", MetaModel::Integer::instance());

    AttributeEditDialog *attrEditDialog = new AttributeEditDialog(metaAttribute, false, this);

    int attrEditDialogReturnCode = attrEditDialog->exec();

    // Add attribute to metaClass (as an action in UndoStack)
    if(attrEditDialogReturnCode == 1){
        metaClass->addAttribute(metaAttribute);
        this->loadAttributes();
    }

}

void ClassEditDialog::removeAttribute() {
    int row = ui->attributeTableWidget->currentRow();
    if (row >= 0) {
        ui->attributeTableWidget->removeRow(row);
    }
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

    accept();  // Cierra el diálogo y guarda cambios
}
