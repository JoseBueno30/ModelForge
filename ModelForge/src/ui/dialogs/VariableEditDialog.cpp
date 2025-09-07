#include "metamodel/MetaModel.h"
#include "utils/MessageBox.h"
#include <ui/dialogs/VariableEditDialog.h>

#include <src/ui/dialogs/ui_VariableEditDialog.h>

#include <QPushButton>

#include <ui/components/ConsoleHandler.h>

VariableEditDialog::VariableEditDialog(std::shared_ptr<MetaModel::MetaVariable> metaVariable, std::shared_ptr<MetaModel::MetaOperation> metaOperation,  std::shared_ptr<MetaModel::MetaModel> metaModel, QWidget* parent)
    : metaVariable(metaVariable), metaOperation(metaOperation), metaModel(metaModel), QDialog(parent){
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
    for (const auto& [name, cls] : metaModel->getClasses()) {
        ui->typeComboBox->addItem(QString::fromStdString(name));
    }
    for (const auto& [name, en] : metaModel->getEnums()) {
        ui->typeComboBox->addItem(QString::fromStdString(name));
    }
    for (const auto& [name, assocCls] : metaModel->getAssociationClasses()) {
        ui->typeComboBox->addItem(QString::fromStdString(name));
    }
    ui->typeComboBox->setCurrentText(QString::fromStdString(metaVariable->getType().toString()));
}

std::shared_ptr<MetaModel::MetaType> VariableEditDialog::getTypeFromComboBox(QString type){
    if (type == "Integer"){
        return MetaModel::Integer::instance();
    }else if(type == "Real"){
        return MetaModel::Real::instance();
    }else if(type == "String"){
        return MetaModel::String::instance();
    }else if(type == "Boolean"){
        return MetaModel::Boolean::instance();
    }
    if (auto cls = metaModel->getClass(type.toStdString())) {
        return cls;
    }
    if (auto en = metaModel->getEnum(type.toStdString())) {
        return en;
    }
    if (auto assocCls = metaModel->getAssociationClass((type.toStdString()))){
        return assocCls;
    }

    return nullptr;
}

void VariableEditDialog::saveChanges(){
    if(!isValidVariable()){
        showExceptionMessageBox("Error", "There was an error saving the condition. Check the console for more information.");
        return;
    }

    metaVariable->setName(ui->nameLineEdit->text().toStdString());

    metaVariable->setType(getTypeFromComboBox(ui->typeComboBox->currentText()));

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
    auto auxVariable = metaOperation->getVariable(variableName);
    if( auxVariable && auxVariable != metaVariable){
        ConsoleHandler::appendErrorLog("Operation '" + QString::fromStdString(metaOperation->getName()) + "' already contains variable called: " + QString::fromStdString(variableName));
        isValid = false;
    }

    return isValid;
}
