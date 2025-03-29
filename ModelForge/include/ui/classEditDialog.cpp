#include "classEditDialog.h"

#include <ui_classEditDialog.h>
#include <QComboBox>
#include <QLabel>
#include <AttributeEditDialog.h>

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
    AttributeEditDialog *attrEditDialog = new AttributeEditDialog(metaAttribute, this);
    attrEditDialog->exec();
}


void ClassEditDialog::addAttribute() {
    int row = ui->attributeTableWidget->rowCount();
    ui->attributeTableWidget->insertRow(row);

    // Nuevo nombre de atributo
    QLineEdit *nameEdit = new QLineEdit();
    ui->attributeTableWidget->setCellWidget(row, 0, nameEdit);

    // Tipo de atributo (desplegable)
    QComboBox *typeCombo = new QComboBox();
    typeCombo->addItems({"int", "float", "string", "bool"});
    ui->attributeTableWidget->setCellWidget(row, 1, typeCombo);
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
