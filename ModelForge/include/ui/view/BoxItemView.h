#ifndef BOXITEMVIEW_H
#define BOXITEMVIEW_H

#include <QGraphicsItem>


class BoxItemView : public QGraphicsItem{
public:
    virtual void setWidth(qreal width){this->width=width;};
    virtual void setHeight(qreal height){this->height=height;};
    virtual void setDimensions(qreal width, qreal height){setWidth(width);setHeight(height);};
    virtual QPointF getDimensions() const {return QPointF(width, height);}

    QRectF boundingRect() const override{
        return QRectF(this->pos().x(), this->pos().y(), width, height);
    };

    virtual ~BoxItemView() = default;

private:
    qreal width, height;
};

#endif // BOXITEMVIEW_H
