#ifndef ADDGENERALIAZTIONDIALOG_H
#define ADDGENERALIAZTIONDIALOG_H

#include <metamodel/MetaModel.h>

#include <QDialog>
#include <qcombobox.h>
#include <ui/components/ModelGraphicsScene.h>


namespace Ui{
class AddGeneralizationDialog;
}

class AddGeneralizationDialog : public QDialog{
public:
    AddGeneralizationDialog(std::shared_ptr<MetaModel::MetaModel> metaModel, ModelGraphicsScene* scene, QWidget* parent = nullptr);

private Q_SLOTS:
    void saveChanges();

private:
    Ui::AddGeneralizationDialog* ui;
    std::shared_ptr<MetaModel::MetaModel> metaModel;
    ModelGraphicsScene* scene;

    void setupComboBox(QComboBox* combobox);
};

#endif // ADDGENERALIAZTIONDIALOG_H
