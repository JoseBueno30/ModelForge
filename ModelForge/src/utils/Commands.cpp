#include <utils/Commands.h>
#include <ui/view/ClassItemView.h>
#include <ui/view/AssociationItemView.h>
#include <ui/view/AssociationClassItemView.h>
#include <ui/view/GeneralizationItemView.h>

MoveCommand::MoveCommand(QGraphicsItem *diagramItem, const QPointF &oldPos, QUndoCommand *parent)
    : QUndoCommand(parent),item(diagramItem), oldPos(oldPos), newPos(diagramItem->pos()){}

void MoveCommand::undo(){
    item->setPos(oldPos);
    ClassItemView * classCast = dynamic_cast<ClassItemView *>(item);
    if(classCast){
        classCast->updateConnectionPositions();
    }
    item->scene()->update();
}

void MoveCommand::redo(){
    item->setPos(newPos);
    ClassItemView * classCast = dynamic_cast<ClassItemView *>(item);
    if(classCast){
        classCast->updateConnectionPositions();
    }
    item->scene()->update();
}


EditMetaClassCommand::EditMetaClassCommand(
    std::shared_ptr<MetaModel::MetaClass> modelMetaElement, std::shared_ptr<MetaModel::MetaClass> newMetaElement, ClassItemView* classView, ModelGraphicsScene* scene)
    : modelMetaElement(modelMetaElement), newMetaElement(newMetaElement), scene(scene), classView(classView){
    this->oldMetaElement = std::make_shared<MetaModel::MetaClass>(*modelMetaElement);
}

void EditMetaClassCommand::undo(){
    *modelMetaElement = *oldMetaElement;
    classView->calculateMinimumSize();
    scene->update();
}

void EditMetaClassCommand::redo(){
    *modelMetaElement = *newMetaElement;
    classView->calculateMinimumSize();
    scene->update();
}

AddMetaClassCommand::AddMetaClassCommand(std::shared_ptr<MetaModel::MetaModel> model, std::shared_ptr<MetaModel::MetaClass> newClass, ClassItemView* newClassView, ModelGraphicsScene* scene)
    : model(model), newClass(newClass), newClassView(newClassView), scene(scene){}

void AddMetaClassCommand::undo(){
    this->model->removeClass(this->newClass->getName());
    scene->removeItem(newClassView);
    scene->removeModelItemView(this->newClass->getName());
    scene->update();
}

void AddMetaClassCommand::redo(){
    this->model->addClass(newClass);
    this->scene->addItem(newClassView);
    this->scene->addModelItemView(newClass->getName(), newClassView);
    this->scene->update();
}


AddMetaAssociationCommand::AddMetaAssociationCommand(
    std::shared_ptr<MetaModel::MetaAssociation> metaAssociation,std::shared_ptr<MetaModel::MetaModel> model, AssociationItemView *associationView, ModelGraphicsScene * scene)
    : metaAssociation(metaAssociation), model(model), associationView(associationView), scene(scene) {}

void AddMetaAssociationCommand::undo(){
    this->model->removeAssociation(metaAssociation->getName());

    this->associationView->getClass1()->deleteAssociation(this->associationView);
    this->associationView->getClass2()->deleteAssociation(this->associationView);

    this->associationView->applyOffsetToSharedAssociations();

    this->scene->removeItem(this->associationView);
    this->scene->removeModelItemView(this->metaAssociation->getName());
    this->scene->update();
}

void AddMetaAssociationCommand::redo(){
    this->model->addAssociation(this->metaAssociation);

    this->associationView->getClass1()->addAssociation(this->associationView);
    this->associationView->getClass2()->addAssociation(this->associationView);

    this->associationView->applyOffsetToSharedAssociations();

    this->scene->addItem(this->associationView);
    this->scene->addModelItemView(this->metaAssociation->getName(), this->associationView);
    this->scene->update();
}


EditMetaAssociationCommand::EditMetaAssociationCommand(
    std::shared_ptr<MetaModel::MetaAssociation> metaAssociation, std::shared_ptr<MetaModel::MetaAssociation> newMetaAssociation
    , AssociationItemView *associationView, ModelGraphicsScene * scene) :
    modelMetaAssociation(metaAssociation), newMetaAssociation(newMetaAssociation), scene(scene), sceneAssociationView(associationView){
    this->oldMetaAssociation = std::make_shared<MetaModel::MetaAssociation>(*metaAssociation);
}

