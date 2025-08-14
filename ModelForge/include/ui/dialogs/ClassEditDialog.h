#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>
#include <ui/components/ModelGraphicsScene.h>

#include <metamodel/MetaClass.h>
#include <metamodel/MetaModel.h>

#include <ui/view/ClassItemView.h>

namespace Ui {
class ClassEditDialog;
}

class ClassEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassEditDialog(std::shared_ptr<MetaModel::MetaClass> metaClass, ModelGraphicsScene* scene, ClassItemView* classView = nullptr, std::shared_ptr<MetaModel::MetaModel> model = nullptr, QWidget *parent = nullptr);
    ~ClassEditDialog();

private Q_SLOTS:
    void addAttribute();
    void removeAttribute();
    void attributeCellDoubleClicked(int row, int column);

    void saveChanges();
    void cancelChanges();

    void addOperation();
    void removeOperation();
    void operationCellDoubleClicked(int row, int column);

private:
    Ui::ClassEditDialog *ui;
    ClassItemView* classView;

    std::shared_ptr<MetaModel::MetaModel> model;
    std::shared_ptr<MetaModel::MetaClass> metaClass;
    std::shared_ptr<MetaModel::MetaClass> editedClass;
    ModelGraphicsScene* scene;

    int attributeCounter;
    int operationCounter;

    void loadAttributes();
    void loadOperations();

    bool isValidClass();
};

#endif // CLASSEDITDIALOG_H
