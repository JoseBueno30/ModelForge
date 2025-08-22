#ifndef ASSOCIATIONEDITDIALOG_H
#define ASSOCIATIONEDITDIALOG_H

#include "metamodel/MetaAssociation.h"
#include <QDialog>
#include <metamodel/MetaModel.h>
#include <any>
#include <ui/components/ModelGraphicsScene.h>
#include <qgraphicsitem.h>
#include <ui/view/AssociationItemView.h>

namespace Ui{
class AssociationEditDialog;
}

class AssociationEditDialog : public QDialog{
    Q_OBJECT

public:
    explicit AssociationEditDialog(
        std::shared_ptr<MetaModel::MetaAssociation> associationModel,
        ModelGraphicsScene* scene,
        AssociationItemView * associationItemView = nullptr,
        std::shared_ptr<MetaModel::MetaModel> model = nullptr
        );

public Q_SLOTS:
    void saveChanges();
    void cancelChanges();

private:
    Ui::AssociationEditDialog *ui;

    std::shared_ptr<MetaModel::MetaAssociation> associationModel;
    ModelGraphicsScene* scene;
    AssociationItemView * associationItemView;
    std::shared_ptr<MetaModel::MetaModel> model;

    void setupUiInfo();
    void setupTypesComboBox();

    void loadVisibilityAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);
    void loadVisibilityAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);

    void setupAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);
    void setupAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);

    MetaModel::Visibility getVisibilityAssociationEnd1();
    MetaModel::Visibility getVisibilityAssociationEnd2();

    void setAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);
    void setAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd);

    bool isValidAssociation();
};

#endif // ASSOCIATIONEDITDIALOG_H
