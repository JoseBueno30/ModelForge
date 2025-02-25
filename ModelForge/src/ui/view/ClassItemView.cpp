#include<ui/view/ClassItemView.h>
#define PADDING 20
#define TEST_NAME "ClassLongTextAdriduty"

void ClassItemView::calculateMinimumSize(){
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    int minHeight = fm.height() + NAME_PADDING + ATTS_PADDING;
    int classNameWidth = fm.horizontalAdvance(QString::fromStdString(this->model->getName())) + PADDING;
    this->setMinWidth(qMax(int(this->getDimensions().x()), classNameWidth));

    //TODO Check attributtes and operations longitude
    fm = QFontMetrics(QFont("Arial", 10, QFont::StyleNormal));
    for(const auto& pair : this->model->getAttributes()){
        int attrWidth = fm.horizontalAdvance(QString::fromStdString(pair.first + " : " + pair.second->getType().toString())) + HORIZONTAL_PADDING; //TODO MetaAttribute toString
        this->setMinWidth(qMax(int(this->getMinDimensions().x()), attrWidth));

        minHeight += ATTS_HEIGHT;
    }
    if(!this->model->getOperations().empty() && !this->model->getAttributes().empty()){
        minHeight += 2*ATTS_PADDING;
    }
    for(const auto& pair: this->model->getOperations()){
        int attrWidth = fm.horizontalAdvance(QString::fromStdString(pair.first + "() : " + pair.second->getReturnType().toString())); //TODO MetaOperation toString
        this->setMinWidth(qMax(int(this->getMinDimensions().x()), attrWidth));

        minHeight += ATTS_HEIGHT;
    }
    this->setMinHeight(minHeight+ATTS_PADDING);
    this->setDimensions(this->getMinDimensions());
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel) : model(classModel){
    this->setPosition(0,0);
    this->setDimensions(150,100);
    calculateMinimumSize();
    // qDebug() << "BoudningREct: " << this->boundingRect() <<"\tShape:" << this->shape();
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel, int x, int y) : model(classModel){
    this->setPosition(x,y);
    this->setDimensions(150,100);
    calculateMinimumSize();
    // qDebug() << "BoudningREct: " << this->boundingRect() <<"\tShape:" << this->shape();
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel, int x, int y, int width, int height) :
    model(classModel){
    this->setPosition(x,y);
    this->setDimensions(width, height);
    calculateMinimumSize();
    // qDebug() << "BoudningREct: " << this->boundingRect() <<"\tShape:" << this->shape();
}

QRectF ClassItemView::classNameRect() {
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    return QRectF(this->getX() + this->getDimensions().x() / 2 - fm.horizontalAdvance(QString::fromStdString(this->model->getName())) / 2,
                  this->getY(),
                  fm.horizontalAdvance(QString::fromStdString(this->model->getName())) , fm.height() + NAME_PADDING);
}

void ClassItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QColor(0x8DD0FF));
    painter->drawRoundedRect(ClassItemView::boundingRect(),10,10);

    painter->setFont(QFont("Arial", 13, QFont::Bold));
    painter->drawText(classNameRect(), Qt::AlignCenter, QString::fromStdString(this->model->getName()));

    painter->drawLine(QLine(this->getX(), this->getY() + classNameRect().height(),this->getX() + this->getDimensions().x(), this->getY() + classNameRect().height()));

    int yOffset = classNameRect().height() + ATTS_PADDING;

    painter->setFont(QFont("Arial", 10, QFont::StyleNormal));
    for(const auto& pair : this->model->getAttributes()){
        QRectF rect(this->getX() + ATTS_PADDING, this->getY() + yOffset,this->getDimensions().x(),ATTS_HEIGHT);
        painter->drawText(rect, Qt::AlignLeft, QString::fromStdString(pair.first + " : " + pair.second->getType().toString())); //TODO MetaAttribute toString
        yOffset += ATTS_HEIGHT;
    }

    yOffset += ATTS_PADDING;
    if(!this->model->getOperations().empty()){
        painter->drawLine(QLine(this->getX(), this->getY() + yOffset, this->getX() + this->getDimensions().x(), this->getY() + yOffset));
    }
    yOffset += ATTS_PADDING;

    for(const auto& pair: this->model->getOperations()){
        QRectF rect(this->getX() +ATTS_PADDING, this->getY() + yOffset,this->getDimensions().x(), ATTS_HEIGHT);
        painter->drawText(rect, Qt::AlignLeft, QString::fromStdString(pair.first + "() : " + pair.second->getReturnType().toString())); //TODO MetaOperation toString
        yOffset += ATTS_HEIGHT;
    }
}

shared_ptr<MetaModel::MetaClass>& ClassItemView::getClassModel(){
    return this->model;
}

ClassItemView::~ClassItemView(){}
