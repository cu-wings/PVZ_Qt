#pragma once
#include "head.h"

class Plant;
class ZombieInfo
{
public:
	int no;	//��ʬ���
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
	int frame;	//��ʬ����֡
    //Position pos;
    QMovie *movie;
	ZombieInfo info;	//��ʬ��Ϣ
	int hp;
	bool moveFlag;	//�ƶ�ָʾ
	bool atkFlag;	//����ָʾ
	bool stop;	//��ʬ�Ƿ����ƶ�
	int frozenFrame;	//�Ӷ����лָ������֡��
	int startmoveFrame;	//��ʼ�ƶ�֡
	int startatkFrame;	//��ʼ����֡
public:
    enum { Type = UserType + 1 };
    Zombie(int frame, QPointF startPos, ZombieInfo info);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    int type() const { return Type; }

	void nextFrame(int currentFrame);
	void move();
	int eat();	//���ؽ�ʬ������
    bool samePos(const QPointF pos);
    QPointF prePos();	//���ؽ�ʬ��ǰ������
    QPointF currentPos();
	void attacked(int atk,int frozen);
	void refresh();
	bool clear();	//�����Ƿ�ɾ���ý�ʬ
	int score();	//���ؽ�ʬ�÷�
};
class ConeheadZombie :public Zombie
{
    bool cone;
public:
    ConeheadZombie(int frame, QPointF startPos, ZombieInfo info) :Zombie(frame, startPos, info) { cone = true; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
