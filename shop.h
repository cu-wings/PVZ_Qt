#pragma once
#include "head.h"
#include "plant.h"
#include "card.h"
#include "info.h"
#include "shovel.h"
class Shop : public QGraphicsItem
{
private:
    vector<Card> shopList;
    QImage shopImage;
    QImage cardImage;
    Shovel *shovel;
    int sun;	//��Ϸ��ǰ������
public:
	Shop();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    void start(QGraphicsScene *gameScene);
    PlantInfo clickPlant();
    void nextFrame(int frame);
    void unclick();
    int clickKind();
    vector<Card>* cards();
    bool enoughSun(int needSun);	//�жϵ�ǰ�Ƿ����㹻������
    void sunChange(int changeSun);	//�޸���������
};
