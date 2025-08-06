#include "utils/MessageBox.h"
#include <ui/dialogs/ConditionEditDialog.h>
#include <ui/dialogs/OperationEditDialog.h>
#include <ui/dialogs/VariableEditDialog.h>
#include <src/ui/dialogs/ui_OperationEditDialog.h>

OperationEditDialog::OperationEditDialog(std::shared_ptr<MetaModel::MetaOperation> metaOperation, QWidget* parent) : metaOperation(metaOperation), QDialog(parent), ui(new Ui::OperationEditDialog)
{
    ui->setupUi(this);
    ui->operationNamelineEdit->setText(QString::fromStdString(metaOperation->getName()));

    loadReturnType();
    loadVisibility();
    loadVariables();
    ui->conditionsTableWidget->setRowCount(0);
    loadConditions(metaOperation->getPreConditions());
    loadConditions(metaOperation->getPostConditions());

    variablesCont = metaOperation->getVariables().size();
    conditionsCont = metaOperation->getPostConditions().size() + metaOperation->getPreConditions().size();

    ui->variablesTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->conditionsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->variablesTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->conditionsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->variablesTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->conditionsTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &OperationEditDialog::saveChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &OperationEditDialog::cancelChanges);


    connect(ui->addVariablePushButton, &QPushButton::clicked, this, &OperationEditDialog::addNewVariable);
    connect(ui->removeVariablePushButton, &QPushButton::clicked, this, &OperationEditDialog::removeVariable);
    connect(ui->addConditionPushButton, &QPushButton::clicked, this, &OperationEditDialog::addNewCondition);
    connect(ui->removeConditionPushButon, &QPushButton::clicked, this, &OperationEditDialog::removeCondition);
    connect(ui->variablesTableWidget, &QTableWidget::cellDoubleClicked, this, &OperationEditDialog::variableCellDoubleClicked);
    connect(ui->conditionsTableWidget, &QTableWidget::cellDoubleClicked, this, &OperationEditDialog::conditionCellDoubleClicked);
}

void OperationEditDialog::loadReturnType(){
    ui->returnTypeComboBox->addItems({"Integer", "Real", "String", "Boolean"});
    ui->returnTypeComboBox->setCurrentText(QString::fromStdString(metaOperation->getReturnType().toString()));
}

void OperationEditDialog::loadVariables(){
    ui->variablesTableWidget->setRowCount(0);  // Limpiar tabla antes de cargar
    int row = 0;

    for(auto variablePair : metaOperation->getVariables()){
        ui->variablesTableWidget->insertRow(row);

        QLabel *nameLabel = new QLabel(QString::fromStdString(variablePair.first));
        nameLabel->setAlignment(Qt::AlignCenter);
        ui->variablesTableWidget->setCellWidget(row, 0, nameLabel);

        QLabel *typeLabel = new QLabel(QString::fromStdString(variablePair.second->getType().toString()));
        typeLabel->setAlignment(Qt::AlignCenter);
        ui->variablesTableWidget->setCellWidget(row, 1, typeLabel);

        row++;
    }
}

void OperationEditDialog::loadConditions(std::map<std::string, std::shared_ptr<MetaModel::PrePostClause>> conditions){
    int row = 0;

    for(auto conditionPair : conditions){
        qDebug() << "fila: " << row;
        ui->conditionsTableWidget->insertRow(row);

        QLabel *nameLabel = new QLabel(QString::fromStdString(conditionPair.first));
        nameLabel->setAlignment(Qt::AlignCenter);
        ui->conditionsTableWidget->setCellWidget(row, 0, nameLabel);

        QLabel *typeLabel = new QLabel(conditionPair.second->getIsPost() ? "Post" : "Pre");
        typeLabel->setAlignment(Qt::AlignCenter);
        ui->conditionsTableWidget->setCellWidget(row, 1, typeLabel);

        row++;
    }
}

