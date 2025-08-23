#include "ui/dialogs/AddGeneraliaztionDialog.h"

#include <src/ui/dialogs/ui_AddGeneralizationDialog.h>

#include <utils/Commands.h>

#include <ui/dialogs/MainWindow.h>

#include <QPushButton>

AddGeneralizationDialog::AddGeneralizationDialog(std::shared_ptr<MetaModel::MetaModel> metaModel, ModelGraphicsScene* scene, QWidget* parent)
    : metaModel(metaModel), scene(scene), ui(new Ui::AddGeneralizationDialog()), QDialog(parent){

    ui->setupUi(this);

    setupComboBox(ui->childClassComboBox);
    setupComboBox(ui->superClassComboBox);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &AddGeneralizationDialog::saveChanges);
}

void AddGeneralizationDialog::setupComboBox(QComboBox* comboBox){
    for(auto classPair : metaModel->getClasses()){
        comboBox->addItem(QString::fromStdString(classPair.second->getName()));
    }
}

void AddGeneralizationDialog::saveChanges(){
    std::shared_ptr<MetaModel::MetaClass> childClass = metaModel->getClass(ui->childClassComboBox->currentText().toStdString());
    std::shared_ptr<MetaModel::MetaClass> superClass = metaModel->getClass(ui->superClassComboBox->currentText().toStdString());

    AddMetaGeneralizationCommand* addCommand = new AddMetaGeneralizationCommand(childClass, superClass, scene);
    MainWindow::undoStack->push(addCommand);

    accept();
}
