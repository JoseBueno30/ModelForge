#ifndef ENUMEDITDIALOG_H
#define ENUMEDITDIALOG_H

#include "metamodel/MetaEnum.h"
#include <QDialog>
#include <QGraphicsScene>
#include <metamodel/MetaModel.h>

namespace Ui{
class EnumEditDialog;
}

class EnumEditDialog : public QDialog{
    Q_OBJECT
public:
    EnumEditDialog(std::shared_ptr<MetaModel::MetaEnum> metaEnum, QGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model=nullptr, QWidget* parent=nullptr);

private:
    Ui::EnumEditDialog *ui;

    std::shared_ptr<MetaModel::MetaEnum> metaEnum;
    std::shared_ptr<MetaModel::MetaModel> model;
    QGraphicsScene* scene;

    void loadElements();
};

#endif // ENUMEDITDIALOG_H
