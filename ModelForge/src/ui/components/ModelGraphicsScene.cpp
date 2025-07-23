#include <ui/components/ModelGraphicsScene.h>
#include <QGraphicsItem>
#include <ui/view/ClassItemView.h>

#include <QGraphicsSceneMouseEvent>

ModelGraphicsScene::ModelGraphicsScene(QObject* parent) : QGraphicsScene(parent){

}

void ModelGraphicsScene::emitMoveSignal(QGraphicsItem * item,const QPointF& pos){
    if (!item) {
        qDebug() << "Error: item es nullptr en emitSignal";
        return;
    }

    qDebug() << "Emitiendo señal con item:" << item << " posición: " << pos;
    if(pos != item->pos()){
        Q_EMIT itemMoved(item, pos);
    }
}

void ModelGraphicsScene::emitEditAssociationSignal(AssociationItemView * association){
    Q_EMIT editAssociation(association);
}

void ModelGraphicsScene::copyItemView(){
    for(auto item : this->selectedItems()){
        if(auto boxItem = qgraphicsitem_cast<ClassItemView*>(item)){
            qDebug() << "copiando";
            clipboard->copy(boxItem);
        }
    }
}

void ModelGraphicsScene::cutItemView(){
    for(auto item : this->selectedItems()){
        if(auto boxItem = qgraphicsitem_cast<ClassItemView*>(item)){
            qDebug() << "cortando";
            clipboard->cut(boxItem);
        }
    }
}

void ModelGraphicsScene::pasteItemView(){
    qDebug() << "pegando";
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

void ModelGraphicsScene::addModelItemView(const std::string& key, QGraphicsItem *item){
    this->modelItemViewElementsMap[key] = item;
}

void ModelGraphicsScene::removeModelItemView(const std::string& key){
    this->modelItemViewElementsMap.erase(key);
}
