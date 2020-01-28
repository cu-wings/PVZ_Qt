#pragma once
#include "head.h"
class Zombie;
class Pea;
class Sun;
class Sun : public QGraphicsItem
{
protected:
    int frame;		//阳光产生时的帧数
    bool death;     //记录是否被点击
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
    int no;	//植物编号
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
    int frame;		//植物被种植时的帧数
    //QPointF pos;	//植物坐标
    PlantInfo info;	//植物信息
    int hp;		//植物当前生命值
public:
    enum { Type = UserType + 2 };
    int type() const { return Type; }
    Plant(int frame, QPointF pos, PlantInfo info);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;


    bool samePos(const QPointF pos);
    virtual void nextFrame(int currentFrame);	//进入下一帧前准备
    void cut();	//铲除植物
    void refresh();	//刷新显示
    int plantNo();	//返回植物编号
    bool clear();	//返回该植物是否该被删除
    void attacked(int atk);	//受到攻击
    QPointF currentPos();	//返回当前位置
    int nameLength();		//植物名称长度
};
class PeaShooter : public Plant
{
protected:
    bool shootFlag;	//是否该发射豌豆
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
