#include "utils/MessageBox.h"
#include <ui/dialogs/AssociationEditDialog.h>

#include <src/ui/dialogs/ui_AssociationEditDialog.h>

#include <QPushButton>

#include <ui/view/AssociationItemView.h>

#include <utils/Commands.h>

#include <ui/dialogs/MainWindow.h>

AssociationEditDialog::AssociationEditDialog(
    std::shared_ptr<MetaModel::MetaAssociation> associationModel,
    ModelGraphicsScene* scene,
    AssociationItemView * associationItemView,
    std::shared_ptr<MetaModel::MetaModel> model
    )
    :
    associationModel(associationModel), scene(scene), model(model),
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
    }else{
        ui->publicAEnd1RadioButton->setChecked(true);
        ui->publicAEnd2RadioButton->setChecked(true);
    }

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &AssociationEditDialog::saveChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &AssociationEditDialog::cancelChanges);

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
    loadVisibilityAssociationEnd1(associationEnd);
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
    loadVisibilityAssociationEnd2(associationEnd);
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

void AssociationEditDialog::loadVisibilityAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    switch (associationEnd->getVisibility()) {
    case MetaModel::Visibility::Public:
        ui->publicAEnd1RadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Private:
        ui->privateAEnd1RadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Protected:
        ui->protectedAEnd1RadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Package:
        ui->packageAEnd1RadioButton->setChecked(true);
        break;

    default:
        ui->publicAEnd1RadioButton->setChecked(true);
        break;
    }
}
void AssociationEditDialog::loadVisibilityAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    switch (associationEnd->getVisibility()) {
    case MetaModel::Visibility::Public:
        ui->publicAEnd2RadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Private:
        ui->privateAEnd2RadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Protected:
        ui->protectedAEnd2RadioButton->setChecked(true);
        break;

    case MetaModel::Visibility::Package:
        ui->packageAEnd2RadioButton->setChecked(true);
        break;

    default:
        ui->publicAEnd2RadioButton->setChecked(true);
        break;
    }
}

void AssociationEditDialog::cancelChanges(){
    auto reply = showQuestionMessageBox("Edit association", "Changes have not been saved. Do you want to cancel?", this);

    if(reply == QMessageBox::No){
        return;
    }

    reject();
}

void AssociationEditDialog::saveChanges(){
    try{
        if(!isValidAssociation()){
            showExceptionMessageBox("Error", "There was an error saving the association. Please check the console for more information.");
            return;
        }

        if(associationModel->getAssociationEnds().empty()){ //Creating new association
            //Check if fields have been completed and create associationEnds
            if(true){

                std::string associationName = ui->associationNameEdit->text().toStdString();

                if(this->model->getAssociation(associationName) != nullptr){
                    ConsoleHandler::appendErrorLog("The model already contains an association named '" + QString::fromStdString(associationName) +"'.");
                    return;
                }

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
                ClassItemView* class1 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(ui->typeAEnd1ComboBox->currentText().toStdString()));
                ClassItemView* class2 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(ui->typeAEnd2ComboBox->currentText().toStdString()));

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

                EditMetaAssociationCommand *editCommand = new EditMetaAssociationCommand(this->associationModel, newAssociation, this->associationItemView, this->scene);
                MainWindow::undoStack->push(editCommand);
            }
        }

        accept();
    }catch(std::invalid_argument exception){
        showExceptionMessageBox("Error", "There was an error saving the association. Please check the console for more information.");
        ConsoleHandler::appendErrorLog(exception.what());
    }

}

MetaModel::Visibility AssociationEditDialog::getVisibilityAssociationEnd1(){
    MetaModel::Visibility vis = MetaModel::Visibility::Package;
    if(ui->publicAEnd1RadioButton->isChecked()){
        vis = MetaModel::Visibility::Public;
    }
    else if(ui->privateAEnd1RadioButton->isChecked()){
        vis = MetaModel::Visibility::Private;
    }
    else if(ui->protectedAEnd1RadioButton->isChecked()){
        vis = MetaModel::Visibility::Protected;
    }

    return vis;
}

MetaModel::Visibility AssociationEditDialog::getVisibilityAssociationEnd2(){
    MetaModel::Visibility vis = MetaModel::Visibility::Package;
    if(ui->publicAEnd2RadioButton->isChecked()){
        vis = MetaModel::Visibility::Public;
    }
    else if(ui->privateAEnd2RadioButton->isChecked()){
        vis = MetaModel::Visibility::Private;
    }
    else if(ui->protectedAEnd2RadioButton->isChecked()){
        vis = MetaModel::Visibility::Protected;
    }

    return vis;
}

void AssociationEditDialog::setAssociationEnd1(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    associationEnd->setRole(ui->roleAEnd1LineEdit->text().toStdString());

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0,0);
    multiplicity->setMultiplicictyFromString(ui->multiplicityAEnd1LineEdit->text().toStdString());
    associationEnd->setMultiplicity(multiplicity);

    associationEnd->setVisibility(getVisibilityAssociationEnd1());

    auto newClass = this->model->getClass(ui->typeAEnd1ComboBox->currentText().toStdString());
    associationEnd->setClass(newClass);

    newClass->addAssociationEnd(associationEnd);
}

void AssociationEditDialog::setAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    associationEnd->setRole(ui->roleAEnd2LineEdit->text().toStdString());

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0,0);
    multiplicity->setMultiplicictyFromString(ui->multiplicityAEnd2LineEdit->text().toStdString());
    associationEnd->setMultiplicity(multiplicity);

    associationEnd->setVisibility(getVisibilityAssociationEnd2());

    auto newClass = this->model->getClass(ui->typeAEnd2ComboBox->currentText().toStdString());
    associationEnd->setClass(newClass);

    newClass->addAssociationEnd(associationEnd);
}

bool AssociationEditDialog::isValidAssociation(){
    bool isValid = true;

    QString multiplicity1 = ui->multiplicityAEnd1LineEdit->text();
    QString multiplicity2 = ui->multiplicityAEnd2LineEdit->text();

    static const QRegularExpression regex(R"((\d+|\*)(\.\.(\d+|\*))?(,(\d+|\*)(\.\.(\d+|\*))?)*)");

    if(!regex.match(multiplicity1).hasMatch()){
        ConsoleHandler::appendErrorLog("'" + multiplicity1 + "' is not a valid multiplicity. AssociationEnd 1.");
        isValid = false;
    }
    if(!regex.match(multiplicity2).hasMatch()){
        ConsoleHandler::appendErrorLog("'" + multiplicity2 + "' is not a valid multiplicity. AssociationEnd 2.");
        isValid = false;
    }

    return isValid;
}
