#ifndef MODELGRAPHICSSCENE_H
#define MODELGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

#include <ui/view/AssociationItemView.h>



class ModelGraphicsScene : public QGraphicsScene{
    Q_OBJECT

public:
    ModelGraphicsScene(QObject *parent = nullptr);
    void emitMoveSignal(QGraphicsItem * item, const QPointF& pos);
    void emitEditAssociationSignal(AssociationItemView * association);

Q_SIGNALS:
    void itemMoved(QGraphicsItem * item, const QPointF& pos);
    void editAssociation(AssociationItemView * association);

};
#endif // MODELGRAPHICSSCENE_H
