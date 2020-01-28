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
    void nextFrame();	//������һ֡
    void end();		//��Ϸ��ֹ
    ~GameScene();
    vector<Zombie*> zombieList;
private:
    vector<Plant*> plantList;

    vector<Pea*> peaList;
    vector<ZombieInfo> zombieInfoList;
    vector<Sun*> sunList;
    ifstream zombieLine;	//��¼��ʬ������Ϣ�ļ�
    int betweenFrame;		//��һ������һ��֮���֡��
    int nextLineFrame;		//��һ��������֡��
    int nextZombies[MAP_LINE];	//��һ�ε����Ľ�ʬ
    Shop *shop;
    Map *map;
    Info *info;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void click(QPointF clickPos);	//ѡ�е��λ��
    void unclick();		//ȡ��ѡ��
    void refresh();		//ˢ�½���
    void cut(QPointF clickPos);	//�ڵ��λ�ò���ֲ��
    void plant(QPointF clickPos);	//�ڵ��λ����ֲֲ��
    int hasZombie(const QPointF pos);	//�жϵ�ǰλ���Ƿ��н�ʬ�����з������������򷵻�-1
    int hasPlant(const QPointF pos);	//�жϵ�ǰλ���Ƿ���ֲ����з������������򷵻�-1
    int hasPea(const QPointF pos);	//�жϵ�ǰλ���Ƿ����㶹�����з������������򷵻�-1
    int maphasPlant(const QPointF pos); //�жϵ�ǰ��ͼ���Ƿ���ֲ����з������������򷵻�-1
    void createZombie();	//������ʬ
    void clear();	//���Ӧ��������ֲ���ʬ

};

#endif // GAMESCENE_H
