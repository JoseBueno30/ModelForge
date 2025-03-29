#include "attributeeditdialog.h"
#include "ui_attributeeditdialog.h"

AttributeEditDialog::AttributeEditDialog(std::shared_ptr<MetaModel::MetaAttribute> metaAttribute, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditDialog),
    metaAttribute(metaAttribute)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(QString::fromStdString(metaAttribute->getName()));
}

AttributeEditDialog::~AttributeEditDialog()
{
    delete ui;
}
