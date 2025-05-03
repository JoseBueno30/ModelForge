#include <utils/Commands.h>
#include <QGraphicsScene>
#include <ui/view/ClassItemView.h>
#include <ui/view/AssociationItemView.h>

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
    std::shared_ptr<MetaModel::MetaClass> modelMetaElement, std::shared_ptr<MetaModel::MetaClass> newMetaElement, ClassItemView* classView, QGraphicsScene* scene)
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

AddMetaClassCommand::AddMetaClassCommand(std::shared_ptr<MetaModel::MetaModel> model, std::shared_ptr<MetaModel::MetaClass> newClass, ClassItemView* newClassView, QGraphicsScene* scene)
    : model(model), newClass(newClass), newClassView(newClassView), scene(scene){}

void AddMetaClassCommand::undo(){
    this->model->removeClass(this->newClass->getName());
    scene->removeItem(newClassView);
    scene->update();
}

void AddMetaClassCommand::redo(){
    this->model->addClass(newClass);
    this->scene->addItem(newClassView);
    this->scene->update();
}


AddMetaAssociationCommand::AddMetaAssociationCommand(
    std::shared_ptr<MetaModel::MetaAssociation> metaAssociation,std::shared_ptr<MetaModel::MetaModel> model, AssociationItemView *associationView, QGraphicsScene * scene)
    : metaAssociation(metaAssociation), model(model), associationView(associationView), scene(scene) {}

void AddMetaAssociationCommand::undo(){
    this->model->removeAssociation(metaAssociation->getName());

    this->associationView->getClass1()->deleteAssociation(this->associationView);
    this->associationView->getClass2()->deleteAssociation(this->associationView);

    this->associationView->applyOffsetToSharedAssociations();

    this->scene->removeItem(this->associationView);
    this->scene->update();
}

void AddMetaAssociationCommand::redo(){
    this->model->addAssociation(this->metaAssociation);

    this->associationView->getClass1()->addAssociation(this->associationView);
    this->associationView->getClass2()->addAssociation(this->associationView);

    this->associationView->applyOffsetToSharedAssociations();

    this->scene->addItem(this->associationView);
    this->scene->update();
}


EditMetaAssociationCommand::EditMetaAssociationCommand(
    std::shared_ptr<MetaModel::MetaAssociation> metaAssociation, std::shared_ptr<MetaModel::MetaAssociation> newMetaAssociation
    , AssociationItemView *associationView, std::map<std::string, QGraphicsItem *> itemViewsMap, QGraphicsScene * scene) :
    modelMetaAssociation(metaAssociation), newMetaAssociation(newMetaAssociation), scene(scene), sceneAssociationView(associationView), itemViewsMap(itemViewsMap){
    this->oldMetaAssociation = std::make_shared<MetaModel::MetaAssociation>(*metaAssociation);
}

void EditMetaAssociationCommand::updateItemView(std::shared_ptr<MetaModel::MetaAssociation> association){
    auto aEndsIt = association->getAssociationEnds().begin();
    ClassItemView* class1 = dynamic_cast<ClassItemView*>(itemViewsMap.find(aEndsIt->second->getClass().getName())->second);
    aEndsIt++;
    ClassItemView* class2 = dynamic_cast<ClassItemView*>(itemViewsMap.find(aEndsIt->second->getClass().getName())->second);

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



