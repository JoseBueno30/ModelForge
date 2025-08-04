#include <ui/dialogs/VariableEditDialog.h>

#include <src/ui/dialogs/ui_VariableEditDialog.h>

#include <QPushButton>

VariableEditDialog::VariableEditDialog(std::shared_ptr<MetaModel::MetaVariable> metaVariable , QWidget* parent) : metaVariable(metaVariable), QDialog(parent){
    ui = new Ui::VariableEditDialog();
    ui->setupUi(this);

    ui->nameLineEdit->setText(QString::fromStdString(metaVariable->getName()));
    loadComboBoxTypes();

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &VariableEditDialog::saveChanges);
}

void VariableEditDialog::loadComboBoxTypes(){
    ui->typeComboBox->addItems({"Integer", "Real", "String", "Boolean"});
    ui->typeComboBox->setCurrentText(QString::fromStdString(metaVariable->getType().toString()));
}

std::shared_ptr<MetaModel::MetaType> VariableEditDialog::getTypeFromComboBox(){
    switch (ui->typeComboBox->currentIndex()) {
    case 0:
        return MetaModel::Integer::instance();
        break;
    case 1:
        return MetaModel::Real::instance();
        break;
    case 2:
        return MetaModel::String::instance();
        break;
    case 3:
        return MetaModel::Boolean::instance();
    default:
        return MetaModel::Integer::instance(); // Devolver tipo personalizado del modelo si se puediese
        break;
    }
}

void VariableEditDialog::saveChanges(){
    metaVariable->setName(ui->nameLineEdit->text().toStdString());

    metaVariable->setType(getTypeFromComboBox());

    accept();
}
