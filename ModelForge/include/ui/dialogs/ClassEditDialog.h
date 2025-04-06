#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>
#include <QGraphicsScene>

#include <metamodel/MetaClass.h>
#include <metamodel/MetaModel.h>

namespace Ui {
class ClassEditDialog;
}

class ClassEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassEditDialog(std::shared_ptr<MetaModel::MetaClass> metaClass, QGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model = nullptr, QWidget *parent = nullptr);
    ~ClassEditDialog();

private Q_SLOTS:
    void addAttribute();
    void removeAttribute();
    void saveChanges();
    void cellDoubleClicked(int row, int column);

private:
    Ui::ClassEditDialog *ui;

    std::shared_ptr<MetaModel::MetaModel> model;
    std::shared_ptr<MetaModel::MetaClass> metaClass;
    std::shared_ptr<MetaModel::MetaClass> editedClass;
    QGraphicsScene* scene;

    int attributeCounter;

    void loadAttributes();
};

#endif // CLASSEDITDIALOG_H
