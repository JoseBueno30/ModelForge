#include <ui/dialogs/ConditionEditDialog.h>
#include <ui/dialogs/OperationEditDialog.h>
#include <src/ui/dialogs/ui_OperationEditDialog.h>

OperationEditDialog::OperationEditDialog(std::shared_ptr<MetaModel::MetaOperation> metaOperation, QWidget* parent) : metaOperation(metaOperation), QDialog(parent), ui(new Ui::OperationEditDialog)
{
    ui->setupUi(this);
    ui->operationNamelineEdit->setText(QString::fromStdString(metaOperation->getName()));

    loadReturnType();
    loadVisibility();
    loadConditions(metaOperation->getPreConditions());
    loadConditions(metaOperation->getPostConditions());

    variablesCont = metaOperation->getVariables().size();
    conditionsCont = metaOperation->getPostConditions().size() + metaOperation->getPreConditions().size();

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &OperationEditDialog::saveChanges);
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
        ui->variablesTableWidget->setCellWidget(row, 0, nameLabel);

        QLabel *typeLabel = new QLabel(QString::fromStdString(variablePair.second->getType().toString()));
        ui->variablesTableWidget->setCellWidget(row, 1, typeLabel);

        row++;
    }
}

void OperationEditDialog::loadConditions(std::map<std::string, std::shared_ptr<MetaModel::PrePostClause>> conditions){
    ui->conditionsTableWidget->setRowCount(0);
    int row = 0;

    for(auto conditionPair : conditions){
        ui->conditionsTableWidget->insertRow(row);

        QLabel *nameLabel = new QLabel(QString::fromStdString(conditionPair.first));
        ui->conditionsTableWidget->setCellWidget(row, 0, nameLabel);

        QLabel *typeLabel = new QLabel(conditionPair.second->getIsPost() ? "Post" : "Pre");
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
       // condition = metaOperation->getPreCondition(item->text().toStdString());
    }else{
        // condition = metaOperation->getPostCondition(item->text().toStdString());
    }
    ConditionEditDialog* conditionEditDialog = new ConditionEditDialog(condition);

    int returnCode = conditionEditDialog->exec();
    if(returnCode == 1){
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

void OperationEditDialog::variableCellDoubleClicked(int row, int column){
    QLabel * item = dynamic_cast<QLabel*>(ui->variablesTableWidget->cellWidget(row, 0));

    auto variable = metaOperation->getVariable(item->text().toStdString());

    //TODO
}

void OperationEditDialog::addNewVariable(){

    auto newVariable = std::make_shared<MetaModel::MetaVariable>("newVariable"+ std::to_string(variablesCont), MetaModel::Integer::instance());

    //TODO
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
