#include<ui/view/EnumItemView.h>

void EnumItemView::calculateMinimumSize(){
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    int minHeight = fm.height() + NAME_PADDING + ATTS_PADDING;
    int enumNameWidth = fm.horizontalAdvance(QString::fromStdString(this->model->getName())) + HORIZONTAL_PADDING;
    this->setMinWidth(qMax(int(this->getDimensions().x()), enumNameWidth));

    //Check enumtypes
    fm = QFontMetrics(QFont("Arial", 10, QFont::StyleNormal));
    for(const auto& pair : this->model->getElements()){
        int typeWidth = fm.horizontalAdvance(QString::fromStdString(pair.first)) + HORIZONTAL_PADDING;
        this->setMinWidth(qMax(int(this->getMinDimensions().x()), typeWidth));
        minHeight += ATTS_HEIGHT;
    }
    this->setMinHeight(minHeight+ATTS_PADDING);
    this->setDimensions(this->getMinDimensions());
}

EnumItemView::EnumItemView(shared_ptr<MetaModel::MetaEnum> model) : model(model){
    this->setPos(0,0);
    this->setDimensions(150, 150);
    calculateMinimumSize();
}

EnumItemView::EnumItemView(shared_ptr<MetaModel::MetaEnum> model, int x, int y, int width, int height) : model(model){
    this->setPos(x,y);
    this->setDimensions(width, height);
    calculateMinimumSize();
}

QRectF EnumItemView::enumNameRect(){
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    return QRectF(this->pos().x() + this->getDimensions().x() / 2 - fm.horizontalAdvance(QString::fromStdString(this->model->getName())) / 2,
                  this->pos().y(),
                  fm.horizontalAdvance(QString::fromStdString(this->model->getName())) , fm.height() + NAME_PADDING);
}

void EnumItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QColor(0x8DD0FF));
    painter->drawRoundedRect(boundingRect(),10,10);
    painter->setFont(QFont("Arial", 13, QFont::Bold));
    painter->drawText(enumNameRect(), Qt::AlignCenter, QString::fromStdString(this->model->getName()));

    painter->drawLine(QLine(this->pos().x(),this->pos().y() + enumNameRect().height(), this->pos().x() + this->getDimensions().x(), this->pos().y() + enumNameRect().height()));
    int yOffset = enumNameRect().height() + ATTS_PADDING;

    painter->setFont(QFont("Arial", 10, QFont::StyleNormal));
    for(const auto& pair : this->model->getElements()){
        QRectF rect(this->pos().x() + ATTS_PADDING, this->pos().y() + yOffset, this->getDimensions().x(), ATTS_HEIGHT);
        painter->drawText(rect, Qt::AlignLeft, QString::fromStdString(pair.first));
        yOffset += ATTS_HEIGHT;
    }
}

EnumItemView::~EnumItemView(){}
