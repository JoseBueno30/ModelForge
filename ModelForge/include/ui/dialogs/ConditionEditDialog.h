#ifndef CONDITIONEDITDIALOG_H
#define CONDITIONEDITDIALOG_H

#include "metamodel/MetaOperation.h"
#include <QDialog>

namespace Ui{
class ConditionEditDialog;
}

class ConditionEditDialog : public QDialog{
    Q_OBJECT

public:
    ConditionEditDialog(std::shared_ptr<MetaModel::PrePostClause> condition, std::shared_ptr<MetaModel::MetaOperation> metaOperation, QWidget* parent=nullptr);

private Q_SLOTS:
    void saveChanges();
    void cancelChanges();

private:
    Ui::ConditionEditDialog* ui;

    std::shared_ptr<MetaModel::PrePostClause> condition;
    std::shared_ptr<MetaModel::MetaOperation> metaOperation;

    bool isValidCondition();
};

#endif // CONDITIONEDITDIALOG_H
