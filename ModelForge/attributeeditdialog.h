#ifndef ATTRIBUTEEDITDIALOG_H
#define ATTRIBUTEEDITDIALOG_H

#include "metamodel/MetaAttribute.h"
#include <QDialog>


namespace Ui {
class AttributeEditDialog;
}

class AttributeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AttributeEditDialog(std::shared_ptr<MetaModel::MetaAttribute> metaAttribute, QWidget *parent = nullptr);
    ~AttributeEditDialog();

private:
    Ui::AttributeEditDialog *ui;
    std::shared_ptr<MetaModel::MetaAttribute> metaAttribute;
};

#endif // ATTRIBUTEEDITDIALOG_H
