#include<ui/ClassItemView.h>

ClassItemView::ClassItemView(ClassItemModel *classModel) : model(classModel){}

QRectF ClassItemView::boundingRect() const {
    return QRectF(0,0,100,50); // Use coordinates from ui
}

void ClassItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QColor(0x8DD0FF));
    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), Qt::AlignCenter, "Class");
}
