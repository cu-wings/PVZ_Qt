#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <time.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QGraphicsSceneEvent>
#include <QDrag>
#include <QMimeData>
#include <QCursor>
#include <QDebug>
#include <QMovie>
using namespace std;
#define FRAME 100
#define MAP_LINE 5
#define MAP_COL 9
#define MAP_EACH_LINE 106
#define MAP_EACH_COL 83
#define SHOP_LINE 3
#define SHOP_COL 4
#define SHOP_EACH_COL 16
#define SHOP_BETWEEN_MAP 2
#define EDGE_WIDTH 1
#define PEA_SPEED 1
#define SUN_MAX 9999
#define SUNFLOWER 1
#define PEASHOOTER 2
#define SNOWPEA 3
#define WALLNUT 4
#define PEA 1
#define SNOW 2
#define ZOMBIE_START_OFFSET 10
#define FROZEN 20
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1000
#define SHOP_WIDTH 446
#define SHOP_HEIGHT 87
#define MAP_X_START 145
#define MAP_Y_START 80
#define SHOP_SUN_X_START 11
#define SHOP_SUN_Y_START 61
#define SHOP_SUN_WIDTH 55
#define SHOP_SUN_HEIGHT 22
#define SHOP_CARD_X_START 76
#define SHOP_CARD_Y_START 7
#define CARD_WIDTH 64
#define CARD_HEIGHT 76
#define SHOP_X_START 200
#define SHOP_Y_START 0
#define CARD_IMG_X_START 5
#define CARD_IMG_Y_START 10
#define PLANT_WIDTH 64
#define PLANT_HEIGHT 80
#define PEA_WIDTH 28
#define SHOVEL_WIDTH 80
#define CARD_IMG_WIDTH 50
#define CARD_IMG_HEIGHT 45
#define SUN_DISAPPEAR 400
class Position
{
public:
	int x;
	int y;
    Position() { x = 0, y = 0; }
	Position(int x, int y) { this->x = x, this->y = y; }
	Position(const Position &p) { x = p.x, y = p.y; }
	Position& operator = (const Position &p) 
	{
		if (this == &p) return *this;
		this->x = p.x, this->y = p.y; 
		return *this; 
	}
};
