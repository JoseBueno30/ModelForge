#include <ui/components/ModelGraphicsScene.h>
#include <QGraphicsItem>
#include <ui/view/ClassItemView.h>

#include <QGraphicsSceneMouseEvent>

ModelGraphicsScene::ModelGraphicsScene(QObject* parent) : QGraphicsScene(parent){

}

void ModelGraphicsScene::emitMoveSignal(QGraphicsItem * item,const QPointF& pos){
    if (!item) {
        return;
    }

    if(pos != item->pos()){
        Q_EMIT itemMoved(item, pos);
    }
}

void ModelGraphicsScene::emitEditAssociationSignal(AssociationItemView * association){
    Q_EMIT editAssociation(association);
}

void ModelGraphicsScene::emitEditClassSignal(ClassItemView* classView){
    Q_EMIT editClass(classView);
}

void ModelGraphicsScene::copyItemView(){
    for(auto item : this->selectedItems()){
        if(auto boxItem = qgraphicsitem_cast<ClassItemView*>(item)){
            clipboard->copy(boxItem);
        }
    }
}

void ModelGraphicsScene::cutItemView(){
    for(auto item : this->selectedItems()){
        if(auto boxItem = qgraphicsitem_cast<ClassItemView*>(item)){
            clipboard->cut(boxItem);
        }
    }
}

void ModelGraphicsScene::pasteItemView(){
    clipboard->paste();
}

void ModelGraphicsScene::setClipboard(ItemViewClipboard* clipboard){
    this->clipboard = clipboard;
}

void ModelGraphicsScene::setClipboardModel(std::shared_ptr<MetaModel::MetaModel> model){
    this->clipboard->setModel(model);
}

QGraphicsItem* ModelGraphicsScene::getModelItemView(const std::string& key){
    auto iterator = this->modelItemViewElementsMap.find(key);
    if(iterator != this->modelItemViewElementsMap.end()){
        return (iterator->second);
    }
    return nullptr;
}

std::map<std::string, QGraphicsItem*> ModelGraphicsScene::getModelItemViewElementsMap(){
    return this->modelItemViewElementsMap;
}

void ModelGraphicsScene::addModelItemView(const std::string& key, QGraphicsItem *item){
    this->modelItemViewElementsMap[key] = item;
}

void ModelGraphicsScene::removeModelItemView(const std::string& key){
    this->modelItemViewElementsMap.erase(key);
}
