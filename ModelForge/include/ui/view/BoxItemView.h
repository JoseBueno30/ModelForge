#ifndef BOXITEMVIEW_H
#define BOXITEMVIEW_H
#define HORIZONTAL_PADDING 20
#define NAME_PADDING 10
#define ATTS_PADDING 5
#define ATTS_HEIGHT 15

#include <QGraphicsItem>


class BoxItemView : virtual public QGraphicsItem{
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

    virtual void setX(qreal x){this->x = x;}
    virtual qreal getX() const {return this->x;}
    virtual void setY(qreal y){this->y = y;}
    virtual qreal getY() const {return this->y;}
    virtual QPointF getPosition() const{return QPointF(x,y);}
    virtual void setPosition(qreal x, qreal y){setX(x);setY(y);}
    virtual void setPosition(QPointF p){setX(p.x());setY(p.y());}

    QRectF boundingRect() const override{
        return QRectF(0, 0, width, height);
    };

    virtual ~BoxItemView() = default;

protected:
    QPointF oldPos;

private:
    qreal x,y, width, height, minWidth, minHeight;
};

#endif // BOXITEMVIEW_H
