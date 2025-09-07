#include "utils/MessageBox.h"
#include <ui/dialogs/AttributeEditDialog.h>

#include <QPushButton>

#include <src/ui/dialogs/ui_AttributeEditDialog.h>
#include <metamodel/MetaType.h>
#include <ui/components/ConsoleHandler.h>

AttributeEditDialog::AttributeEditDialog(std::shared_ptr<MetaModel::MetaAttribute> metaAttribute, std::shared_ptr<MetaModel::MetaClass> metaClass, std::shared_ptr<MetaModel::MetaModel> metaModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditDialog),
    metaAttribute(metaAttribute),
    metaClass(metaClass),
    metaModel(metaModel)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &AttributeEditDialog::saveChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &AttributeEditDialog::cancelChanges);


    ui->nameLineEdit->setText(QString::fromStdString(metaAttribute->getName()));
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
    ui->typeComboBox->setCurrentText(QString::fromStdString(metaAttribute->getType().toString()));

    if(auto collectionType = std::dynamic_pointer_cast<MetaModel::CollectionType>(metaAttribute->getTypePtr())){
        ui->collectionGroupBox->setChecked(true);
        ui->isUniqueCheckBox->setChecked(collectionType->getIsUnique());
        ui->isOrderedCheckBox->setChecked(collectionType->getIsOrdered());
    }

    loadVisibility();
}

AttributeEditDialog::~AttributeEditDialog()
{
    delete ui;
}

void AttributeEditDialog::loadVisibility(){
    switch (metaAttribute->getVisibility()) {
    case MetaModel::Visibility::Public:
        ui->publicRadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Private:
        ui->privateRadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Protected:
        ui->protectedRadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Package:
        ui->packageRadioButton->setChecked(true);
        break;

    default:
        break;
    }
}

void AttributeEditDialog::saveVisibility(){
    MetaModel::Visibility vis = MetaModel::Visibility::Package;
    if(ui->publicRadioButton->isChecked()){
        vis = MetaModel::Visibility::Public;
    }
    else if(ui->privateRadioButton->isChecked()){
        vis = MetaModel::Visibility::Private;
    }
    else if(ui->protectedRadioButton->isChecked()){
        vis = MetaModel::Visibility::Protected;
    }

    metaAttribute->setVisibility(vis);
}
std::shared_ptr<MetaModel::MetaType> AttributeEditDialog::getSingleTypeFromComboBox(QString type){
    if (type == "Integer"){
        return MetaModel::Integer::instance();
    }
    else if(type == "Real"){
        return MetaModel::Real::instance();
    }
    else if(type == "String"){
        return MetaModel::String::instance();
    }
    else if(type == "Boolean"){
        return MetaModel::Boolean::instance();
    }
    else if (auto cls = metaModel->getClass(type.toStdString())) {
        return cls;
    }
    else if (auto en = metaModel->getEnum(type.toStdString())) {
        return en;
    }
    else if (auto assocCls = metaModel->getAssociationClass((type.toStdString()))){
        return assocCls;
    }

    return nullptr;
}

std::shared_ptr<MetaModel::MetaType> AttributeEditDialog::getType(QString type){
    auto typePtr = getSingleTypeFromComboBox(type);
    if(ui->collectionGroupBox->isChecked()){
        auto collection = std::make_shared<MetaModel::CollectionType>(ui->isOrderedCheckBox->isChecked(), ui->isUniqueCheckBox->isChecked(), ui->sizeSpinBox->value(), typePtr);
        return collection;
    }else{
        return typePtr;
    }
}

void AttributeEditDialog::saveChanges(){

    if(!isValidAttribute()){
        showExceptionMessageBox("Error", "There was an unexpected error saving the attribute. Please check the console for more information.");
        return;
    }

    metaAttribute->setName(ui->nameLineEdit->text().toStdString());
    metaAttribute->setType(getType(ui->typeComboBox->currentText()));

    saveVisibility();

    if(!ui->derivedExprTextEdit->toPlainText().isEmpty()){
        std::shared_ptr<MetaModel::Expr> derivedExpr = std::make_shared<MetaModel::Expr>(ui->derivedExprTextEdit->toPlainText().toStdString());
        metaAttribute->setDeriveExpr(derivedExpr);
    }else if(!ui->initExprTextEdit->toPlainText().isEmpty()){
        std::shared_ptr<MetaModel::Expr> initExpr = std::make_shared<MetaModel::Expr>(ui->initExprTextEdit->toPlainText().toStdString());
        metaAttribute->setInitExpr(initExpr);
    }

    accept();
}

void AttributeEditDialog::cancelChanges(){
    auto reply = showQuestionMessageBox("Edit attribute", "Changes have not been saved. Do you want to cancel?", this);

    if(reply == QMessageBox::No){
        return;
    }

    reject();
}

bool AttributeEditDialog::isValidAttribute(){
    bool isValid = true;

    std::string attributeName = ui->nameLineEdit->text().toStdString();
    auto auxAttribute = metaClass->getAttribute(attributeName);
    if( auxAttribute && auxAttribute != metaAttribute){
        ConsoleHandler::appendErrorLog("Class '" + QString::fromStdString(metaClass->getName()) + "' already have an attribute named '"
                                       + QString::fromStdString(metaAttribute->getName()) +"'.");
        isValid = false;
    }

    //Check expr?

    return isValid;
}
