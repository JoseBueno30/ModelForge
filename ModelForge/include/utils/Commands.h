#ifndef COMMANDS_H
#define COMMANDS_H

#include "metamodel/MetaClass.h"
#include "ui/view/ClassItemView.h"
#include <QGraphicsItem>
#include <QUndoCommand>

#include <metamodel/MetaAttribute.h>
#include <metamodel/MetaModel.h>

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

class EditMetaClassCommand : public QUndoCommand{
public:
    EditMetaClassCommand(std::shared_ptr<MetaModel::MetaClass> modelElement, std::shared_ptr<MetaModel::MetaClass> newElement, QGraphicsScene* scene);

    void undo() override;
    void redo() override;

private:
    QGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaClass> modelMetaElement;
    std::shared_ptr<MetaModel::MetaClass> oldMetaElement;
    std::shared_ptr<MetaModel::MetaClass> newMetaElement;
};

class AddMetaClassCommand : public QUndoCommand{
public:
    AddMetaClassCommand(std::shared_ptr<MetaModel::MetaModel> model, std::shared_ptr<MetaModel::MetaClass> newClass, ClassItemView* newClassView, QGraphicsScene* scene);

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<MetaModel::MetaModel> model;
    std::shared_ptr<MetaModel::MetaClass> newClass;
    ClassItemView* newClassView;
    QGraphicsScene* scene;
};


#endif // COMMANDS_H
