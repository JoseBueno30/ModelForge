#include<ui/view/EnumItemView.h>

#include <ui/components/ModelGraphicsScene.h>

#include <ui/dialogs/EnumEditDialog.h>

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
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

EnumItemView::EnumItemView(shared_ptr<MetaModel::MetaEnum> model, int x, int y, int width, int height) : model(model){
    this->setPos(x,y);
    this->setDimensions(width, height);
    calculateMinimumSize();
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QRectF EnumItemView::enumNameRect(){
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    return QRectF(this->getDimensions().x() / 2 - fm.horizontalAdvance(QString::fromStdString(this->model->getName())) / 2,
                  0,
                  fm.horizontalAdvance(QString::fromStdString(this->model->getName())) , fm.height() + NAME_PADDING);
}

void EnumItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(this->borderColor, this->borderWidth));
    painter->setBrush(QColor(0x8DD0FF));


    painter->drawRoundedRect(boundingRect(),10,10);
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial", 13, QFont::Bold));
    painter->drawText(enumNameRect(), Qt::AlignCenter, QString::fromStdString(this->model->getName()));

    painter->drawLine(QLine(0,enumNameRect().height(), this->getDimensions().x(), enumNameRect().height()));
    int yOffset = enumNameRect().height() + ATTS_PADDING;

    painter->setFont(QFont("Arial", 10, QFont::StyleNormal));
    for(const auto& pair : this->model->getElements()){
        QRectF rect(ATTS_PADDING, yOffset, this->getDimensions().x(), ATTS_HEIGHT);
        painter->drawText(rect, Qt::AlignLeft, QString::fromStdString(pair.first));
        yOffset += ATTS_HEIGHT;
    }
}

void EnumItemView::mousePressEvent(QGraphicsSceneMouseEvent* event){
    setCursor(Qt::ClosedHandCursor);
    setZValue(ModelGraphicsView::highestZIndex);
    ModelGraphicsView::highestZIndex++;
    oldPos = pos();
    QGraphicsItem::mousePressEvent(event);
}

void EnumItemView::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    QGraphicsItem::mouseMoveEvent(event);
}

void EnumItemView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    setCursor(Qt::ArrowCursor);

    ModelGraphicsScene* scene = dynamic_cast<ModelGraphicsScene*>(this->scene());
    if(this->scene()!=nullptr){
        scene->emitMoveSignal(this, oldPos);
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

void EnumItemView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
    auto scene = dynamic_cast<ModelGraphicsScene*>(this->scene());
    EnumEditDialog* editDialog = new EnumEditDialog(this->model, scene, nullptr, this, nullptr);
    editDialog->exec();
}

std::shared_ptr<MetaModel::MetaEnum> EnumItemView::getMetaEnumModel(){
    return this->model;
}
