#include "utils/MessageBox.h"
#include <include/ui/dialogs/ConstraintEditDialog.h>
#include <metamodel/MetaClass.h>
#include <ui/components/ConsoleHandler.h>

#include <src/ui/dialogs/ui_ConstraintEditDialog.h>

#include <QPushButton>

ConstraintEditDialog::ConstraintEditDialog(std::shared_ptr<MetaModel::MetaConstraint> metaConstraint, std::shared_ptr<MetaModel::MetaClass> metaClass, QWidget* parent)
    : metaConstraint(metaConstraint), metaClass(metaClass), QDialog(parent), ui(new Ui::ConstraintEditDialog()){

    ui->setupUi(this);

    ui->nameLineEdit->setText(QString::fromStdString(metaConstraint->getName()));
    ui->expressionTextEdit->setText(QString::fromStdString(metaConstraint->getExpression().getExpression()));
    ui->isExistentialCheckBox->setChecked(metaConstraint->getIsExistential());

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &ConstraintEditDialog::saveChanges);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &ConstraintEditDialog::cancelChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
}

bool ConstraintEditDialog::isValidConstraint(){
    bool isValid = true;
    if(metaClass->getConstraint(ui->nameLineEdit->text().toStdString())){
        ConsoleHandler::appendErrorLog("Class '" + QString::fromStdString(metaClass->getName()) + "' already have a constraint named '"
                                       + QString::fromStdString(metaConstraint->getName()) +"'.");
        isValid = false;
    }

    // CHECK EXpression with parser.
    return isValid;
}

void ConstraintEditDialog::saveChanges(){
    if(!isValidConstraint()){
        showExceptionMessageBox("Error", "There was an unexpected error saving the constraint. Please check the console for more information.");
        return;
    }

    metaConstraint->setName(ui->nameLineEdit->text().toStdString());
    metaConstraint->setIsExistential(ui->isExistentialCheckBox->isChecked());

    auto metaType = metaConstraint->getExpression().getType() ? metaConstraint->getExpression().getType() : MetaModel::Void::instance();

    std::shared_ptr<MetaModel::Expr> expr = std::make_shared<MetaModel::Expr>(ui->expressionTextEdit->toPlainText().toStdString(), true, metaType);
    metaConstraint->setExpression(expr);

    accept();
}

void ConstraintEditDialog::cancelChanges(){
    auto reply = showQuestionMessageBox("Edit Constraint", "Changes have not been saved. Do you want to cancel?", this);

    if(reply == QMessageBox::No){
        return;
    }

    reject();
}
