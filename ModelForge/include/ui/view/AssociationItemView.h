#ifndef ASSOCIATIONITEMVIEW_H
#define ASSOCIATIONITEMVIEW_H

#include <ui/view/ClassItemView.h>
#include <QGraphicsItem>
#include <QPainter>
#include <metamodel/MetaAssociation.h>
#include <ui/components/ThemeManager.h>
using std::shared_ptr;

enum ClassesOrientation {VERTICAL,HORIZONTAL};

class AssociationItemView : public QGraphicsItem{
public:
    AssociationItemView(shared_ptr<MetaModel::MetaAssociation> model,
                        ClassItemView* class1,
                        ClassItemView* class2);

    QRectF associationNameRect();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition();

    QPointF getP1() const;
    QPointF getP2() const;
    ClassItemView* getClass1() const;
    ClassItemView* getClass2() const;

    void setClass1(ClassItemView* newClass);
    void setClass2(ClassItemView* newClass);

    shared_ptr<MetaModel::MetaAssociation> getAssociationModel();
    QPointF getNearestEdgeIntersection(const QRectF &rect, const QLineF &line, const QPointF& last);

    void applyOffsetToSharedAssociations();
    void setOffset(qreal newOffset){this->offset = newOffset;}
    qreal getOffset(){return this->offset;}

    void setAssociationClassItem(AssociationClassItemView* associationClass);
    AssociationClassItemView* getAssociationClassItem() const;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override{
        if (change == QGraphicsItem::ItemSelectedChange) {
            if(value.toBool()){
                lineColor = Qt::blue;
            }else{
                lineColor = ThemeManager::getAssociationColor();
            }
        }
        this->update();
        return QGraphicsItem::itemChange(change, value);
    }

private:
    shared_ptr<MetaModel::MetaAssociation> model;
    ClassItemView* class1;
    ClassItemView* class2;
    AssociationClassItemView* associationClass;
    QPointF p1;
    QPointF p2;
    qreal offset;
    QColor lineColor = ThemeManager::getAssociationColor();

    void drawArrow(QLineF &line, QPainter *painter);
    QPointF drawDiamond(QLineF &line, QPainter *painter, bool filled);

    void setP1(QPointF p){this->p1 = p;}
    void setP2(QPointF p){this->p2 = p;}

    ClassesOrientation checkOrientation(QRectF& class1Rect, QRectF& class2Rect);
};

#endif // ASSOCIATIONITEMVIEW_H
