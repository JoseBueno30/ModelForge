#include "ui/dialogs/MainWindow.h"
#include <include/utils/ItemViewClipboard.h>
#include <ui/components/ModelGraphicsScene.h>
#include <ui/view/ClassItemView.h>
#include <utils/Commands.h>

ItemViewClipboard::ItemViewClipboard(ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model) : scene(scene), model(model){}

std::string ItemViewClipboard::getClassCopyName(std::string name){
    int defaultNameCont = 0;
    std::string newName = name;
    for(auto metaClassPair : this->model->getClasses()){
        if(metaClassPair.first == newName){
            defaultNameCont++;
            newName = name + std::to_string(defaultNameCont);
        }
    }

    return newName;
}

std::string ItemViewClipboard::getEnumCopyName(std::string name){
    int defaultNameCont = 0;
    std::string newName = name;
    for(auto metaEnumPair : this->model->getEnums()){
        if(metaEnumPair.first == newName){
            defaultNameCont++;
            newName = name + std::to_string(defaultNameCont);
        }
    }

    return newName;
}

void ItemViewClipboard::copy(BoxItemView* item){
    if(auto classItemView = qgraphicsitem_cast<ClassItemView*>(item)){
        std::shared_ptr<MetaModel::MetaClass> metaClass = std::make_shared<MetaModel::MetaClass>(".", false);
        *metaClass = *(classItemView->getClassModel());
        metaClass->setName(metaClass->getName() + "Copy");
        itemView = new ClassItemView(metaClass);

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
        std::shared_ptr<MetaModel::MetaClass> metaClassToPaste = std::make_shared<MetaModel::MetaClass>(".", false);
        *metaClassToPaste = *(classItemView->getClassModel());
        std::string name = getClassCopyName(metaClassToPaste->getName());
        metaClassToPaste->setName(name);
        AddMetaClassCommand* command = new AddMetaClassCommand(model, metaClassToPaste, new ClassItemView(metaClassToPaste), scene);
        MainWindow::undoStack->push(command);
    }else if(itemView != nullptr){
        auto enumItemView = qgraphicsitem_cast<EnumItemView*>(itemView);
        std::shared_ptr<MetaModel::MetaEnum> metaEnumToPaste;
        *metaEnumToPaste = *(enumItemView->getMetaEnumModel());
        std::string name = getEnumCopyName(metaEnumToPaste->getName());
        metaEnumToPaste->setName(name);
        AddMetaEnumCommand* command = new AddMetaEnumCommand(metaEnumToPaste, model, new EnumItemView(metaEnumToPaste), scene);
        MainWindow::undoStack->push(command);
    }
}

void ItemViewClipboard::setModel(std::shared_ptr<MetaModel::MetaModel> model){
    this->model = model;
}
