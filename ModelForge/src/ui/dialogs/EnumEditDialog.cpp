#include <include/ui/dialogs/EnumEditDialog.h>

#include <src/ui/dialogs/ui_EnumEditDialog.h>

EnumEditDialog::EnumEditDialog(std::shared_ptr<MetaModel::MetaEnum> metaEnum, QGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model, QWidget* parent)
    : metaEnum(metaEnum), scene(scene), model(model), ui(new Ui::EnumEditDialog),QDialog(parent)
{
    ui->setupUi(this);

    ui->nameLineEdit->setText(QString::fromStdString(metaEnum->getName()));
    loadElements();
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
