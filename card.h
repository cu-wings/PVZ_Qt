#ifndef CARD_H
#define CARD_H
#include "head.h"
#include "plant.h"
class Card : public QGraphicsItem
{
private:
    PlantInfo info;
    QImage plantImage;
    bool chosen;
public:
    Card(const Card& c);
    Card(const PlantInfo &info, QPointF pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    bool ifchosen();
    PlantInfo plantInfo();
    void cancel(); //取消选中
};
#endif // CARD_H
