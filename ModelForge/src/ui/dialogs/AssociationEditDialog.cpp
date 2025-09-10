 #include "utils/MessageBox.h"
#include <ui/dialogs/AssociationEditDialog.h>

#include <src/ui/dialogs/ui_AssociationEditDialog.h>

#include <QPushButton>

#include <ui/view/AssociationClassItemView.h>
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

    if( auto aclass = std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(associationModel)){
        for(auto aEnd : aclass->MetaAssociation::getAssociationEnds()){
        }
    }

    setupUiInfo();

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &AssociationEditDialog::saveChanges);
    disconnect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &AssociationEditDialog::cancelChanges);

}

void AssociationEditDialog::setupUiInfo(){
    ui->associationNameEdit->setText(QString::fromStdString(associationModel->getName()));

    //set ui type
    setupTypesComboBox();
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

                setAssociationEnd1(associationEnd1);
                setAssociationEnd2(associationEnd2);

                ClassItemView* class1 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(ui->typeAEnd1ComboBox->currentText().toStdString()));
                ClassItemView* class2 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(ui->typeAEnd2ComboBox->currentText().toStdString()));

                if(auto associationClassModelCast = std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(this->associationModel)){
                    associationClassModelCast->addAssociationEnd(associationEnd1);
                    associationClassModelCast->addAssociationEnd(associationEnd2);
                    AssociationClassItemView* associationClassView = new AssociationClassItemView(associationClassModelCast, class1, class2);
                    AddMetaAssociationClassCommand* addCommand = new AddMetaAssociationClassCommand(associationClassModelCast, model, associationClassView, scene);
                    MainWindow::undoStack->push(addCommand);
                }else{
                    associationModel->addAssociationEnd(associationEnd1);
                    associationModel->addAssociationEnd(associationEnd2);
                    AssociationItemView * newAssociation = new AssociationItemView(associationModel, class1, class2);
                    AddMetaAssociationCommand* addCommand = new AddMetaAssociationCommand(associationModel, model, newAssociation, scene);
                    MainWindow::undoStack->push(addCommand);
                }
            }
        }
        else{ //Updating an existing association
                // std::vector<std::string> oldAEndClassNames = associationModel->getAssociationEndsClassesNames();
                // std::vector<std::string> oldRoles;
                // std::vector<std::string> oldMultiplicities;
                // for(auto [key, aEnd] : associationModel->getAssociationEnds()){
                //     oldRoles.push_back(aEnd->getRole());
                //     oldMultiplicities.push_back(aEnd->getMultiplicity().toString());
                // }

                // std::shared_ptr<MetaModel::MetaAssociation> newAssociation = std::make_shared<MetaModel::MetaAssociation>(*this->associationModel);
                std::string oldName = this->associationModel->getName();

                this->associationModel->setName(ui->associationNameEdit->text().toStdString());

                this->associationModel->setType(ui->associationTypeComboBox->currentIndex());

                auto aEndsIt = this->associationModel->getAssociationEnds().begin();
                std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd1 = std::make_shared<MetaModel::MetaAssociationEnd>(*aEndsIt->second);
                aEndsIt++;
                std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd2 = std::make_shared<MetaModel::MetaAssociationEnd>(*aEndsIt->second);

                this->model->removeAssociation(oldName);

                setAssociationEnd1(associationEnd1);
                setAssociationEnd2(associationEnd2);

                auto classItemView1 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(associationEnd1->getClass().getName()));
                auto classItemView2 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(associationEnd2->getClass().getName()));

                if(auto associationClassModel = std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(this->associationModel)){
                    this->model->removeAssociationClass(oldName);
                    this->model->addAssociationClass(associationClassModel);
                    associationClassModel->addAssociationEnd(associationEnd1);
                    associationClassModel->addAssociationEnd(associationEnd2);

                    auto assocClassItemViewAux = dynamic_cast<AssociationClassItemView*>(this->scene->getModelItemView(associationClassModel->getName()));
                    assocClassItemViewAux->getAssociationClassItemView()->calculateMinimumSize();
                    auto associationItemViewAux = assocClassItemViewAux->getAssociationClassAssociationItemView();

                    associationItemViewAux->getClass1()->deleteAssociationClass(assocClassItemViewAux);
                    associationItemViewAux->getClass1()->deleteAssociation(associationItemViewAux);
                    associationItemViewAux->getClass2()->deleteAssociationClass(assocClassItemViewAux);
                    associationItemViewAux->getClass2()->deleteAssociation(associationItemViewAux);

                    associationItemViewAux->setClass1(classItemView1);
                    classItemView1->addAssociationClass(assocClassItemViewAux);
                    classItemView1->addAssociation(associationItemViewAux);
                    associationItemViewAux->setClass2(classItemView2);
                    classItemView2->addAssociationClass(assocClassItemViewAux);
                    classItemView2->addAssociation(associationItemViewAux);
                }else{

                    this->model->addAssociation(this->associationModel);
                    this->associationModel->addAssociationEnd(associationEnd1);
                    this->associationModel->addAssociationEnd(associationEnd2);

                    for(auto aEnds : this->associationModel->getAssociationEnds()){
                        qDebug() << "AENDS: " << aEnds.second->getClass().getName();
                    }

                    this->associationItemView->getClass1()->deleteAssociation(this->associationItemView);
                    this->associationItemView->getClass2()->deleteAssociation(this->associationItemView);

                    this->associationItemView->setClass1(classItemView1);
                    classItemView1->addAssociation(this->associationItemView);
                    this->associationItemView->setClass2(classItemView2);
                    classItemView2->addAssociation(this->associationItemView);
                }
                classItemView1->updateConnectionPositions();
                classItemView2->updateConnectionPositions();
                this->scene->update();
                //EditMetaAssociationCommand *editCommand = new EditMetaAssociationCommand(this->associationModel, newAssociation, oldAEndClassNames, oldRoles, oldMultiplicities, this->model, this->associationItemView, this->scene);
                //MainWindow::undoStack->push(editCommand);
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
    auto newClass = this->model->getClass(ui->typeAEnd1ComboBox->currentText().toStdString());
    associationEnd->setClass(newClass);

    associationEnd->setRole(ui->roleAEnd1LineEdit->text().toStdString());

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0,0);
    multiplicity->setMultiplicictyFromString(ui->multiplicityAEnd1LineEdit->text().toStdString());
    associationEnd->setMultiplicity(multiplicity);

    associationEnd->setVisibility(getVisibilityAssociationEnd1());

    //newClass->removeAssociationEnd(associationEnd->getRole());
    //newClass->addAssociationEnd(associationEnd);
}

void AssociationEditDialog::setAssociationEnd2(std::shared_ptr<MetaModel::MetaAssociationEnd> associationEnd){
    auto newClass = this->model->getClass(ui->typeAEnd2ComboBox->currentText().toStdString());
    associationEnd->setClass(newClass);

    associationEnd->setRole(ui->roleAEnd2LineEdit->text().toStdString());

    auto multiplicity = std::make_shared<MetaModel::MetaMultiplicity>(0,0);
    multiplicity->setMultiplicictyFromString(ui->multiplicityAEnd2LineEdit->text().toStdString());
    associationEnd->setMultiplicity(multiplicity);

    associationEnd->setVisibility(getVisibilityAssociationEnd2());



    //newClass->removeAssociationEnd(associationEnd->getRole());
    //newClass->addAssociationEnd(associationEnd);
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
