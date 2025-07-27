#include <ui/dialogs/AttributeEditDialog.h>

#include <QPushButton>

#include <src/ui/dialogs/ui_AttributeEditDialog.h>
#include <metamodel/MetaType.h>

AttributeEditDialog::AttributeEditDialog(std::shared_ptr<MetaModel::MetaAttribute> metaAttribute, bool isEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditDialog),
    metaAttribute(metaAttribute),
    isEdit(isEdit)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &AttributeEditDialog::saveChanges);

    ui->nameLineEdit->setText(QString::fromStdString(metaAttribute->getName()));
    ui->typeComboBox->addItems({"Integer", "Real", "String", "Boolean"});
    ui->typeComboBox->setCurrentText(QString::fromStdString(metaAttribute->getType().toString()));
}

AttributeEditDialog::~AttributeEditDialog()
{
    delete ui;
}

std::shared_ptr<MetaModel::MetaType> getTypefromComboBox(QString type){
    if (type == "Integer"){
        return MetaModel::Integer::instance();
    }else if(type == "Real"){
        return MetaModel::Real::instance();
    }else if(type == "String"){
        return MetaModel::String::instance();
    }else{
        return MetaModel::Boolean::instance();
    }
}

void AttributeEditDialog::saveChanges(){

    metaAttribute->setName(ui->nameLineEdit->text().toStdString());
    metaAttribute->setType(getTypefromComboBox(ui->typeComboBox->currentText()));

    std::shared_ptr<MetaModel::Expr> derivedExpr = std::make_shared<MetaModel::Expr>(ui->derivedExprTextEdit->toPlainText().toStdString());
    metaAttribute->setDeriveExpr(derivedExpr);

    std::shared_ptr<MetaModel::Expr> initExpr = std::make_shared<MetaModel::Expr>(ui->initExprTextEdit->toPlainText().toStdString());
    metaAttribute->setInitExpr(initExpr);

    accept();
}
