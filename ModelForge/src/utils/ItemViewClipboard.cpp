#include "ui/dialogs/MainWindow.h"
#include <include/utils/ItemViewClipboard.h>
#include <ui/components/ModelGraphicsScene.h>
#include <ui/view/ClassItemView.h>
#include <utils/Commands.h>

ItemViewClipboard::ItemViewClipboard(ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model) : scene(scene), model(model){}

void ItemViewClipboard::copy(BoxItemView* item){
    if(auto classItemView = qgraphicsitem_cast<ClassItemView*>(item)){
        std::shared_ptr<MetaModel::MetaClass> metaClass = std::make_shared<MetaModel::MetaClass>(".", false);
        qDebug() << "n";
        *metaClass = *(classItemView->getClassModel());
        qDebug() << "n";
        metaClass->setName(metaClass->getName() + "Copy");
        qDebug() << "n";
        itemView = new ClassItemView(metaClass);
        qDebug() << "n";
    }else{
        auto enumItemView = qgraphicsitem_cast<EnumItemView*>(item);
        std::shared_ptr<MetaModel::MetaEnum> metaEnum;
        *metaEnum = *(enumItemView->getMetaEnumModel());
        metaEnum->setName(metaEnum->getName() + "Copy");
        itemView = new EnumItemView(metaEnum);
    }
}

void ItemViewClipboard::cut(BoxItemView* item){
    if(auto classItemView = qgraphicsitem_cast<ClassItemView*>(item)){
        itemView = classItemView;
        RemoveMetaClassCommand* command = new RemoveMetaClassCommand(classItemView, scene, model);
        MainWindow::undoStack->push(command);
    }else{
        auto enumItemView = qgraphicsitem_cast<EnumItemView*>(item);
        itemView = enumItemView;
        RemoveMetaEnumCommand* command = new RemoveMetaEnumCommand(enumItemView, scene, model);
        MainWindow::undoStack->push(command);
    }
}

void ItemViewClipboard::paste(){
    if(auto classItemView = qgraphicsitem_cast<ClassItemView*>(itemView)){
        AddMetaClassCommand* command = new AddMetaClassCommand(model, classItemView->getClassModel(), classItemView, scene);
        MainWindow::undoStack->push(command);
    }else if(itemView != nullptr){
        auto enumItemView = qgraphicsitem_cast<EnumItemView*>(itemView);
        AddMetaEnumCommand* command = new AddMetaEnumCommand(enumItemView->getMetaEnumModel(), model, enumItemView, scene);
        MainWindow::undoStack->push(command);
    }
}

void ItemViewClipboard::setModel(std::shared_ptr<MetaModel::MetaModel> model){
    this->model = model;
}
