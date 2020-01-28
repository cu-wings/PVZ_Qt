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
    int sun;	//游戏当前阳光数
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
    bool enoughSun(int needSun);	//判断当前是否有足够的阳光
    void sunChange(int changeSun);	//修改阳光数量
};
