#include "game.h"
#include "zombie.h"
Game::Game()
{


}
void Game::run()
{
    gameScene = new GameScene();  //³¡¾°
    view = new QGraphicsView; //ÊÓÍ¼
    timer = new QTimer;
    gameScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    gameScene->run();

    view->setScene(gameScene);
    view->setMouseTracking(true);
    QObject::connect(timer, &QTimer::timeout, gameScene, &QGraphicsScene::advance);
    QObject::connect(timer, &QTimer::timeout, gameScene, &GameScene::nextFrame);
    //QObject::connect(timer, &QTimer::timeout, gameScene, &GameScene::end);
    timer->start(50);

    view->show();

}




/*

void Game::refresh()
{

	map.refresh();
	for (int i = 0;i < (int)plantList.size();i++)
		plantList[i]->refresh();
	for (int i = 0;i < (int)peaList.size();i++)
		peaList[i]->refresh();
	for (int i = 0;i < (int)zombieList.size();i++)
		zombieList[i]->refresh();
	info.refresh();
}



*/
