#pragma once
#include "head.h"
#include "plant.h"
class ClickInfo
{
public:
	enum { NONE, SHOP, CUT } kind;
	PlantInfo choosePlant;	//选中的植物类信息
	Position choosePos;	//箭头坐标
};
class Info  : public QGraphicsItem
{
private:
	int frame;	//游戏当前帧数
	int score;	//游戏当前分数

	ClickInfo clickState;	//当前选中状态
public:
	Info();
    enum { Type = UserType + 4 };
    int type() const { return Type; }
    void clickShop(PlantInfo plant);//点击商店购买植物
	void clickCut(); //点击铲除植物
	int frameNum();	//返回当前游戏帧数
	void nextFrame();	//下一帧
	void unclick();		//取消选中
	int clickStateKind();	//返回选中的种类
    PlantInfo clickPlant();	//返回点击的植物类信息
	void refresh();		//更新信息界面

	void addScore(int score);		//增加分数
	int scoreNum();		//返回当前分数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};
