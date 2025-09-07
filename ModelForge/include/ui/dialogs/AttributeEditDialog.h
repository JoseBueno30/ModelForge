#ifndef ATTRIBUTEEDITDIALOG_H
#define ATTRIBUTEEDITDIALOG_H

#include "metamodel/MetaAttribute.h"
#include "metamodel/MetaClass.h"
#include <QDialog>
#include <metamodel/MetaModel.h>


namespace Ui {
class AttributeEditDialog;
}

class AttributeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AttributeEditDialog(std::shared_ptr<MetaModel::MetaAttribute> metaAttribute, std::shared_ptr<MetaModel::MetaClass> metaClass,  std::shared_ptr<MetaModel::MetaModel> metaModel, QWidget *parent = nullptr);
    ~AttributeEditDialog();

private Q_SLOTS:
    void saveChanges();
    void cancelChanges();

private:
    bool isValidAttribute();

    std::shared_ptr<MetaModel::MetaType> getTypeFromComboBox(QString type);

    void loadVisibility();
    void saveVisibility();

    Ui::AttributeEditDialog *ui;
    std::shared_ptr<MetaModel::MetaAttribute> metaAttribute;
    std::shared_ptr<MetaModel::MetaClass> metaClass;
    std::shared_ptr<MetaModel::MetaModel> metaModel;
};

#endif // ATTRIBUTEEDITDIALOG_H
