#ifndef ASSOCIATIONEDITDIALOG_H
#define ASSOCIATIONEDITDIALOG_H

#include "metamodel/MetaAssociation.h"
#include <QDialog>
#include <metamodel/MetaModel.h>
#include <any>
#include <qgraphicsitem.h>

namespace Ui{
class AssociationEditDialog;
}

class AssociationEditDialog : public QDialog{
    Q_OBJECT

public:
    explicit AssociationEditDialog(
        std::shared_ptr<MetaModel::MetaAssociation> associationModel,
        std::map<std::string, QGraphicsItem*> itemViewsMap,
        QGraphicsScene* scene,
        std::shared_ptr<MetaModel::MetaModel> model = nullptr
        );

private:
    Ui::AssociationEditDialog *ui;

    std::shared_ptr<MetaModel::MetaAssociation> associationModel;
    std::map<std::string, QGraphicsItem*> itemViewsMap;
    QGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaModel> model;

    void setupTypesComboBox();

    void setupAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);
    void setupAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);
};

#endif // ASSOCIATIONEDITDIALOG_H
