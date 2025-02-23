#ifndef BOXITEMVIEW_H
#define BOXITEMVIEW_H
#define HORIZONTAL_PADDING 20
#define NAME_PADDING 10
#define ATTS_PADDING 5
#define ATTS_HEIGHT 15

#include <QGraphicsItem>


class BoxItemView : public QGraphicsItem{
public:
    virtual void setWidth(qreal width){this->width=width;};
    virtual void setHeight(qreal height){this->height=height;};
    virtual void setDimensions(qreal width, qreal height){setWidth(width);setHeight(height);};
    virtual void setDimensions(QPointF newDimension){setWidth(newDimension.x()); setHeight(newDimension.y());}
    virtual QPointF getDimensions() const {return QPointF(width, height);}

    virtual void setMinWidth(qreal width){this->minWidth=width;};
    virtual void setMinHeight(qreal height){this->minHeight=height;};
    virtual void setMinDimensions(qreal width, qreal height){setMinWidth(width);setMinHeight(height);};
    virtual QPointF getMinDimensions() const {return QPointF(minWidth, minHeight);}



    QRectF boundingRect() const override{
        return QRectF(this->pos().x(), this->pos().y(), width, height);
    };

    virtual ~BoxItemView() = default;

private:
    qreal width, height, minWidth, minHeight;
};

#endif // BOXITEMVIEW_H
