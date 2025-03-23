#ifndef MODELGRAPHICSSCENE_H
#define MODELGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>



class ModelGraphicsScene : public QGraphicsScene{
    Q_OBJECT

public:
    ModelGraphicsScene(QObject *parent = nullptr);
    void emitSignal(QGraphicsItem * item, const QPointF& pos);

Q_SIGNALS:
    void itemMoved();

};
#endif // MODELGRAPHICSSCENE_H
