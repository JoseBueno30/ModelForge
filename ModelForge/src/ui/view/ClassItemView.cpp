#include<ui/view/ClassItemView.h>
#define PADDING 20
#define TEST_NAME "ClassLongTextAdriduty"

void ClassItemView::calculateMinimumSize(){
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    int classNameWidth = fm.horizontalAdvance(TEST_NAME) + PADDING;
    this->width = qMax(this->width, classNameWidth);

    //TODO Check attributtes and operations longitude
}

ClassItemView::ClassItemView(MetaModel::MetaClass *classModel) : model(classModel), x(0), y(0), width(150), height(100){
    calculateMinimumSize();
}

ClassItemView::ClassItemView(MetaModel::MetaClass *classModel, int x, int y, int width, int height) :
    model(classModel),
    x(x), y(y),
    width(width),
    height(height){}

QRectF ClassItemView::boundingRect() const {
    return QRectF(x, y, width, height); // Replace with coordinates from ui
}

QRectF ClassItemView::classNameRect() {
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    return QRectF(x + width / 2 - fm.horizontalAdvance(QString::fromStdString(this->model->getName())) / 2, y,
                  fm.horizontalAdvance(QString::fromStdString(this->model->getName())) , fm.height());
}

void ClassItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QColor(0x8DD0FF));
    painter->drawRoundedRect(boundingRect(),10,10);
    painter->setFont(QFont("Arial", 13, QFont::Bold));
    painter->drawText(classNameRect(), Qt::AlignCenter, QString::fromStdString(this->model->getName()));
}
