#include "card.h"
Card::Card(const Card &c)
{
    info = c.info;
    plantImage = c.plantImage;
    this->setPos(c.pos());
    chosen = false;
}
Card::Card(const PlantInfo &info, QPointF pos)
{
    this->info = info;
    plantImage.load(":/img/" + info.name + ".png");
    this->setPos(pos);
    chosen = false;
}

void Card::advance(int phase)
{
    if (!phase)
        return;
    update();
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage tempImage;
    tempImage.load(":/img/PotatoMine.png");
    QRectF windowRect(CARD_IMG_X_START, CARD_IMG_Y_START, CARD_IMG_WIDTH, CARD_IMG_HEIGHT);
    painter->drawImage(windowRect, plantImage);
    if(chosen)
    {
        //painter->drawImage(boundingRect(), tempImage);
        QBrush brush(QColor(0, 0, 0, 50));
        painter->setBrush(brush);
        painter->drawRect(boundingRect());
    }
}

QRectF Card::boundingRect() const
{
    return QRectF(0, 0, CARD_WIDTH, CARD_HEIGHT);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!chosen && event->button() == Qt::LeftButton)
        chosen = true;
    if(event->button() == Qt::RightButton)
        chosen = false;
    //event->setAccepted(true);
    //setCursor(Qt::ClosedHandCursor);
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    /*QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    mime->setImageData(plantImage);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(plantImage));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
    */
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
bool Card::ifchosen()
{
    return chosen;
}

PlantInfo Card::plantInfo()
{
    return info;
}

void Card::cancel()
{
    chosen = false;
}
