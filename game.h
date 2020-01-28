#pragma once

#include "gamescene.h"
class Game
{
private:
    GameScene *gameScene;
    QGraphicsView *view;
    QTimer *timer;

public:
	Game();

	void run();	//ÓÎÏ·Ö´ÐÐ
};
