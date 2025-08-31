#ifndef CONSTRAINTEDITDIALOG_H
#define CONSTRAINTEDITDIALOG_H

#include <QDialog>

#include <metamodel/MetaConstraint.h>


namespace Ui{
class ConstraintEditDialog;
}

class ConstraintEditDialog : public QDialog{
public:
    ConstraintEditDialog(std::shared_ptr<MetaModel::MetaConstraint> metaConstraint, std::shared_ptr<MetaModel::MetaClass> metaClass, QWidget* parent = nullptr);

public Q_SLOTS:
    void saveChanges();
    void cancelChanges();

private:
    std::shared_ptr<MetaModel::MetaConstraint> metaConstraint;
    std::shared_ptr<MetaModel::MetaClass> metaClass;
    Ui::ConstraintEditDialog* ui;

    bool isValidConstraint();
};

#endif // CONSTRAINTEDITDIALOG_H
