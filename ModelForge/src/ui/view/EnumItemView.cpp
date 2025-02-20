#include<ui/view/EnumItemView.h>
#define PADDING 20

void EnumItemView::calculateMinimumSize(){
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    int classNameWidth = fm.horizontalAdvance(QString::fromStdString(this->model->getName())) + PADDING;
    this->setWidth(qMax(int(this->getDimensions().x()), classNameWidth));

    //TODO Check attributtes and operations longitude
}

EnumItemView::EnumItemView(shared_ptr<MetaModel::MetaEnum> model) : model(model){
    this->setPos(0,0);
    this->setDimensions(150, 100);
    calculateMinimumSize();
}

EnumItemView::EnumItemView(shared_ptr<MetaModel::MetaEnum> model, int x, int y, int width, int height) : model(model){
    this->setPos(x,y);
    this->setDimensions(width, height);
    calculateMinimumSize();
}

QRectF EnumItemView::enumNameRect(){
    return QRectF();
}

void EnumItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

}

EnumItemView::~EnumItemView(){}
