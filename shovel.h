#ifndef SHOVEL_H
#define SHOVEL_H
#include "head.h"
class Shovel : public QGraphicsItem
{
private:
    QImage shovelImage;
    QImage shovelBackImage;
    bool chosen;
public:
    enum { Type = UserType + 3 };
    int type() const { return Type; }
    Shovel(QPointF pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    void cancel();
};
#endif // SHOVEL_H
