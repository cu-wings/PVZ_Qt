#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include "head.h"
#include "info.h"
#include "map.h"
#include "zombie.h"
#include "plant.h"
#include "shop.h"
class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QGraphicsScene *parent = 0);
    void run();
    void nextFrame();	//进入下一帧
    void end();		//游戏终止
    ~GameScene();
    vector<Zombie*> zombieList;
private:
    vector<Plant*> plantList;

    vector<Pea*> peaList;
    vector<ZombieInfo> zombieInfoList;
    vector<Sun*> sunList;
    ifstream zombieLine;	//记录僵尸波次信息文件
    int betweenFrame;		//这一波到下一波之间的帧数
    int nextLineFrame;		//下一波到来的帧数
    int nextZombies[MAP_LINE];	//下一次到来的僵尸
    Shop *shop;
    Map *map;
    Info *info;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void click(QPointF clickPos);	//选中点击位置
    void unclick();		//取消选中
    void refresh();		//刷新界面
    void cut(QPointF clickPos);	//在点击位置铲除植物
    void plant(QPointF clickPos);	//在点击位置种植植物
    int hasZombie(const QPointF pos);	//判断当前位置是否有僵尸，若有返回索引，否则返回-1
    int hasPlant(const QPointF pos);	//判断当前位置是否有植物，若有返回索引，否则返回-1
    int hasPea(const QPointF pos);	//判断当前位置是否有豌豆，若有返回索引，否则返回-1
    int maphasPlant(const QPointF pos); //判断当前地图块是否有植物，若有返回索引，否则返回-1
    void createZombie();	//产生僵尸
    void clear();	//清除应该消除的植物、僵尸

};

#endif // GAMESCENE_H
