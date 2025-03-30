#include "attributeeditdialog.h"
#include "ui_attributeeditdialog.h"

#include <QPushButton>

AttributeEditDialog::AttributeEditDialog(std::shared_ptr<MetaModel::MetaAttribute> metaAttribute, bool isEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditDialog),
    metaAttribute(metaAttribute),
    isEdit(isEdit)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &AttributeEditDialog::saveChanges);

    ui->nameLineEdit->setText(QString::fromStdString(metaAttribute->getName()));
}

AttributeEditDialog::~AttributeEditDialog()
{
    delete ui;
}

std::shared_ptr<MetaModel::MetaType> getTypefromComboBox(QString type){
    //TODO - Pasar mapa con los tipos?
    return nullptr;
}

void AttributeEditDialog::saveChanges(){
    //TODO - crear accion y añadir a la cola

    /*
    metaAttribute->setName(ui->nameLineEdit->text().toStdString());
    metaAttribute->setType(getTypefromComboBox(ui->typeComboBox->currentText()));

    std::shared_ptr<MetaModel::OCLExpr> derivedExpr = std::make_shared<MetaModel::OCLExpr>(ui->derivedExprTextEdit->toPlainText());
    metaAttribute->setDeriveExpr(derivedExpr);

    std::shared_ptr<MetaModel::OCLExpr> initExpr = std::make_shared<MetaModel::OCLExpr>(ui->initExprTextEdit->toPlainText());
    metaAttribute->setInitExpr(initExpr);*/
    accept();
}
