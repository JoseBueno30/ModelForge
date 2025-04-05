#ifndef COMMANDS_H
#define COMMANDS_H

#include "metamodel/MetaElement.h"
#include <QGraphicsItem>
#include <QUndoCommand>

#include <metamodel/MetaAttribute.h>

class MoveCommand : public QUndoCommand
{
public:
    MoveCommand(QGraphicsItem *diagramItem, const QPointF &oldPos,
                QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    QGraphicsItem *item;
    QPointF oldPos;
    QPointF newPos;
};

class EditMetaElementCommand : public QUndoCommand{
public:
    EditMetaElementCommand(std::shared_ptr<MetaModel::MetaElement> modelElement, std::shared_ptr<MetaModel::MetaElement> newElement);

    void undo() override;
    void redo() override;

private:

    std::shared_ptr<MetaModel::MetaElement> modelMetaElement;
    std::shared_ptr<MetaModel::MetaElement> oldMetaElement;
    std::shared_ptr<MetaModel::MetaElement> newMetaElement;
};


#endif // COMMANDS_H
