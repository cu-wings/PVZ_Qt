#include "shovel.h"
#include "info.h"
Shovel::Shovel(QPointF pos)
{
    shovelImage.load(":/img/shovel.png");
    shovelBackImage.load(":/img/shovelBack.png");
    this->setPos(pos);
    chosen = false;
}
void Shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
       for(int i = 0; i < items.size(); i++)
       {
           Info *info = qgraphicsitem_cast<Info *>(items[i]);
           if(info)
           {
               info->clickCut();
               chosen = true;
           }
       }
    }
}

void Shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(), shovelBackImage);
    if(!chosen)
        painter->drawImage(boundingRect(), shovelImage);
    update();
}

QRectF Shovel::boundingRect() const
{
    return QRectF(0, 0, SHOVEL_WIDTH, SHOVEL_WIDTH);
}

void Shovel::cancel()
{
    chosen = false;
}
