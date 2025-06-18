#ifndef ITEMVIEWCLIPBOARD_H
#define ITEMVIEWCLIPBOARD_H

#include <ui/view/BoxItemView.h>

#include <metamodel/MetaModel.h>

class ItemViewClipboard : public QObject{
    Q_OBJECT

public:

    ItemViewClipboard(QGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model);

    void copy(BoxItemView* item);
    void cut(BoxItemView* item);
    void paste();

    void setModel(std::shared_ptr<MetaModel::MetaModel> model);

private:
    BoxItemView* itemView;
    QGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaModel> model;
};

#endif // ITEMVIEWCLIPBOARD_H
