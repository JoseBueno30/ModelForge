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
    void updateConnectionPositions();

    enum{Type = UserType + 1};
    int type() const override{return Type;}

    void addAssociation(AssociationItemView* association);
    void deleteAssociation(AssociationItemView* association);
    std::vector<AssociationItemView *> getAssociations();

    void addAssociationClass(AssociationClassItemView* associationClass);
    void deleteAssociationClass(AssociationClassItemView* associationClass);
    std::vector<AssociationClassItemView *> getAssociationClasses();

    void addGeneralization(GeneralizationItemView * generalization);
    void deleteGeneralization(GeneralizationItemView * generalization);
    std::vector<GeneralizationItemView *> getGeneralizations();

    std::vector<AssociationItemView *> associationsShared(ClassItemView *class2);

    void calculateMinimumSize();
    shared_ptr<MetaModel::MetaClass>& getClassModel();

    ~ClassItemView();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    shared_ptr<MetaModel::MetaClass> model;
    std::vector<AssociationItemView *> associations;
    std::vector<GeneralizationItemView *> generalizations;
    std::vector<AssociationClassItemView *> associationClasses;

};

#endif // CLASSITEMVIEW_H
