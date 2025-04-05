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


EditMetaElementCommand::EditMetaElementCommand(
    std::shared_ptr<MetaModel::MetaElement> modelMetaElement, std::shared_ptr<MetaModel::MetaElement> newMetaElement)
    : modelMetaElement(modelMetaElement), oldMetaElement(modelMetaElement), newMetaElement(newMetaElement){}

void EditMetaElementCommand::undo(){
    *modelMetaElement = *oldMetaElement;
}

void EditMetaElementCommand::redo(){
    *modelMetaElement = *newMetaElement;
}