void OperationEditDialog::loadVisibility(){
    switch (metaOperation->getVisibility()) {
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

void OperationEditDialog::conditionCellDoubleClicked(int row, int column){
    QLabel * item = dynamic_cast<QLabel*>(ui->conditionsTableWidget->cellWidget(row, 0));
    QLabel * type = dynamic_cast<QLabel*>(ui->conditionsTableWidget->cellWidget(row, 1));

    std::shared_ptr<MetaModel::PrePostClause> condition ;
    if(type->text().toLower() == "pre"){
        condition = metaOperation->getPreCondition(item->text().toStdString());
    }else{
        condition = metaOperation->getPostCondition(item->text().toStdString());
    }
    ConditionEditDialog* conditionEditDialog = new ConditionEditDialog(condition);

    int returnCode = conditionEditDialog->exec();
    if(returnCode == 1){
        ui->conditionsTableWidget->setRowCount(0);
        loadConditions(metaOperation->getPreConditions());
        loadConditions(metaOperation->getPostConditions());
    }
}

void OperationEditDialog::addNewCondition(){
    auto conditionExpression = std::make_shared<MetaModel::Expr>("");
    auto newCondition = std::make_shared<MetaModel::PrePostClause>("NewPrePostClause"+ std::to_string(conditionsCont), conditionExpression, true, false);

    ConditionEditDialog* conditionEditDialog = new ConditionEditDialog(newCondition);
    int returnCode = conditionEditDialog->exec();

    if (returnCode == 1){
        ui->conditionsTableWidget->setRowCount(0);
        if(newCondition->getIsPost()){
            metaOperation->addPostCondition(newCondition);
        }else{
            metaOperation->addPreCondition(newCondition);
        }
        loadConditions(metaOperation->getPreConditions());
        loadConditions(metaOperation->getPostConditions());
        conditionsCont++;
    }
}

void OperationEditDialog::removeCondition(){
    if(ui->conditionsTableWidget->currentRow() == -1){
        return;
    }

    auto *conditionNameLabel = dynamic_cast<QLabel*>(this->ui->conditionsTableWidget->cellWidget(this->ui->conditionsTableWidget->currentRow(), 0));
    auto conditionName = conditionNameLabel->text().toStdString();

    auto reply = showQuestionMessageBox("Remove operation", QString::fromStdString("Do you want to remove the operation '" + conditionName + "'?"), this);
    if(reply == QMessageBox::No){
        return;
    }

    auto *conditionTypeLabel = dynamic_cast<QLabel*>(this->ui->conditionsTableWidget->cellWidget(this->ui->conditionsTableWidget->currentRow(), 1));
    auto conditionType = conditionTypeLabel->text().toStdString();

    if(conditionType == "Pre"){
        metaOperation->removePreCondition(conditionName);
    }else{
        metaOperation->removePostCondition(conditionName);
    }
    this->loadConditions(metaOperation->getPreConditions());
    this->loadConditions(metaOperation->getPostConditions());
}

void OperationEditDialog::variableCellDoubleClicked(int row, int column){
    QLabel * item = dynamic_cast<QLabel*>(ui->variablesTableWidget->cellWidget(row, 0));

    auto variable = metaOperation->getVariable(item->text().toStdString());

    VariableEditDialog* variableEditDialog = new VariableEditDialog(variable);
    int returnCode = variableEditDialog->exec();

    if(returnCode == 1) {
        loadVariables();
    }
}

void OperationEditDialog::addNewVariable(){
    auto newVariable = std::make_shared<MetaModel::MetaVariable>("newVariable"+ std::to_string(variablesCont), MetaModel::Integer::instance());

    VariableEditDialog* variableEditDialog = new VariableEditDialog(newVariable);
    int returnCode = variableEditDialog->exec();

    if(returnCode == 1) {
        metaOperation->addVariable(newVariable);
        loadVariables();
    }
}

void OperationEditDialog::removeVariable(){
    if(ui->variablesTableWidget->currentRow() == -1){
        return;
    }

    auto *variableLabel = dynamic_cast<QLabel*>(this->ui->variablesTableWidget->cellWidget(this->ui->variablesTableWidget->currentRow(), 0));
    auto variableName = variableLabel->text().toStdString();

    auto reply = showQuestionMessageBox("Remove operation", QString::fromStdString("Do you want to remove the variable '" + variableName + "'?"), this);
    if(reply == QMessageBox::No){
        return;
    }

    this->metaOperation->removeVariable(variableName);
    this->loadVariables();
}

void OperationEditDialog::saveReturnType(QString type){
    if (type == "Integer"){
        metaOperation->setReturnType(MetaModel::Integer::instance());
    }else if(type == "Real"){
        metaOperation->setReturnType(MetaModel::Real::instance());
    }else if(type == "String"){
        metaOperation->setReturnType(MetaModel::String::instance());
    }else{
        metaOperation->setReturnType(MetaModel::Boolean::instance());
    }
}

void OperationEditDialog::saveVisibility(){
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

    metaOperation->setVisibility(vis);
}

void OperationEditDialog::saveChanges(){
    metaOperation->setName(ui->operationNamelineEdit->text().toStdString());

    saveVisibility();
    saveReturnType(ui->returnTypeComboBox->currentText());
}

void OperationEditDialog::cancelChanges(){
    auto reply = showQuestionMessageBox("Edit Operation", "Changes have not been saved. Do you want to cancel?", this);

    if(reply == QMessageBox::No){
        return;
    }

    reject();
}
