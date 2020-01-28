#pragma once
#include "head.h"
#include "plant.h"
#include "zombie.h"
class Map : public QGraphicsItem
{
private:
	int line;			//����
	int col;			//����
	int lineEach;		//ÿ�г���
	int colEach;		//ÿ�г���
	int edgeWidth;		//���߿�
    QImage image;       //��ͼͼƬ
public:
    Map();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
	void start();
    QPointF click(QPointF clickPos);	//���ݵ��λ�÷��ص�ͼ�ϵ�ֲ����ֲλ��
	void refresh();		//ˢ�µ�ͼ
};
