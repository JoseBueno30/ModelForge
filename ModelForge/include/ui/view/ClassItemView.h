#ifndef CLASSITEMVIEW_H
#define CLASSITEMVIEW_H

#include <ui/view/BoxItemView.h>
#include <QPainter>
#include <metamodel/MetaClass.h>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <ui/components/ModelGraphicsView.h>

using std::shared_ptr;

class AssociationItemView;
class AssociationClassItemView;
class GeneralizationItemView;

class ClassItemView : public BoxItemView{
public:
    ClassItemView(shared_ptr<MetaModel::MetaClass> model);
    ClassItemView(shared_ptr<MetaModel::MetaClass> model, int x, int y);
    ClassItemView(shared_ptr<MetaModel::MetaClass> model, int x, int y, int width, int height);

    QRectF classNameRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addAssociation(AssociationItemView* association);
    void deleteAssociation(AssociationItemView* association);

    void addAssociationClass(AssociationClassItemView* associationClass);
    void deleteAssociationClass(AssociationClassItemView* associationClass);

    void addGeneralization(GeneralizationItemView * generalization);
    void deleteGeneralization(GeneralizationItemView * generalization);

    ~ClassItemView();

protected:
    shared_ptr<MetaModel::MetaClass>& getClassModel();
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    shared_ptr<MetaModel::MetaClass> model;
    std::vector<AssociationItemView *> associations;
    std::vector<GeneralizationItemView *> generalizations;
    std::vector<AssociationClassItemView *> associationClasses;

    void calculateMinimumSize();

};

#endif // CLASSITEMVIEW_H
