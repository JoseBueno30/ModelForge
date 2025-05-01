#include <ui/dialogs/AssociationEditDialog.h>

#include <src/ui/dialogs/ui_AssociationEditDialog.h>

AssociationEditDialog::AssociationEditDialog(
    std::shared_ptr<MetaModel::MetaAssociation> associationModel,
    std::map<std::string, QGraphicsItem*> itemViewsMap,
    QGraphicsScene* scene,
    std::shared_ptr<MetaModel::MetaModel> model
    )
    :
    associationModel(associationModel), itemViewsMap(itemViewsMap), scene(scene), model(model),
    ui(new Ui::AssociationEditDialog)
{
    ui->setupUi(this);
    setupTypesComboBox();

    ui->associationNameEdit->setText(QString::fromStdString(associationModel->getName()));

    //set ui type
    ui->associationTypeComboBox->setCurrentIndex(associationModel->getType());

    //set Association end if not null


    if(!associationModel->getAssociationEnds().empty()){

    }
}

void AssociationEditDialog::setupAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    ui->roleAEnd1LineEdit->setText(QString::fromStdString(associationEnd->getRole()));

    ui->multiplicityAEnd1LineEdit->setText(
        QString::fromStdString(associationEnd->getMultiplicity().toString())
    );
    int typeIndex = ui->typeAEnd1ComboBox->findText(
        QString::fromStdString(associationEnd->getClass().getName())
    );
    ui->typeAEnd1ComboBox->setCurrentIndex(typeIndex);
}

void AssociationEditDialog::setupAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    ui->roleAEnd2LineEdit->setText(QString::fromStdString(associationEnd->getRole()));

    ui->multiplicityAEnd2LineEdit->setText(
        QString::fromStdString(associationEnd->getMultiplicity().toString())
        );
    int typeIndex = ui->typeAEnd2ComboBox->findText(
        QString::fromStdString(associationEnd->getClass().getName())
        );
    ui->typeAEnd2ComboBox->setCurrentIndex(typeIndex);
}


void AssociationEditDialog::setupTypesComboBox(){

     ui->associationTypeComboBox->addItems({"Association", "Aggregation", "Composition"});

    for(auto metaClassPair : model->getClasses()){
        ui->typeAEnd1ComboBox->addItem(
            QString::fromStdString(metaClassPair.second->getName())
        );

        ui->typeAEnd2ComboBox->addItem(
            QString::fromStdString(metaClassPair.second->getName())
        );
    }

    for(auto metaAssocClassPair : model->getAssociationClasses()){
        ui->typeAEnd1ComboBox->addItem(
            QString::fromStdString(metaAssocClassPair.second->getName())
            );

        ui->typeAEnd2ComboBox->addItem(
            QString::fromStdString(metaAssocClassPair.second->getName())
            );
    }
}
