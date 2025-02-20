#include<ui/view/ClassItemView.h>
#define PADDING 20
#define TEST_NAME "ClassLongTextAdriduty"

void ClassItemView::calculateMinimumSize(){
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    int classNameWidth = fm.horizontalAdvance(QString::fromStdString(this->model->getName())) + PADDING;
    this->setWidth(qMax(int(this->getDimensions().x()), classNameWidth));

    //TODO Check attributtes and operations longitude
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel) : model(classModel){
    this->setPos(0,0);
    this->setDimensions(150,100);
    calculateMinimumSize();
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel, int x, int y, int width, int height) :
    model(classModel){
    this->setPos(x,y);
    this->setDimensions(width, height);
}

QRectF ClassItemView::classNameRect() {
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    return QRectF(this->pos().x() + this->getDimensions().x() / 2 - fm.horizontalAdvance(QString::fromStdString(this->model->getName())) / 2,
                  this->pos().y(),
                  fm.horizontalAdvance(QString::fromStdString(this->model->getName())) , fm.height());
}

void ClassItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QColor(0x8DD0FF));
    painter->drawRoundedRect(boundingRect(),10,10);
    painter->setFont(QFont("Arial", 13, QFont::Bold));
    painter->drawText(classNameRect(), Qt::AlignCenter, QString::fromStdString(this->model->getName()));
}

ClassItemView::~ClassItemView(){}
