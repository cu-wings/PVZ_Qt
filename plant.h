#pragma once
#include "head.h"
class Zombie;
class Pea;
class Sun;
class Sun : public QGraphicsItem
{
protected:
    int frame;		//�������ʱ��֡��
    bool death;     //��¼�Ƿ񱻵��
    QMovie *movie;
public:
    Sun(int frame, QPointF pos);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int frameNum();
    bool dead();
};

class PlantInfo
{
public:
    int no;	//ֲ����
    QString name;
    int fullhp;
    int atk;
    int atkspeed;
    int cost;
    PlantInfo();
    PlantInfo(const PlantInfo &p);
};
class Plant : public QGraphicsItem
{

protected:
    int frame;		//ֲ�ﱻ��ֲʱ��֡��
    //QPointF pos;	//ֲ������
    PlantInfo info;	//ֲ����Ϣ
    int hp;		//ֲ�ﵱǰ����ֵ
public:
    enum { Type = UserType + 2 };
    int type() const { return Type; }
    Plant(int frame, QPointF pos, PlantInfo info);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;


    bool samePos(const QPointF pos);
    virtual void nextFrame(int currentFrame);	//������һ֡ǰ׼��
    void cut();	//����ֲ��
    void refresh();	//ˢ����ʾ
    int plantNo();	//����ֲ����
    bool clear();	//���ظ�ֲ���Ƿ�ñ�ɾ��
    void attacked(int atk);	//�ܵ�����
    QPointF currentPos();	//���ص�ǰλ��
    int nameLength();		//ֲ�����Ƴ���
};
class PeaShooter : public Plant
{
protected:
    bool shootFlag;	//�Ƿ�÷����㶹
public:
    PeaShooter(int frame, QPointF pos, PlantInfo info) :Plant(frame, pos, info) { shootFlag = false; }
    void nextFrame(int currentFrame);
    virtual Pea* shoot(int currentFrame);
};
class SnowPea : public PeaShooter
{
public:
    SnowPea(int frame, QPointF pos, PlantInfo info) :PeaShooter(frame, pos, info) {}
    Pea* shoot(int currentFrame);
};
class SunFlower : public Plant
{
protected:
    bool sunFlag;
public:
    SunFlower(int frame, QPointF pos, PlantInfo info) :Plant(frame, pos, info) { sunFlag = false; }
    void nextFrame(int currentFrame);
    Sun *produceSun(int currentFrame);
};
class Pea : public QGraphicsItem
{
    enum { Type = UserType + 3 };
protected:
    bool death;
    int no;
    int frame;
    int atk;
    //QPointF pos;
    int speed;
public:
    Pea(int frame,int atk,QPointF startPos,int speed);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    int type() const { return Type; }

    virtual void nextFrame(int currentFrame);
    void move();
    QPointF currentPos();
    bool samePos(const QPointF pos);
    void refresh();
    int attack();
    int peaNo();
    bool dead();
};

class Snow :public Pea
{
public:
    Snow(int frame, int atk, QPointF startPos, int speed) :Pea(frame, atk, startPos, speed) { no = SNOW; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void nextFrame(int currentFrame);
};

class WallNut :public Plant
{
public:
    void nextFrame(int currentFrame) {}
    WallNut(int frame, QPointF pos, PlantInfo info) :Plant(frame, pos, info) {}
};
