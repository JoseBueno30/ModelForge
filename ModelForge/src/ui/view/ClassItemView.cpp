
#include<ui/view/ClassItemView.h>
#include <ui/view/AssociationItemView.h>
#include <ui/view/AssociationClassItemView.h>
#include <ui/view/GeneralizationItemView.h>

#include <ui/components/ModelGraphicsScene.h>
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
        int attrWidth = fm.horizontalAdvance(QString::fromStdString(pair.second->toString())) + HORIZONTAL_PADDING;
        this->setMinWidth(qMax(int(this->getMinDimensions().x()), attrWidth));

        minHeight += ATTS_HEIGHT;
    }

    if(!this->model->getOperations().empty() && !this->model->getAttributes().empty()){
        minHeight += 2*ATTS_PADDING;
    }

    for(const auto& pair: this->model->getOperations()){
        int attrWidth = fm.horizontalAdvance(QString::fromStdString(pair.second->toString())) + HORIZONTAL_PADDING;
        this->setMinWidth(qMax(int(this->getMinDimensions().x()), attrWidth));

        minHeight += ATTS_HEIGHT;
    }

    this->setMinHeight(minHeight+ATTS_PADDING);
    this->setDimensions(this->getMinDimensions());
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel) : model(classModel){
    this->setPos(0,0);
    this->setDimensions(150,100);
    calculateMinimumSize();
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    // qDebug() << "BoudningREct: " << this->boundingRect() <<"\tShape:" << this->shape();
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel, int x, int y) : model(classModel){
    this->setPos(x,y);
    this->setDimensions(150,100);
    calculateMinimumSize();

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    // qDebug() << "BoudningREct: " << this->boundingRect() <<"\tShape:" << this->shape();
}

ClassItemView::ClassItemView(shared_ptr<MetaModel::MetaClass> classModel, int x, int y, int width, int height) :
    model(classModel){
    this->setPosition(x,y);
    this->setDimensions(width, height);
    calculateMinimumSize();
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    // qDebug() << "BoudningREct: " << this->boundingRect() <<"\tShape:" << this->shape();
}

QRectF ClassItemView::classNameRect() {
    QFontMetrics fm(QFont("Arial", 13, QFont::Bold));
    return QRectF(this->getDimensions().x() / 2 - fm.horizontalAdvance(QString::fromStdString(this->model->getName())) / 2,
                  0,
                  fm.horizontalAdvance(QString::fromStdString(this->model->getName())) , fm.height() + NAME_PADDING);
}

void ClassItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    if(model->getIsAbstract()){
        painter->setBrush(QColor(0xCC9FED));
    }else{
        painter->setBrush(QColor(0x8DD0FF));
    }

    painter->setPen(QPen(Qt::black));
    painter->drawRoundedRect(ClassItemView::boundingRect(),5,5);

    painter->setFont(QFont("Arial", 13, QFont::Bold));
    painter->drawText(classNameRect(), Qt::AlignCenter, QString::fromStdString(this->model->getName()));

    painter->drawLine(QLine(0, classNameRect().height(),this->getDimensions().x(), classNameRect().height()));

    int yOffset = classNameRect().height() + ATTS_PADDING;

    painter->setFont(QFont("Arial", 10, QFont::StyleNormal));
    for(const auto& pair : this->model->getAttributes()){
        QRectF rect(ATTS_PADDING, yOffset,this->getDimensions().x(),ATTS_HEIGHT);
        painter->drawText(rect, Qt::AlignLeft, QString::fromStdString(pair.second->toString()));
        yOffset += ATTS_HEIGHT;
    }

    yOffset += ATTS_PADDING;
    if(!this->model->getOperations().empty()){
        painter->drawLine(QLine(0, yOffset, this->getDimensions().x(), yOffset));
    }
    yOffset += ATTS_PADDING;

    for(const auto& pair: this->model->getOperations()){
        QRectF rect(ATTS_PADDING, yOffset,this->getDimensions().x(), ATTS_HEIGHT);
        painter->drawText(rect, Qt::AlignLeft, QString::fromStdString(pair.second->toString()));
        yOffset += ATTS_HEIGHT;
    }
}

shared_ptr<MetaModel::MetaClass>& ClassItemView::getClassModel(){
    return this->model;
}

void ClassItemView::addAssociation(AssociationItemView* association){
    this->associations.push_back(association);
}

void ClassItemView::deleteAssociation(AssociationItemView* association){
    this->associations.erase(std::remove(this->associations.begin(), this->associations.end(), association), this->associations.end());
}
void ClassItemView::addAssociationClass(AssociationClassItemView* associationClass){
    this->associationClasses.push_back(associationClass);
}
void ClassItemView::deleteAssociationClass(AssociationClassItemView* associationClass){
    this->associationClasses.erase(std::remove(this->associationClasses.begin(), this->associationClasses.end(), associationClass), this->associationClasses.end());
}

void ClassItemView::addGeneralization(GeneralizationItemView * generalization){
    this->generalizations.push_back(generalization);
}

void ClassItemView::deleteGeneralization(GeneralizationItemView * generalization){
    this->generalizations.erase(std::remove(this->generalizations.begin(), this->generalizations.end(), generalization), this->generalizations.end());
}


std::vector<AssociationItemView *> ClassItemView::associationsShared(ClassItemView *class2){
    //TODO Add generalizations and associationClasses in the future

    std::vector<AssociationItemView *> associationsShared;
    for(auto association : this->associations){
        if(association->getClass1()->getClassModel()->equals(*class2->model) ||
            association->getClass2()->getClassModel()->equals(*class2->model)){
            associationsShared.push_back(association);
        }
    }
    return associationsShared;
}


void ClassItemView::mousePressEvent(QGraphicsSceneMouseEvent* event){
    setCursor(Qt::ClosedHandCursor);
    setZValue(ModelGraphicsView::highestZIndex);
    ModelGraphicsView::highestZIndex++;
    oldPos = pos();
    QGraphicsItem::mousePressEvent(event);
}

void ClassItemView::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    //this->setPosition(event->pos() - this->ClassItemView::boundingRect().center());
    //this->scene()->update();
    QGraphicsItem::mouseMoveEvent(event);
    for(auto association: this->associations){
        association->updatePosition();
    }
    for(auto associationClass : associationClasses){
        associationClass->update();
    }
    for(auto generalization : generalizations){
        generalization->updatePosition();
    }
}

void ClassItemView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    setCursor(Qt::ArrowCursor);
    ModelGraphicsScene* scene = dynamic_cast<ModelGraphicsScene*>(this->scene());
    qDebug() << "casteado y pos: " << oldPos;
    scene->emitSignal(this, oldPos);
    qDebug() << "movido";
    QGraphicsItem::mouseReleaseEvent(event);
}

ClassItemView::~ClassItemView(){}
