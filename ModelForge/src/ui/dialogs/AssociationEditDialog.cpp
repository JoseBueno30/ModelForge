#include <ui/dialogs/AssociationEditDialog.h>

#include <src/ui/dialogs/ui_AssociationEditDialog.h>

#include <QPushButton>

#include <ui/view/AssociationItemView.h>

#include <utils/Commands.h>

#include <ui/dialogs/MainWindow.h>

AssociationEditDialog::AssociationEditDialog(
    std::shared_ptr<MetaModel::MetaAssociation> associationModel,
    std::map<std::string, QGraphicsItem*> itemViewsMap,
    QGraphicsScene* scene,
    AssociationItemView * associationItemView,
    std::shared_ptr<MetaModel::MetaModel> model
    )
    :
    associationModel(associationModel), itemViewsMap(itemViewsMap), scene(scene), model(model),
    associationItemView(associationItemView), ui(new Ui::AssociationEditDialog)
{
    ui->setupUi(this);
    setupTypesComboBox();

    ui->associationNameEdit->setText(QString::fromStdString(associationModel->getName()));

    //set ui type
    ui->associationTypeComboBox->setCurrentIndex(associationModel->getType());

    //set Association end if not null
    if(!associationModel->getAssociationEnds().empty()){
        auto aEndIterator = associationModel->getAssociationEnds().begin();

        setupAssociationEnd1(aEndIterator->second);
        ui->multiplicityAEnd1LineEdit->setText(
            QString::fromStdString(aEndIterator->second->getMultiplicity().toString())
        );
        ui->roleAEnd1LineEdit->setText(QString::fromStdString(aEndIterator->second->getRole()));

        aEndIterator++;
        setupAssociationEnd2(aEndIterator->second);
        ui->multiplicityAEnd2LineEdit->setText(
            QString::fromStdString(aEndIterator->second->getMultiplicity().toString())
        );
        ui->roleAEnd2LineEdit->setText(QString::fromStdString(aEndIterator->second->getRole()));
    }

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &AssociationEditDialog::saveChanges);
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

void AssociationEditDialog::saveChanges(){


    if(associationModel->getAssociationEnds().empty()){ //Creating new association
        //Check if fields have been completed and create associationEnds
        if(true){

            associationModel->setName(ui->associationNameEdit->text().toStdString());

            associationModel->setType(ui->associationTypeComboBox->currentIndex());

            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd1 = std::make_shared<MetaModel::MetaAssociationEnd>(associationModel, 0);
            associationEnd1->setMultiplicity(std::make_shared<MetaModel::MetaMultiplicity>(0,0));
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd2 = std::make_shared<MetaModel::MetaAssociationEnd>(associationModel, ui->associationTypeComboBox->currentIndex());
            associationEnd2->setMultiplicity(std::make_shared<MetaModel::MetaMultiplicity>(0,0));


            qDebug()<< "a";
            setAssociationEnd1(associationEnd1);
            setAssociationEnd2(associationEnd2);

            qDebug()<< "b";
            associationModel->addAssociationEnd(associationEnd1);
            associationModel->addAssociationEnd(associationEnd2);

            qDebug()<< "c";
            ClassItemView* class1 = dynamic_cast<ClassItemView*>(itemViewsMap.find(ui->typeAEnd1ComboBox->currentText().toStdString())->second);
            ClassItemView* class2 = dynamic_cast<ClassItemView*>(itemViewsMap.find(ui->typeAEnd2ComboBox->currentText().toStdString())->second);

            qDebug()<< "d";
            AssociationItemView * newAssociation = new AssociationItemView(associationModel, class1, class2);
            qDebug()<< "e";
            AddMetaAssociationCommand* addCommand = new AddMetaAssociationCommand(associationModel, model, newAssociation, scene);
            MainWindow::undoStack->push(addCommand);
        }
    }
    else{ //Updating an existing association

        // Check if fields have been changed and update existing associationEnds
        if(true){
            std::shared_ptr<MetaModel::MetaAssociation> newAssociation = std::make_shared<MetaModel::MetaAssociation>(*this->associationModel);

            newAssociation->setName(ui->associationNameEdit->text().toStdString());

            newAssociation->setType(ui->associationTypeComboBox->currentIndex());

            auto aEndsIt = newAssociation->getAssociationEnds().begin();
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd1 = aEndsIt->second;
            aEndsIt++;
            std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd2 = aEndsIt->second;

            setAssociationEnd1(associationEnd1);
            setAssociationEnd2(associationEnd2);

            EditMetaAssociationCommand *editCommand = new EditMetaAssociationCommand(this->associationModel, newAssociation, this->associationItemView, this->itemViewsMap, this->scene);
            MainWindow::undoStack->push(editCommand);
        }
    }


}

void AssociationEditDialog::setAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    associationEnd->setRole(ui->roleAEnd1LineEdit->text().toStdString());

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0,0);
    multiplicity->setMultiplicictyFromString(ui->multiplicityAEnd1LineEdit->text().toStdString());
    associationEnd->setMultiplicity(multiplicity);

    auto newClass = this->model->getClass(ui->typeAEnd1ComboBox->currentText().toStdString());
    associationEnd->setClass(newClass);
}

void AssociationEditDialog::setAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    associationEnd->setRole(ui->roleAEnd2LineEdit->text().toStdString());

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0,0);
    multiplicity->setMultiplicictyFromString(ui->multiplicityAEnd2LineEdit->text().toStdString());

    associationEnd->setMultiplicity(multiplicity);

    auto newClass = this->model->getClass(ui->typeAEnd2ComboBox->currentText().toStdString());
    associationEnd->setClass(newClass);

}
