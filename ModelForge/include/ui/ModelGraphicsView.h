#ifndef MODELGRAPHICSVIEW_H
#define MODELGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPainter>

class ModelGraphicsView : public QGraphicsView{
    Q_OBJECT

public:
    explicit ModelGraphicsView(QWidget * parent=nullptr);
//explicit ModelGraphicsView(QWidget *parent=nullptr, QGraphicsView *gview=nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // MODELGRAPHICSVIEW_H
