#include<ui/components/ModelGraphicsView.h>

#include <ui/view/ClassItemView.h>

#include <utils/Commands.h>

#include <ui/dialogs/MainWindow.h>

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

ModelGraphicsView::ModelGraphicsView(QWidget *parent, std::shared_ptr<MetaModel::MetaModel> model)
    : QGraphicsView(parent), model(model), minScale(0.25), maxScale(3.0), currentScale(1.0){
    setupGraphicsView();
    //this->setBackgroundBrush(QBrush(QColor(0x21252A)));
}

void ModelGraphicsView::setModel(std::shared_ptr<MetaModel::MetaModel> model){
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

void ModelGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        QList<QGraphicsItem *> selectedItems = scene()->selectedItems();
        try{
            for (QGraphicsItem *item : selectedItems) {
                if(auto classItemView = qgraphicsitem_cast<ClassItemView*>(item)){
                    RemoveMetaClassCommand* removeClassCommand = new RemoveMetaClassCommand(classItemView, this->scene(), this->model);
                    MainWindow::undoStack->push(removeClassCommand);
                }else if(auto enumItemView = qgraphicsitem_cast<EnumItemView*>(item)){
                    RemoveMetaEnumCommand* removeMetaEnumCommand = new RemoveMetaEnumCommand(enumItemView, this->scene(), this->model);
                    MainWindow::undoStack->push(removeMetaEnumCommand);
                }
                else if(auto associationItemView = qgraphicsitem_cast<AssociationItemView*>(item)){
                    RemoveMetaAssociationCommand* removeAssociationCommand = new RemoveMetaAssociationCommand(associationItemView, this->scene(), this->model);
                    MainWindow::undoStack->push(removeAssociationCommand);
                }
            }
        }catch(int err){
            qDebug() <<"code " << err;
        }
    } else {
        QGraphicsView::keyPressEvent(event); // Propaga el evento si no es Delete
    }
}

void ModelGraphicsView::drawBackground(QPainter *painter, const QRectF &rect){
    //painter->fillRect(rect, QColor(0x21252A));
}
