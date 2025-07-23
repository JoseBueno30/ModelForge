#ifndef ENUMEDITDIALOG_H
#define ENUMEDITDIALOG_H

#include "metamodel/MetaEnum.h"
#include "ui/view/EnumItemView.h"
#include <QDialog>
#include <ui/components/ModelGraphicsScene.h>
#include <metamodel/MetaModel.h>

namespace Ui{
class EnumEditDialog;
}

class EnumEditDialog : public QDialog{
    Q_OBJECT
public:
    EnumEditDialog(std::shared_ptr<MetaModel::MetaEnum> metaEnum, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model=nullptr, EnumItemView* itemView=nullptr, QWidget* parent=nullptr);

public Q_SLOTS:
    void saveChanges();
    void addElement();
    void deleteElement();

private:
    Ui::EnumEditDialog *ui;
    std::shared_ptr<MetaModel::MetaEnum> metaEnum;
    std::shared_ptr<MetaModel::MetaModel> model;
    EnumItemView * itemView;
    ModelGraphicsScene* scene;

    void loadElements();
    void setMetaEnum(std::shared_ptr<MetaModel::MetaEnum> metaEnumPointer);
};

#endif // ENUMEDITDIALOG_H
