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
    void emitEditClassSignal(ClassItemView* classView);

    void setClipboard(ItemViewClipboard* clipboard);
    void setClipboardModel(std::shared_ptr<MetaModel::MetaModel> model);

    QGraphicsItem* getModelItemView(const std::string& key);
    void addModelItemView(const std::string& key, QGraphicsItem *item);
    void removeModelItemView(const std::string& key);

    std::map<std::string, QGraphicsItem*> getModelItemViewElementsMap();

Q_SIGNALS:
    void itemMoved(QGraphicsItem * item, const QPointF& pos);
    void editAssociation(AssociationItemView * association);
    void editClass(ClassItemView* classView);

public Q_SLOTS:
    void copyItemView();
    void cutItemView();
    void pasteItemView();

private:
    ItemViewClipboard* clipboard;
    std::map<std::string, QGraphicsItem*> modelItemViewElementsMap;
};
#endif // MODELGRAPHICSSCENE_H
