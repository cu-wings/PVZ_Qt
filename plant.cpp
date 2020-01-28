#include "plant.h"
#include "zombie.h"
PlantInfo::PlantInfo()
{
    cost = -1;
}
PlantInfo::PlantInfo(const PlantInfo &p)
{
    this->atk = p.atk;
    this->atkspeed = p.atkspeed;
    this->cost = p.cost;
    this->fullhp = p.fullhp;
    this->no = p.no;
    this->name = p.name;
}

Plant::Plant(int frame, QPointF pos, PlantInfo info)
{
	this->frame = frame;
    setPos(pos);
    //this->pos = { pos.x + (int)info.name.length() ,pos.y };
	this->info = info;
	this->hp = info.fullhp;

}
bool Plant::samePos(const QPointF pos)
{
    if (pos.x() == this->pos().x() && pos.y() == this->pos().y())
        return true;
	return false;
}
void Plant::nextFrame(int currentFrame)
{
    Q_UNUSED(currentFrame)
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image;
    image.load(":/img/" + info.name + ".png");
    painter->drawImage(boundingRect(), image);
}

QRectF Plant::boundingRect() const
{
    return QRectF(0, 0, PLANT_WIDTH, PLANT_HEIGHT);
}

void Plant::cut()
{
	hp = 0;
	//refresh();
}

int Plant::plantNo()
{
	return info.no;
}
QPointF Plant::currentPos()
{
    return pos();
}

void Plant::refresh()
{
}
bool Plant::clear()
{
	return hp <= 0;
}
int Plant::nameLength()
{
	return (int)info.name.length();
}
void Plant::attacked(int atk)
{
	hp -= atk;
}
void PeaShooter::nextFrame(int currentFrame)
{
	if ((currentFrame - frame) % info.atkspeed == 0)
		shootFlag = true;	
}

Pea* PeaShooter::shoot(int currentFrame)
{
	Pea* newPea = NULL;
	if (shootFlag)
	{
        QPointF p(pos().x() + PLANT_WIDTH, pos().y() + 5);
        newPea = new Pea(currentFrame, info.atk, p, PEA_SPEED);
        scene()->addItem(newPea);
	}
	shootFlag = false;
	return newPea;
}

Pea* SnowPea::shoot(int currentFrame)
{
	Pea* newPea = NULL;
	if (shootFlag)
	{
        QPointF p(pos().x() + PLANT_WIDTH, pos().y() + 5);
		newPea = new Snow(currentFrame, info.atk, p, PEA_SPEED);
        scene()->addItem(newPea);
	}
	shootFlag = false;
	return newPea;
}

void SunFlower::nextFrame(int currentFrame)
{
	if ((currentFrame - frame) % info.atkspeed == 0)
		sunFlag = true;
}

Sun *SunFlower::produceSun(int currentFrame)
{
    Sun *newSun = NULL;
	if (sunFlag)
    {
        //ret = 50;
        newSun = new Sun(currentFrame, QPointF(pos().x() + PLANT_WIDTH, pos().y() + 5));
        scene()->addItem(newSun);
    }
	sunFlag = false;
    return newSun;
}

Pea::Pea(int frame, int atk, QPointF startPos, int speed)
{
	no = PEA;
	this->frame = frame;
	this->atk = atk;
    //this->pos = startPos;
    setPos(startPos);
    this->speed = speed;
    death = false;
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image;
    image.load(":/img/Pea.png");
    painter->drawImage(boundingRect(), image);
}

void Snow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image;
    image.load(":/img/Snow.png");
    painter->drawImage(boundingRect(), image);
}

QRectF Pea::boundingRect() const
{
    return QRectF(0, 0, PEA_WIDTH, PEA_WIDTH);
}

void Pea::nextFrame(int currentFrame)
{
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
       for(int i = 0; i < items.size(); i++)
       {
           Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[i]);
           if(zombie != NULL)
           {
               if(zombie->Type == Zombie::Type)
               {
                   zombie->attacked(atk, 0);
                   death = true;
               }
           }
       }
    }
	if ((currentFrame - frame) % speed == 0)
		move();
}

void Snow::nextFrame(int currentFrame)
{
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
       for(int i = 0; i < items.size(); i++)
       {
           Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[i]);
           if(zombie != NULL)
           {
               if(zombie->Type == Zombie::Type)
               {
                   zombie->attacked(atk, FROZEN);
                   death = true;
               }
           }
       }
    }
    if ((currentFrame - frame) % speed == 0)
        move();
}

void Pea::move()
{
    QPointF p(pos());
    p.setX(pos().x() + 3);
    setPos(p);
    //qDebug() << pos().x();
}

bool Pea::dead()
{
    return death;
}
void Pea::refresh()
{
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleCursorPosition(handle, { (short)pos.x,(short)pos.y });
    /*if (no == SNOW)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	}
	cout << "o";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY| FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);
    */
}

QPointF Pea::currentPos()
{
    return pos();
}

int Pea::peaNo()
{
	return no;
}

int Pea::attack()
{
	return atk;
}

bool Pea::samePos(const QPointF pos)
{
    if (pos.x() == this->pos().x() && pos.y() == this->pos().y())
		return true;
	return false;
}

Sun::Sun(int frame, QPointF pos)
{
    this->frame = frame;
    movie = NULL;
    setPos(pos);
    death = false;
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(!movie)
    {
        movie = new QMovie;
        movie->setFileName(":/img/Sun.gif");
        movie->start();
    }
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
    update();
}
QRectF Sun::boundingRect() const
{
    return QRectF(0, 0, 66, 65);
}
int Sun::frameNum()
{
    return frame;
}

bool Sun::dead()    //ÅÐ¶ÏÊÇ·ñÒªÏû³ý
{
    return death;
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        death = true;
    }
}
