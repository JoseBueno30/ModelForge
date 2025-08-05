#include "utils/MessageBox.h"
#include <ui/dialogs/ConditionEditDialog.h>
#include <src/ui/dialogs/ui_ConditionEditDialog.h>
#include <QPushButton>

ConditionEditDialog::ConditionEditDialog(std::shared_ptr<MetaModel::PrePostClause> condition) : condition(condition){
    ui = new Ui::ConditionEditDialog();
    ui->setupUi(this);

    ui->nameLineEdit->setText(QString::fromStdString(condition->getName()));

    if(condition->getIsPre()){
        ui->typeComboBox->setCurrentIndex(0);
    }else{
        ui->typeComboBox->setCurrentIndex(1);
    }

    ui->expressionTextEdit->setText(QString::fromStdString(condition->getExpression().getExpression()));

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &ConditionEditDialog::saveChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &ConditionEditDialog::cancelChanges);

}

void ConditionEditDialog::saveChanges(){
    condition->setName(ui->nameLineEdit->text().toStdString());

    if(ui->typeComboBox->currentIndex() == 0){
        qDebug() << "indice 0";
        condition->setIsPost(false);
        condition->setIsPre(true);
    }else{
        qDebug() << "indice 1";
        condition->setIsPost(true);
        condition->setIsPre(false);
    }

    condition->setExpression(std::make_shared<MetaModel::Expr>(ui->expressionTextEdit->toPlainText().toStdString()));

    accept();
}

void ConditionEditDialog::cancelChanges(){
    auto reply = showQuestionMessageBox("Edit class", "Changes have not been saved. Do you want to cancel?", this);

    if(reply == QMessageBox::No){
        return;
    }

    reject();
}