void EditMetaAssociationCommand::updateItemView(std::shared_ptr<MetaModel::MetaAssociation> association){
    auto aEndsIt = association->getAssociationEnds().begin();
    ClassItemView* class1 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(aEndsIt->second->getClass().getName()));
    aEndsIt++;
    ClassItemView* class2 = dynamic_cast<ClassItemView*>(this->scene->getModelItemView(aEndsIt->second->getClass().getName()));

    this->sceneAssociationView->setClass1(class1);
    class1->addAssociation(this->sceneAssociationView);
    this->sceneAssociationView->setClass2(class2);
    class2->addAssociation(this->sceneAssociationView);

    this->sceneAssociationView->applyOffsetToSharedAssociations();
    this->sceneAssociationView->updatePosition();
}

void EditMetaAssociationCommand::undo(){
    *modelMetaAssociation = *oldMetaAssociation;

    updateItemView(oldMetaAssociation);
    scene->update();
}

void EditMetaAssociationCommand::redo(){
    *modelMetaAssociation = *newMetaAssociation;

    updateItemView(newMetaAssociation);
    scene->update();
}


AddMetaEnumCommand::AddMetaEnumCommand(std::shared_ptr<MetaModel::MetaEnum> metaEnum, std::shared_ptr<MetaModel::MetaModel> model, EnumItemView* enumItemView, ModelGraphicsScene* scene)
    : metaEnum(metaEnum), model(model), enumItemView(enumItemView), scene(scene){}

void AddMetaEnumCommand::undo(){
    model->removeEnum(metaEnum->getName());
    scene->removeItem(enumItemView);
    scene->removeModelItemView(metaEnum->getName());

    scene->update();
}

void AddMetaEnumCommand::redo(){
    model->addEnum(metaEnum);
    scene->addItem(enumItemView);
    scene->addModelItemView(metaEnum->getName(), enumItemView);

    scene->update();
}


EditMetaEnumCommand::EditMetaEnumCommand(std::shared_ptr<MetaModel::MetaEnum> modelMetaEnum, std::shared_ptr<MetaModel::MetaEnum> newMetaEnum, EnumItemView* enumItemView, ModelGraphicsScene* scene)
    : modelMetaEnum(modelMetaEnum), newMetaEnum(newMetaEnum), enumItemView(enumItemView), scene(scene){
    this->oldMetaEnum = std::make_shared<MetaModel::MetaEnum>(*modelMetaEnum);
}

void EditMetaEnumCommand::undo(){
    *this->modelMetaEnum = *this->oldMetaEnum;

    this->enumItemView->calculateMinimumSize();
    this->scene->update();
}

void EditMetaEnumCommand::redo(){
    *this->modelMetaEnum = *this->newMetaEnum;

    this->enumItemView->calculateMinimumSize();
    this->scene->update();
}


RemoveMetaClassCommand::RemoveMetaClassCommand(ClassItemView* classItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model)
    : classItemView(classItemView), scene(scene), model(model){}

