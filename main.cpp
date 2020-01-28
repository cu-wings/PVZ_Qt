#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsView>
//#include <QGraphicsScene>
#include "gamescene.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;
    game.run();
    return a.exec();
}
