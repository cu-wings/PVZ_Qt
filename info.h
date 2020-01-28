#pragma once
#include "head.h"
#include "plant.h"
class ClickInfo
{
public:
	enum { NONE, SHOP, CUT } kind;
	PlantInfo choosePlant;	//ѡ�е�ֲ������Ϣ
	Position choosePos;	//��ͷ����
};
class Info  : public QGraphicsItem
{
private:
	int frame;	//��Ϸ��ǰ֡��
	int score;	//��Ϸ��ǰ����

	ClickInfo clickState;	//��ǰѡ��״̬
public:
	Info();
    enum { Type = UserType + 4 };
    int type() const { return Type; }
    void clickShop(PlantInfo plant);//����̵깺��ֲ��
	void clickCut(); //�������ֲ��
	int frameNum();	//���ص�ǰ��Ϸ֡��
	void nextFrame();	//��һ֡
	void unclick();		//ȡ��ѡ��
	int clickStateKind();	//����ѡ�е�����
    PlantInfo clickPlant();	//���ص����ֲ������Ϣ
	void refresh();		//������Ϣ����

	void addScore(int score);		//���ӷ���
	int scoreNum();		//���ص�ǰ����
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};
