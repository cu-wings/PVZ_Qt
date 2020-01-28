#pragma once
#include "head.h"
#include "plant.h"
#include "zombie.h"
class Map : public QGraphicsItem
{
private:
	int line;			//列数
	int col;			//行数
	int lineEach;		//每行长度
	int colEach;		//每列长度
	int edgeWidth;		//边线宽
    QImage image;       //地图图片
public:
    Map();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
	void start();
    QPointF click(QPointF clickPos);	//根据点击位置返回地图上的植物种植位置
	void refresh();		//刷新地图
};
