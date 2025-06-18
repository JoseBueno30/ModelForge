#ifndef MODELGRAPHICSSCENE_H
#define MODELGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

#include <ui/view/AssociationItemView.h>

#include <utils/ItemViewClipboard.h>



class ModelGraphicsScene : public QGraphicsScene{
    Q_OBJECT

public:
    ModelGraphicsScene(QObject *parent = nullptr);
    void emitMoveSignal(QGraphicsItem * item, const QPointF& pos);
    void emitEditAssociationSignal(AssociationItemView * association);

    void setClipboard(ItemViewClipboard* clipboard);
    void setClipboardModel(std::shared_ptr<MetaModel::MetaModel> model);

Q_SIGNALS:
    void itemMoved(QGraphicsItem * item, const QPointF& pos);
    void editAssociation(AssociationItemView * association);

public Q_SLOTS:
    void copyItemView();
    void cutItemView();
    void pasteItemView();

private:
    ItemViewClipboard* clipboard;
};
#endif // MODELGRAPHICSSCENE_H
