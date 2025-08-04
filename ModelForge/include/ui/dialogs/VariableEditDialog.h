#ifndef VARIABLEEDITDIALOG_H
#define VARIABLEEDITDIALOG_H

#include <QDialog>

#include <metamodel/MetaVariable.h>


namespace Ui{
class VariableEditDialog;
}

class VariableEditDialog : public QDialog{
    Q_OBJECT
public:
    VariableEditDialog(std::shared_ptr<MetaModel::MetaVariable> metaVariable, QWidget* parent=nullptr);

private Q_SLOTS:
    void saveChanges();

private:
    Ui::VariableEditDialog* ui;
    std::shared_ptr<MetaModel::MetaVariable> metaVariable;

    void loadComboBoxTypes();
    std::shared_ptr<MetaModel::MetaType> getTypeFromComboBox();


};

#endif // VARIABLEEDITDIALOG_H
