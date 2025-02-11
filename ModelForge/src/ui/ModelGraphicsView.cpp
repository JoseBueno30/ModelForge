#include<ui/ModelGraphicsView.h>

ModelGraphicsView::ModelGraphicsView(QWidget *parent) : QGraphicsView(parent){
    setDragMode(QGraphicsView::NoDrag);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setSceneRect(-10000, -10000, 20000, 20000);
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
        setDragMode(QGraphicsView::NoDrag);
        QMouseEvent fakeEvent(QEvent::MouseButtonPress, event->position(), event->globalPosition(),
                              Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QGraphicsView::mouseReleaseEvent(&fakeEvent);
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}
