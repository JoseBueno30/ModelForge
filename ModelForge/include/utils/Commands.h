#ifndef COMMANDS_H
#define COMMANDS_H

#include <QGraphicsItem>
#include <QUndoCommand>

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

// class DeleteCommand : public QUndoCommand
// {
// public:
//     explicit DeleteCommand(QGraphicsScene *graphicsScene, QUndoCommand *parent = nullptr);

//     void undo() override;
//     void redo() override;

// private:
//     QGraphicsItem *myDiagramItem;
//     QGraphicsScene *myGraphicsScene;
// };

// class AddCommand : public QUndoCommand
// {
// public:
//     AddCommand(QGraphicsItem *item, QGraphicsScene *graphicsScene,
//                QUndoCommand *parent = nullptr);
//     ~AddCommand();

//     void undo() override;
//     void redo() override;

// private:
//     QGraphicsItem *myDiagramItem;
//     QGraphicsScene *myGraphicsScene;
//     QPointF initialPosition;
// };

#endif // COMMANDS_H
