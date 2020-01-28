#pragma once
#include "head.h"

class Plant;
class ZombieInfo
{
public:
	int no;	//僵尸编号
	string name;
	int fullhp;
	int atk;
	int atkspeed;
	int speed;
	int score;
};
class Zombie : public QGraphicsItem
{

protected:
	int frame;	//僵尸出现帧
    //Position pos;
    QMovie *movie;
	ZombieInfo info;	//僵尸信息
	int hp;
	bool moveFlag;	//移动指示
	bool atkFlag;	//攻击指示
	bool stop;	//僵尸是否在移动
	int frozenFrame;	//从冻结中恢复所需的帧数
	int startmoveFrame;	//开始移动帧
	int startatkFrame;	//开始攻击帧
public:
    enum { Type = UserType + 1 };
    Zombie(int frame, QPointF startPos, ZombieInfo info);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    int type() const { return Type; }

	void nextFrame(int currentFrame);
	void move();
	int eat();	//返回僵尸攻击力
    bool samePos(const QPointF pos);
    QPointF prePos();	//返回僵尸面前的坐标
    QPointF currentPos();
	void attacked(int atk,int frozen);
	void refresh();
	bool clear();	//返回是否删除该僵尸
	int score();	//返回僵尸得分
};
class ConeheadZombie :public Zombie
{
    bool cone;
public:
    ConeheadZombie(int frame, QPointF startPos, ZombieInfo info) :Zombie(frame, startPos, info) { cone = true; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
