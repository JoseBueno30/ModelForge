#ifndef VARIABLEEDITDIALOG_H
#define VARIABLEEDITDIALOG_H

#include <QDialog>

#include <metamodel/MetaModel.h>
#include <metamodel/MetaOperation.h>
#include <metamodel/MetaVariable.h>


namespace Ui{
class VariableEditDialog;
}

class VariableEditDialog : public QDialog{
    Q_OBJECT
public:
    VariableEditDialog(std::shared_ptr<MetaModel::MetaVariable> metaVariable, std::shared_ptr<MetaModel::MetaOperation> metaOperation,  std::shared_ptr<MetaModel::MetaModel> metaModel, QWidget* parent=nullptr);

private Q_SLOTS:
    void saveChanges();
    void cancelChanges();

private:
    Ui::VariableEditDialog* ui;
    std::shared_ptr<MetaModel::MetaVariable> metaVariable;
    std::shared_ptr<MetaModel::MetaOperation> metaOperation;
    std::shared_ptr<MetaModel::MetaModel> metaModel;

    void loadComboBoxTypes();
    std::shared_ptr<MetaModel::MetaType> getTypeFromComboBox(QString type);

    bool isValidVariable();
};

#endif // VARIABLEEDITDIALOG_H
