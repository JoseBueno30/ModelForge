#ifndef OPERATIONEDITDIALOG_H
#define OPERATIONEDITDIALOG_H

#include "metamodel/MetaOperation.h"
#include <QDialog>
#include <metamodel/MetaClass.h>

namespace Ui{
class OperationEditDialog;
}

class OperationEditDialog : public QDialog{
    Q_OBJECT

public:
    OperationEditDialog(std::shared_ptr<MetaModel::MetaOperation> metaOperation, std::shared_ptr<MetaModel::MetaClass> metaClass, bool isNew, QWidget* parent = nullptr);


private Q_SLOTS:
    void saveChanges();
    void cancelChanges();

    void loadReturnType();
    void loadVisibility();
    void loadVariables();
    void loadConditions(std::map<std::string, std::shared_ptr<MetaModel::PrePostClause>> conditions);

    void conditionCellDoubleClicked(int row, int column);
    void addNewCondition();
    void removeCondition();

    void variableCellDoubleClicked(int row, int column);
    void addNewVariable();
    void removeVariable();

    void saveReturnType(QString type);
    void saveVisibility();

private:
    Ui::OperationEditDialog* ui;
    std::shared_ptr<MetaModel::MetaOperation> metaOperation;
    std::shared_ptr<MetaModel::MetaClass> metaClass;

    int variablesCont = 0, conditionsCont = 0;
    bool isNew;

    bool isValidOperation();
};

#endif // OPERATIONEDITDIALOG_H
