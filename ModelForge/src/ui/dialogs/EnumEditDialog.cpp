#include "ui/dialogs/MainWindow.h"
#include <include/ui/dialogs/EnumEditDialog.h>

#include <src/ui/dialogs/ui_EnumEditDialog.h>

#include <metamodel/MetaEnum.h>

#include <utils/Commands.h>

EnumEditDialog::EnumEditDialog(std::shared_ptr<MetaModel::MetaEnum> metaEnum, QGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model, EnumItemView * itemView, QWidget* parent)
    : metaEnum(metaEnum), scene(scene), model(model), ui(new Ui::EnumEditDialog), itemView(itemView),QDialog(parent)
{
    ui->setupUi(this);

    ui->nameLineEdit->setText(QString::fromStdString(metaEnum->getName()));
    loadElements();

    connect(ui->addElementButton, &QPushButton::clicked, this, &EnumEditDialog::addElement);
    connect(ui->deleteElementButton, &QPushButton::clicked, this, &EnumEditDialog::deleteElement);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &EnumEditDialog::saveChanges);
}

void EnumEditDialog::loadElements(){
    ui->enumElementsTable->setRowCount(0);
    // Supón que quieres que la última columna (índice 2) se estire
    ui->enumElementsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    int row = 0;
    for(auto metaEnumElementPair : metaEnum->getElements()){
        ui->enumElementsTable->insertRow(row);

        // QLabel *elementLabel = new QLabel(QString::fromStdString(metaEnumElementPair.first));
        QLineEdit *elementLineEdit = new QLineEdit();
        elementLineEdit->setText(QString::fromStdString(metaEnumElementPair.first));
        ui->enumElementsTable->setCellWidget(row,0,elementLineEdit);

        row++;
    }
}

void EnumEditDialog::setMetaEnum(std::shared_ptr<MetaModel::MetaEnum> metaEnumPointer){
    metaEnumPointer->setName(ui->nameLineEdit->text().toStdString());
    for(int row = 0; row < ui->enumElementsTable->rowCount(); row++){
        auto elementLineEdit = qobject_cast<QLineEdit *>(ui->enumElementsTable->cellWidget(row, 0));
        std::shared_ptr<MetaModel::MetaEnumElement> metaEnumElement = std::make_shared<MetaModel::MetaEnumElement>(elementLineEdit->text().toStdString());
        metaEnumPointer->addElement(metaEnumElement);
    }
}


void EnumEditDialog::saveChanges(){
    if(model){ //Creating metaEnum
        setMetaEnum(this->metaEnum);
        itemView = new EnumItemView(this->metaEnum);

        AddMetaEnumCommand* addCommand = new AddMetaEnumCommand(this->metaEnum,this->model, itemView, this->scene);
        MainWindow::undoStack->push(addCommand);
    }
    else{ //Edit metaEnum

        std::shared_ptr<MetaModel::MetaEnum> newMetaEnum =std::make_shared<MetaModel::MetaEnum>("");
        setMetaEnum(newMetaEnum);

        EditMetaEnumCommand* editCommand = new EditMetaEnumCommand(this->metaEnum, newMetaEnum, itemView, this->scene);
        MainWindow::undoStack->push(editCommand);
    }
}

void EnumEditDialog::addElement(){
    int nRows = ui->enumElementsTable->rowCount();

    ui->enumElementsTable->insertRow(nRows);
    QLineEdit *elementLineEdit = new QLineEdit();
    ui->enumElementsTable->setCellWidget(nRows,0,elementLineEdit);
    elementLineEdit->setFocus();
}
void EnumEditDialog::deleteElement(){
    int selectedRow = ui->enumElementsTable->currentRow();

    ui->enumElementsTable->removeRow(selectedRow);
}
