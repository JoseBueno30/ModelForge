#ifndef OPERATIONEDITDIALOG_H
#define OPERATIONEDITDIALOG_H

#include "metamodel/MetaOperation.h"
#include <QDialog>

namespace Ui{
class OperationEditDialog;
}

class OperationEditDialog : public QDialog{
    Q_OBJECT

public:
    OperationEditDialog(std::shared_ptr<MetaModel::MetaOperation> metaOperation, QWidget* parent = nullptr);


private Q_SLOTS:
    void saveChanges();

    void loadReturnType();
    void loadVisibility();
    void loadVariables();
    void loadConditions(std::map<std::string, std::shared_ptr<MetaModel::PrePostClause>> conditions);

    void conditionCellDoubleClicked(int row, int column);
    void addNewCondition();

    void variableCellDoubleClicked(int row, int column);
    void addNewVariable();

    void saveReturnType(QString type);
    void saveVisibility();

private:
    Ui::OperationEditDialog* ui;
    std::shared_ptr<MetaModel::MetaOperation> metaOperation;

    int variablesCont = 0, conditionsCont = 0;
};

#endif // OPERATIONEDITDIALOG_H