void RemoveMetaClassCommand::undo(){
    for(auto associationItemView : this->classItemView->getAssociations()){
        qDebug() << "a";
        this->scene->addItem(associationItemView);
        this->scene->addModelItemView(associationItemView->getAssociationModel()->getName(), associationItemView);

        if(!std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(associationItemView->getAssociationModel())){
            qDebug() << "added - " << associationItemView->getAssociationModel()->getName() + " association";
            this->model->addAssociation(associationItemView->getAssociationModel());
        }
    }


    for(auto associationClassesItemView : this->classItemView->getAssociationClasses()){
        qDebug() << "a";
        this->scene->addItem(associationClassesItemView);
        this->scene->addModelItemView(associationClassesItemView->getAssociationClassModel()->getName(), associationClassesItemView);
        if(!classItemView->getClassModel()->equals(*associationClassesItemView->getAssociationClassItemView()->getClassModel())){
            qDebug() << "a1";
            this->scene->addItem(associationClassesItemView->getAssociationClassItemView());
        }
        qDebug() << "a";

        auto auxAssociationItemView = associationClassesItemView->getAssociationClassAssociationItemView();
        this->scene->addItem(auxAssociationItemView);
        this->scene->addModelItemView(auxAssociationItemView->getAssociationModel()->getName(), auxAssociationItemView);

        if(!this->classItemView->getClassModel()->equals(*associationClassesItemView->getAssociationClassModel())){
            this->model->addAssociationClass(associationClassesItemView->getAssociationClassModel());
        }
    }

    for(auto generalizationItemView : this->classItemView->getGeneralizations()){
        auto superClass = generalizationItemView->getSuperClass();
        auto subClass = generalizationItemView->getSubClass();

        if(this->classItemView == superClass){
            subClass->getClassModel()->addSuperClass(superClass->getClassModel());
        }else{
            superClass->getClassModel()->addChildrenClass(subClass->getClassModel());
        }

        this->scene->addItem(generalizationItemView);
    }
    qDebug() << "a";
    this->scene->addItem(this->classItemView);
    this->scene->addModelItemView(this->classItemView->getClassModel()->getName(), this->classItemView);
    if(!std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(this->classItemView->getClassModel())){
        this->model->addClass(this->classItemView->getClassModel());
    }else{
        this->model->addAssociationClass(std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(this->classItemView->getClassModel()));
    }

}
void RemoveMetaClassCommand::redo(){
    for(auto associationItemView : this->classItemView->getAssociations()){
        /*if(this->classItemView == associationItemView->getClass1()){
            associationItemView->getClass2()->deleteAssociation(associationItemView);
        }else{
            associationItemView->getClass1()->deleteAssociation(associationItemView);
        }*/
        this->scene->removeItem(associationItemView);
        this->scene->removeModelItemView(associationItemView->getAssociationModel()->getName());
        qDebug() << "a";
        if(!std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(associationItemView->getAssociationModel())){
            this->model->removeAssociation(associationItemView->getAssociationModel()->getName());
        }
        qDebug() << "b";
    }

    for(auto associationClassItemView : this->classItemView->getAssociationClasses()){
        /*if(this->classItemView == associationClassItemView->getClass1()){
            associationClassItemView->getClass2()->deleteAssociationClass(associationClassItemView);
        }else{
             associationClassItemView->getClass1()->deleteAssociationClass(associationClassItemView);
        }*/
        this->scene->removeItem(associationClassItemView);
        this->scene->removeModelItemView(associationClassItemView->getAssociationClassModel()->getName());
        if(!classItemView->getClassModel()->equals(*associationClassItemView->getAssociationClassModel())){
            this->scene->removeItem(associationClassItemView->getAssociationClassItemView());
        }

        auto auxAssociationItemView = associationClassItemView->getAssociationClassAssociationItemView();
        this->scene->removeItem(auxAssociationItemView);
        this->scene->removeModelItemView(auxAssociationItemView->getAssociationModel()->getName());

        qDebug() << "aa - " << associationClassItemView->getAssociationClassModel()->getName() << this->model->modelContainsKey( associationClassItemView->getAssociationClassModel()->getName());
        qDebug() << this->model->getAssociationClass(associationClassItemView->getAssociationClassModel()->getName())->getName();
        this->model->removeAssociationClass(associationClassItemView->getAssociationClassModel()->getName());
        qDebug() << "bb";
    }

    for(auto generalizationItemView : this->classItemView->getGeneralizations()){
        auto superClass = generalizationItemView->getSuperClass();
        auto subClass = generalizationItemView->getSubClass();

        if(this->classItemView == superClass){
            subClass->getClassModel()->removeSuperClass(superClass->getClassModel()->getName());
        }else{
            superClass->getClassModel()->removeChildrenClass(subClass->getClassModel()->getName());
        }
        this->scene->removeItem(generalizationItemView);
    }
    qDebug() << "cc";
    this->scene->removeItem(this->classItemView);
    this->scene->removeModelItemView(this->classItemView->getClassModel()->getName());
    qDebug() << "dd";
    if(!std::dynamic_pointer_cast<MetaModel::MetaAssociationClass>(this->classItemView->getClassModel())){
        this->model->removeClass(this->classItemView->getClassModel()->getName());
    }
    qDebug() << "ee";
    this->scene->update();
}

RemoveMetaAssociationCommand::RemoveMetaAssociationCommand(AssociationItemView* associationItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model)
    : associationItemView(associationItemView), scene(scene), model(model){}

