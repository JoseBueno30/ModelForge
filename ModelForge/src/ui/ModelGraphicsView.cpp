#include<ui/ModelGraphicsView.h>

ModelGraphicsView::ModelGraphicsView(QWidget *parent) : QGraphicsView(parent){
    setObjectName("modelGraphicsView");
    setDragMode(QGraphicsView::NoDrag);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setSceneRect(-10000, -10000, 20000, 20000);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setBackgroundBrush(QBrush(QColor(0x21252A)));
}


void ModelGraphicsView::wheelEvent(QWheelEvent *event){
    double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0)
        scale(scaleFactor, scaleFactor);
    else
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
}

void ModelGraphicsView::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::MiddleButton){
        viewport()->update();
        setDragMode(QGraphicsView::ScrollHandDrag);

        QMouseEvent fakeEvent(QEvent::MouseButtonPress, event->position(), event->globalPosition(),
                              Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QGraphicsView::mousePressEvent(&fakeEvent);
    }else{
        QGraphicsView::mousePressEvent(event);
    }
}

void ModelGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        viewport()->update();
        setDragMode(QGraphicsView::NoDrag);
        QMouseEvent fakeEvent(QEvent::MouseButtonPress, event->position(), event->globalPosition(),
                              Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QGraphicsView::mouseReleaseEvent(&fakeEvent);

    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void ModelGraphicsView::drawBackground(QPainter *painter, const QRectF &rect){
    //painter->fillRect(rect, QColor(0x21252A));
}
