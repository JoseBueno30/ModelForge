#ifndef ITEMVIEWCLIPBOARD_H
#define ITEMVIEWCLIPBOARD_H

#include <ui/view/BoxItemView.h>

#include <metamodel/MetaModel.h>

class ModelGraphicsScene;

class ItemViewClipboard : public QObject{
    Q_OBJECT

public:

    ItemViewClipboard(ModelGraphicsScene* scene, std::shared_ptr<MetaModel::MetaModel> model);

    void copy(BoxItemView* item);
    void cut(BoxItemView* item);
    void paste();

    void setModel(std::shared_ptr<MetaModel::MetaModel> model);

private:
    BoxItemView* itemView;
    ModelGraphicsScene* scene;
    std::shared_ptr<MetaModel::MetaModel> model;

    std::string getClassCopyName(std::string name);
    std::string getEnumCopyName(std::string name);
};

#endif // ITEMVIEWCLIPBOARD_H
