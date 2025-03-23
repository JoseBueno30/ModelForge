#include <utils/Commands.h>
#include <QGraphicsScene>

MoveCommand::MoveCommand(QGraphicsItem *diagramItem, const QPointF &oldPos, QUndoCommand *parent)
    : QUndoCommand(parent),item(diagramItem), oldPos(oldPos), newPos(diagramItem->pos()){}

void MoveCommand::undo(){
    item->setPos(oldPos);
    item->scene()->update();
}

void MoveCommand::redo(){
    item->setPos(newPos);
    item->scene()->update();
}
