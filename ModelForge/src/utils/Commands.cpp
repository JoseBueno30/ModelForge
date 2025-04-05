#include <utils/Commands.h>
#include <QGraphicsScene>
#include <ui/view/ClassItemView.h>

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
    std::shared_ptr<MetaModel::MetaClass> modelMetaElement, std::shared_ptr<MetaModel::MetaClass> newMetaElement, QGraphicsScene* scene)
    : modelMetaElement(modelMetaElement), newMetaElement(newMetaElement), scene(scene){
    this->oldMetaElement = std::make_shared<MetaModel::MetaClass>(*modelMetaElement);
}

void EditMetaClassCommand::undo(){
    *modelMetaElement = *oldMetaElement;
    scene->update();
}

void EditMetaClassCommand::redo(){
    *modelMetaElement = *newMetaElement;
    scene->update();
}

