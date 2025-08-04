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
    ConditionEditDialog(std::shared_ptr<MetaModel::PrePostClause> condition);

private Q_SLOTS:
    void saveChanges();

private:
    Ui::ConditionEditDialog* ui;

    std::shared_ptr<MetaModel::PrePostClause> condition;
};

#endif // CONDITIONEDITDIALOG_H
