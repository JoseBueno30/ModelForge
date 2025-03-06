#include<ui/components/ModelGraphicsView.h>

int ModelGraphicsView::highestZIndex = 1;

void ModelGraphicsView::setupGraphicsView(){
    setObjectName("modelGraphicsView");
    setDragMode(QGraphicsView::NoDrag);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setSceneRect(-10000, -10000, 20000, 20000);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

ModelGraphicsView::ModelGraphicsView(QWidget *parent, MetaModel::MetaModel *model)
    : QGraphicsView(parent), model(model), minScale(0.25), maxScale(3.0), currentScale(1.0){
    setupGraphicsView();
    //this->setBackgroundBrush(QBrush(QColor(0x21252A)));
}

void ModelGraphicsView::setModel(MetaModel::MetaModel *model){
    this->model = model;
}

void ModelGraphicsView::wheelEvent(QWheelEvent *event){
    constexpr double scaleFactor = 1.15;
    double factor = (event->angleDelta().y() > 0) ? scaleFactor : (1.0 / scaleFactor);

    double newScale = currentScale * factor;

    if (newScale >= minScale && newScale <= maxScale) {
        scale(factor, factor);
        currentScale = newScale;
    }
}

void ModelGraphicsView::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::MiddleButton || event->button() == Qt::LeftButton){
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