void RemoveMetaAssociationCommand::undo(){
    if(auto associationClassItem = this->associationItemView->getAssociationClassItem()){
        scene->addItem(associationClassItem);
        scene->addModelItemView(associationClassItem->getAssociationClassModel()->getName(), associationClassItem);

        auto auxClassItemView = associationClassItem->getAssociationClassItemView();
        scene->addItem(auxClassItemView);
        scene->addModelItemView(auxClassItemView->getClassModel()->getName(), auxClassItemView);

        this->associationItemView->getClass1()->addAssociationClass(associationClassItem);
        this->associationItemView->getClass2()->addAssociationClass(associationClassItem);

        model->addAssociationClass(associationClassItem->getAssociationClassModel());
    }else{
        model->addAssociation(this->associationItemView->getAssociationModel());
    }

    scene->addItem(this->associationItemView);
    scene->addModelItemView(this->associationItemView->getAssociationModel()->getName(), this->associationItemView);
    this->associationItemView->getClass1()->addAssociation(this->associationItemView);
    this->associationItemView->getClass2()->addAssociation(this->associationItemView);

    scene->update();
}

void RemoveMetaAssociationCommand::redo(){
    if(auto associationClassItem = this->associationItemView->getAssociationClassItem()){
        scene->removeItem(associationClassItem);
        scene->removeModelItemView(associationClassItem->getAssociationClassModel()->getName());

        auto auxClassItemView = associationClassItem->getAssociationClassItemView();
        scene->removeItem(auxClassItemView);
        scene->removeModelItemView(auxClassItemView->getClassModel()->getName());


        this->associationItemView->getClass1()->deleteAssociationClass(associationClassItem);
        this->associationItemView->getClass2()->deleteAssociationClass(associationClassItem);

        model->removeAssociationClass(associationClassItem->getAssociationClassModel()->getName());
    }else{
        model->removeAssociation(this->associationItemView->getAssociationModel()->getName());
    }

    scene->removeItem(this->associationItemView);
    scene->removeModelItemView(this->associationItemView->getAssociationModel()->getName());

    this->associationItemView->getClass1()->deleteAssociation(this->associationItemView);
    this->associationItemView->getClass2()->deleteAssociation(this->associationItemView);

    scene->update();
}

RemoveMetaEnumCommand::RemoveMetaEnumCommand(EnumItemView* enumItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model)
    : enumItemView(enumItemView), scene(scene), model(model){}

void RemoveMetaEnumCommand::undo(){
    scene->addItem(enumItemView);
    scene->addModelItemView(enumItemView->getMetaEnumModel()->getName(), enumItemView);
    model->addEnum(enumItemView->getMetaEnumModel());

    scene->update();
}

void RemoveMetaEnumCommand::redo(){
    qDebug() << "enum";
    scene->removeItem(enumItemView);
    scene->removeModelItemView(enumItemView->getMetaEnumModel()->getName());
    qDebug() << "enum";
    model->removeEnum(enumItemView->getMetaEnumModel()->getName());
    qDebug() << "enum";
    scene->update();
}

RemoveMetaGeneralizationCommand::RemoveMetaGeneralizationCommand(GeneralizationItemView* generalizationItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model)
    : generalizationItemView(generalizationItemView), scene(scene), model(model){}

void RemoveMetaGeneralizationCommand::undo(){
    scene->addItem(generalizationItemView);

    auto superClass = generalizationItemView->getSuperClass();
    auto subClass = generalizationItemView->getSubClass();

    subClass->addGeneralization(generalizationItemView);
    superClass->addGeneralization(generalizationItemView);

    superClass->getClassModel()->addChildrenClass(subClass->getClassModel());
    subClass->getClassModel()->addSuperClass(superClass->getClassModel());

    scene->update();
}

void RemoveMetaGeneralizationCommand::redo(){
    scene->removeItem(generalizationItemView);

    auto superClass = generalizationItemView->getSuperClass();
    auto subClass = generalizationItemView->getSubClass();

    subClass->deleteGeneralization(generalizationItemView);
    superClass->deleteGeneralization(generalizationItemView);

    superClass->getClassModel()->removeChildrenClass(subClass->getClassModel()->getName());
    subClass->getClassModel()->removeSuperClass(superClass->getClassModel()->getName());

    this->scene->update();
}




