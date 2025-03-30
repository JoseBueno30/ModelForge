#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>

#include <metamodel/MetaClass.h>

namespace Ui {
class ClassEditDialog;
}

class ClassEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassEditDialog(QWidget *parent = nullptr, std::shared_ptr<MetaModel::MetaClass> metaClass = nullptr);
    ~ClassEditDialog();

private Q_SLOTS:
    void addAttribute();
    void removeAttribute();
    void saveChanges();
    void cellDoubleClicked(int row, int column);

private:
    Ui::ClassEditDialog *ui;
    std::shared_ptr<MetaModel::MetaClass> metaClass;

    int attributeCounter = 1;

    void loadAttributes();
};

#endif // CLASSEDITDIALOG_H
