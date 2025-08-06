#include "utils/MessageBox.h"
#include <ui/dialogs/VariableEditDialog.h>

#include <src/ui/dialogs/ui_VariableEditDialog.h>

#include <QPushButton>

#include <ui/components/ConsoleHandler.h>

VariableEditDialog::VariableEditDialog(std::shared_ptr<MetaModel::MetaVariable> metaVariable,std::shared_ptr<MetaModel::MetaOperation> metaOperation, bool isNew, QWidget* parent)
    : metaVariable(metaVariable), metaOperation(metaOperation), isNew(isNew), QDialog(parent){
    ui = new Ui::VariableEditDialog();
    ui->setupUi(this);

    ui->nameLineEdit->setText(QString::fromStdString(metaVariable->getName()));
    loadComboBoxTypes();

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &VariableEditDialog::saveChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &VariableEditDialog::cancelChanges);

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
    if(!isValidVariable()){
        showExceptionMessageBox("Error", "There was an error saving the condition. Check the console for more information.");
        return;
    }

    metaVariable->setName(ui->nameLineEdit->text().toStdString());

    metaVariable->setType(getTypeFromComboBox());

    accept();
}

void VariableEditDialog::cancelChanges(){
    auto reply = showQuestionMessageBox("Edit variable", "Changes have not been saved. Do you want to cancel?", this);

    if(reply == QMessageBox::No){
        return;
    }

    reject();
}

bool VariableEditDialog::isValidVariable(){
    bool isValid = true;

    std::string variableName = ui->nameLineEdit->text().toStdString();
    if(metaOperation->getVariable(variableName) && isNew){
        ConsoleHandler::appendErrorLog("Operation '" + QString::fromStdString(metaOperation->getName()) + "' already contains variable called: " + QString::fromStdString(variableName));
        isValid = false;
    }

    return isValid;
}
