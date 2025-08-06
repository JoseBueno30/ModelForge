#ifndef COMMANDS_H
#define COMMANDS_H

#include "metamodel/MetaClass.h"
#include "ui/view/ClassItemView.h"
#include "ui/view/EnumItemView.h"
#include <QGraphicsItem>
#include <QUndoCommand>

#include <metamodel/MetaAttribute.h>
#include <metamodel/MetaModel.h>
#include <ui/components/ModelGraphicsScene.h>

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
    EditMetaClassCommand(std::shared_ptr<MetaModel::MetaClass> modelElement, std::shared_ptr<MetaModel::MetaClass> newElement, ClassItemView* classView, ModelGraphicsScene* scene);

    void undo() override;
    void redo() override;

private:
    ModelGraphicsScene* scene;
    ClassItemView* classView;
    std::shared_ptr<MetaModel::MetaClass> modelMetaElement;
    std::shared_ptr<MetaModel::MetaClass> oldMetaElement;
    std::shared_ptr<MetaModel::MetaClass> newMetaElement;
};

class AddMetaClassCommand : public QUndoCommand{
public:
    AddMetaClassCommand(std::shared_ptr<MetaModel::MetaModel> model, std::shared_ptr<MetaModel::MetaClass> newClass, ClassItemView* newClassView, ModelGraphicsScene* scene);

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<MetaModel::MetaModel> model;
    std::shared_ptr<MetaModel::MetaClass> newClass;
    ClassItemView* newClassView;
    ModelGraphicsScene* scene;
};

class AddMetaAssociationCommand : public QUndoCommand{
public:
    AddMetaAssociationCommand(std::shared_ptr<MetaModel::MetaAssociation> metaAssociation, std::shared_ptr<MetaModel::MetaModel> model
                              , AssociationItemView *associationView, ModelGraphicsScene * scene);

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<MetaModel::MetaAssociation> metaAssociation;
    std::shared_ptr<MetaModel::MetaModel> model;
    AssociationItemView *associationView;
    ModelGraphicsScene * scene;
};

class EditMetaAssociationCommand : public QUndoCommand{
public:
    EditMetaAssociationCommand(std::shared_ptr<MetaModel::MetaAssociation> metaAssociation, std::shared_ptr<MetaModel::MetaAssociation> newMetaAssociation,
                               AssociationItemView *associationView, ModelGraphicsScene * scene);

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<MetaModel::MetaAssociation> modelMetaAssociation;
    std::shared_ptr<MetaModel::MetaAssociation> oldMetaAssociation;
    std::shared_ptr<MetaModel::MetaAssociation> newMetaAssociation;
    std::shared_ptr<MetaModel::MetaModel> model;
    AssociationItemView *sceneAssociationView;
    ModelGraphicsScene * scene;

    void updateItemView(std::shared_ptr<MetaModel::MetaAssociation> association);
};


class AddMetaEnumCommand : public QUndoCommand{
public:
    AddMetaEnumCommand(std::shared_ptr<MetaModel::MetaEnum> metaEnum, std::shared_ptr<MetaModel::MetaModel> model, EnumItemView* enumItemView, ModelGraphicsScene* scene);

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<MetaModel::MetaEnum> metaEnum;
    std::shared_ptr<MetaModel::MetaModel> model;
    EnumItemView* enumItemView;
    ModelGraphicsScene* scene;
};

class EditMetaEnumCommand : public QUndoCommand{
public:
    EditMetaEnumCommand(std::shared_ptr<MetaModel::MetaEnum> modelMetaEnum, std::shared_ptr<MetaModel::MetaEnum> newMetaEnum, EnumItemView* enumItemView, ModelGraphicsScene* scene);

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<MetaModel::MetaEnum> modelMetaEnum;
    std::shared_ptr<MetaModel::MetaEnum> newMetaEnum;
    std::shared_ptr<MetaModel::MetaEnum> oldMetaEnum;
    EnumItemView* enumItemView;
    ModelGraphicsScene* scene;
};

class RemoveMetaClassCommand : public QUndoCommand{
public:
    RemoveMetaClassCommand(ClassItemView* classItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model);

    void undo() override;
    void redo() override;

private:
    ClassItemView* classItemView;
    ModelGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaModel> model;
};

class RemoveMetaAssociationCommand : public QUndoCommand{
public:
    RemoveMetaAssociationCommand(AssociationItemView* associationItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model);

    void undo() override;
    void redo() override;

private:
    AssociationItemView* associationItemView;
    ModelGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaModel> model;
};

class RemoveMetaEnumCommand : public QUndoCommand{
public:
    RemoveMetaEnumCommand(EnumItemView* enumItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model);

    void undo() override;
    void redo() override;

private:
    EnumItemView* enumItemView;
    ModelGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaModel> model;
};

class RemoveMetaGeneralizationCommand : public QUndoCommand{
public:
    RemoveMetaGeneralizationCommand(GeneralizationItemView* generalizationItemView, ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model);

    void undo() override;
    void redo() override;

private:
    GeneralizationItemView* generalizationItemView;
    ModelGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaModel> model;
};

#endif // COMMANDS_H
