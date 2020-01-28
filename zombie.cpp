#include "zombie.h"
#include "plant.h"
Zombie::Zombie(int frame, QPointF startPos, ZombieInfo info)
{
    this->frame = frame;
    frozenFrame = 0;
    //pos = startPos;
    setPos(startPos);
    this->info = info;
    hp = info.fullhp;
    moveFlag = true;
    atkFlag = false;
    stop = false;	//³õÊ¼×´Ì¬ÎªÒÆ¶¯×´Ì¬
    startmoveFrame = frame;
    startatkFrame = frame;
    movie = NULL;
}

bool Zombie::samePos(const QPointF pos)
{
    if (pos.x() == this->pos().x() && pos.y() == this->pos().y())
        return true;
    return false;
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    /*QImage image;

    image.load(":/img/" + s + ".gif");
    painter->drawImage(boundingRect(), image);
    */
    QString s(info.name.c_str());

    if(!movie)
    {
        movie = new QMovie;
        movie->setFileName(":/img/" + s + ".gif");
        movie->start();
    }
    QImage image = movie->currentImage();
    painter->drawImage(QRectF(0, -10, 100, 100), image);

    update();
}

QRectF Zombie::boundingRect() const
{
    return QRectF(0, 0, PLANT_WIDTH, PLANT_HEIGHT);
}

void Zombie::nextFrame(int currentFrame)
{
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        bool flag = false;
        for(int i = 0; i < items.size(); i++)
        {
            Plant *plant = qgraphicsitem_cast<Plant *>(items[i]);
            if(plant)
            {
                flag = true;
                plant->attacked(eat());
            }
        }
        if(!flag)
            move();
    }
    else
        move();
    if (stop)	//Í£Ö¹×´Ì¬£¬ÕýÔÚ¹¥»÷
    {
        if ((currentFrame - startatkFrame) % info.atkspeed == 0)
        {
            atkFlag = true;
        }
    }
    else //ÒÆ¶¯×´Ì¬
    {
        if ((currentFrame - startmoveFrame) % info.speed == 0)
        {
            moveFlag = true;
        }
    }
    if (frozenFrame > 0)
    {
        if(movie)
            movie->setPaused(true);
        frozenFrame--;
    }
    else
    {
        if(movie)
            movie->setPaused(false);
    }
}
void Zombie::move()
{
    stop = false;
    if (frozenFrame > 0)
        return;
    if (moveFlag)
    {
        QPointF p = pos();
        p.setX(p.x()-5);
        setPos(p);
        moveFlag = false;
    }
}

int Zombie::eat()
{
    stop = true;
    if (atkFlag)
    {
        atkFlag = false;
        return info.atk;
    }
    return 0;
}

QPointF Zombie::prePos()
{
    return pos();
}

void Zombie::attacked(int atk,int frozen)
{
    frozenFrame += frozen;
    hp -= atk;

}
void Zombie::refresh()
{

}
bool Zombie::clear()
{
    return hp <= 0;
}

QPointF Zombie::currentPos()
{
    return pos();
}
int Zombie::score()
{
    return info.score;
}

void ConeheadZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QString s(info.name.c_str());

    if(!movie)
    {
        movie = new QMovie;
        movie->setFileName(":/img/" + s + ".gif");
        movie->start();
    }
    if(this->hp <= 100 && cone == true)
    {
        movie->stop();
        delete movie;
        movie = new QMovie;
        movie->setFileName(":/img/Zombie.gif");
        movie->start();
        cone = false;
    }
    QImage image = movie->currentImage();
    painter->drawImage(QRectF(0, -10, 100, 100), image);

    update();
}
