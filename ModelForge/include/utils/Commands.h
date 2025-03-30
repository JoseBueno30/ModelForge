#ifndef COMMANDS_H
#define COMMANDS_H

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

class DeleteClassCommand : public QUndoCommand
{
public:
    explicit DeleteClassCommand(QGraphicsItem *item, QGraphicsScene *graphicsScene, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    QGraphicsItem *myDiagramItem;
    QGraphicsScene *myGraphicsScene;
};

class AddClassCommand : public QUndoCommand
{
public:
    AddClassCommand(QGraphicsItem *item, QGraphicsScene *graphicsScene,
               QUndoCommand *parent = nullptr);
    ~AddClassCommand();

    void undo() override;
    void redo() override;

private:
    QGraphicsItem *myDiagramItem;
    QGraphicsScene *myGraphicsScene;
};

class AddAttributeCommand : public QUndoCommand{
public:
    AddAttributeCommand(QGraphicsScene *graphicsScene);
    ~AddAttributeCommand();

    void undo() override;
    void redo() override;

private:
};

class AddAssociationClassCommand : public QUndoCommand{
public:
    AddAssociationClassCommand(QGraphicsScene *graphicsScene);
    ~AddAssociationClassCommand();

    void undo() override;
    void redo() override;
private:
};

class AddEnumCommand : public QUndoCommand{
public:
    AddEnumCommand(QGraphicsScene *graphicsScene);
    ~AddEnumCommand();

    void undo() override;
    void redo() override;
private:
};

class EditAttributeCommand : public QUndoCommand{
public:
    EditAttributeCommand(QGraphicsScene *graphicsScene);
    ~EditAttributeCommand();

    void undo() override;
    void redo() override;
private:
};

class EditClassCommand : public QUndoCommand{
public:
    EditClassCommand(QGraphicsScene *graphicsScene);
    ~EditClassCommand();

    void undo() override;
    void redo() override;
private:
};

class EditAssociationClassCommand : public QUndoCommand{
public:
    EditAssociationClassCommand(QGraphicsScene *graphicsScene);
    ~EditAssociationClassCommand();

    void undo() override;
    void redo() override;
private:
};

class EditEnumCommand : public QUndoCommand{
public:
    EditEnumCommand(QGraphicsScene *graphicsScene);
    ~EditEnumCommand();

    void undo() override;
    void redo() override;
private:
};


#endif // COMMANDS_H
