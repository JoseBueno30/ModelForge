#include <ui/components/ModelGraphicsScene.h>
#include <QGraphicsItem>
#include <ui/view/ClassItemView.h>

#include <QGraphicsSceneMouseEvent>

ModelGraphicsScene::ModelGraphicsScene(QObject* parent) : QGraphicsScene(parent){}

void ModelGraphicsScene::emitSignal(QGraphicsItem * item,const QPointF& pos){
    if (!item) {
        qDebug() << "Error: item es nullptr en emitSignal";
        return;
    }

    qDebug() << "Emitiendo señal con item:" << item << " posición: " << pos;
    if(pos != item->pos()){
        Q_EMIT itemMoved(item, pos);
    }
}
