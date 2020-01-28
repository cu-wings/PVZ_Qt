#include "gamescene.h"
#include <QGraphicsRectItem>

GameScene::GameScene(QGraphicsScene *parent) :
    QGraphicsScene(parent)
{
    //QGraphicsRectItem *item = new QGraphicsRectItem(100,100,50,50);
    //this->addItem(item);
    //game = new Game;
    shop = new Shop;
    map = new Map;
    info = new Info;

    zombieLine.open("zombieList.txt");
    string tempStr;
    getline(zombieLine, tempStr);
    stringstream tempss(tempStr);
    tempss >> nextLineFrame;
    nextLineFrame += info->frameNum();
    for (int i = 0;i < MAP_LINE;i++)
    {
        tempss >> nextZombies[i];
    }

    //初始化僵尸信息列表
    ifstream ifs("zombie.txt");
    while (!ifs.eof())
    {
        ZombieInfo tempInfo;
        string tempString;
        getline(ifs, tempString);
        stringstream ss(tempString);
        ss >> tempInfo.no >> tempInfo.name >> tempInfo.fullhp >> tempInfo.atk >> tempInfo.atkspeed >> tempInfo.speed >> tempInfo.score;
        zombieInfoList.push_back(tempInfo);
    }
    ifs.close();

}

void GameScene::run()
{

    this->addItem(map);
    this->addItem(shop);
    this->addItem(info);
    shop->start(this);
}

void GameScene::nextFrame()
{

    shop->nextFrame(info->frameNum());
    info->nextFrame();

    createZombie();

    for (int i = 0;i < (int)peaList.size();i++)
    {
        peaList[i]->nextFrame(info->frameNum());
        //击中僵尸
        /*
        int index = hasZombie(map->click(peaList[i]->currentPos()));
        if (index > -1)
        {
            int frozen = 0;
            if (peaList[i]->peaNo() == SNOW)
                frozen = FROZEN;
            zombieList[index]->attacked(peaList[i]->attack(),frozen);
            vector<Pea*>::iterator itera = peaList.begin() + i;
            removeItem(*itera);
            itera = peaList.erase(itera);
            i--;
        }*/
    }

    for (int i = 0;i < (int)plantList.size();i++)
    {
        plantList[i]->nextFrame(info->frameNum());
        Pea* newPea = NULL;
        Sun* newSun = NULL;
        switch (plantList[i]->plantNo())
        {
        case SUNFLOWER:
            newSun = ((SunFlower*)plantList[i])->produceSun(info->frameNum());	//向日葵产出阳光
            if(newSun)
                sunList.push_back(newSun);

            break;
        case PEASHOOTER:
            newPea = ((PeaShooter*)plantList[i])->shoot(info->frameNum());//豌豆射手发射豌豆
            if (newPea)		//发射豌豆
                peaList.push_back(newPea);
            break;
        case SNOWPEA:
            newPea = ((SnowPea*)plantList[i])->shoot(info->frameNum());//豌豆射手发射豌豆
            if (newPea)		//发射豌豆
                peaList.push_back(newPea);
            break;
        default:
            break;
        }
    }

    for (int i = 0;i < (int)zombieList.size();i++)
    {
        zombieList[i]->nextFrame(info->frameNum());
        /*int index = hasPlant(map->click(zombieList[i]->prePos()));
        if (index > -1)//攻击植物
        {
            plantList[index]->attacked(zombieList[i]->eat());
        }
        else
        {
            //移动
            zombieList[i]->move();
            int index = hasPea(zombieList[i]->currentPos());
            if (index > -1)	//触碰豌豆
            {
                int frozen = 0;
                if (peaList[index]->peaNo() == SNOW)
                    frozen = FROZEN;
                zombieList[i]->attacked(peaList[index]->attack(), frozen);
                vector<Pea*>::iterator itera = peaList.begin() + index;
                removeItem(*itera);
                itera = peaList.erase(itera);
            }
        }*/
    }

    clear();
    update();
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    vector<Card> *prevList = shop->cards();
    int chosen = -1;
    for(int i = 0;i < (int)prevList->size(); i++)
    {
        if((*prevList)[i].ifchosen())
            chosen = i;
    }
    QGraphicsScene::mousePressEvent(event);
    vector<Card> *currentShop = shop->cards();
    if(event->button() == Qt::LeftButton)
    {
        for(int i = 0;i < (int)currentShop->size(); i++)
        {
            //如果更改了选择的植物，将原先选中的解除选中
            if((*currentShop)[i].ifchosen() && i != chosen)
            {
                info->clickShop((*currentShop)[i].plantInfo());//现在选中原先未选中，则选择现在
                (*currentShop)[chosen].cancel();//原先选中的需要解除

            }
        }
        click(event->scenePos());
    }
    if(event->button() == Qt::RightButton)
    {
        info->unclick();
        shop->unclick();
    }

    //event->setAccepted(true);
    //setCursor(Qt::ClosedHandCursor);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    info->setPos(event->scenePos());
    update();
}

void GameScene::click(QPointF clickPos)
{
    if(clickPos.x() >= MAP_X_START && clickPos.y() >= MAP_Y_START)
    {
        clickPos = map->click(clickPos);		//获取地图上可种植或移除植物的坐标
        if (clickPos.x() != 0 && clickPos.y() != 0)
        {
            if (info->clickStateKind() == ClickInfo::SHOP)
            {
                plant(clickPos);
            }
            else if (info->clickStateKind() == ClickInfo::CUT)
            {
                cut(clickPos);
            }
        }
    }
}
void GameScene::plant(QPointF clickPos)
{
    PlantInfo newPlantInfo = info->clickPlant();
    if (shop->enoughSun(newPlantInfo.cost))	//如果有足够的的阳光，才能进行种植
    {
        Plant* newPlant = NULL;
        if (maphasPlant(clickPos) > -1)	//如果该位置存在植物，则种植无法进行
        {
            return;
        }

        switch (newPlantInfo.no)
        {
        case SUNFLOWER:
            newPlant = new SunFlower(info->frameNum(), clickPos, newPlantInfo);
            break;
        case PEASHOOTER:
            newPlant = new PeaShooter(info->frameNum(), clickPos, newPlantInfo);
            break;
        case SNOWPEA:
            newPlant = new SnowPea(info->frameNum(), clickPos, newPlantInfo);
            break;
        case WALLNUT:
            newPlant = new WallNut(info->frameNum(), clickPos, newPlantInfo);
            break;
        default:
            break;
        }
        /*
        if (hasZombie(newPlant->currentPos()) > -1)	//如果该位置存在僵尸，则种植无法进行
        {
            return;
        }
        */
        addItem(newPlant);
        plantList.push_back(newPlant);	//将新种植植物加入容器
        shop->sunChange(-newPlantInfo.cost);	//减少阳光数量
        unclick();	//成功种植后消除当前选中
    }
}

void GameScene::unclick()
{
    /*vector<Card> *currentShop = shop->cards();
    for(int i = 0;i < (int)currentShop->size(); i++)
    {
        if((*currentShop)[i].ifchosen())
        {
            (*currentShop)[i].cancel();//原先选中的需要解除
        }
    }*/
    shop->unclick();
    info->unclick();
}

void GameScene::cut(QPointF clickPos)
{
    vector<Plant*>::iterator itera = plantList.begin();
    for (;itera < plantList.end();itera++)
    {
        if (*itera)
        {
            if ((*itera)->pos() == clickPos)
            {
                (*itera)->cut();
                //itera = plantList.erase(itera);
            }
        }
    }
    unclick();
}
int GameScene::maphasPlant(const QPointF pos)
{
    for (int i = 0;i < (int)plantList.size();i++)
    {
        if (plantList[i])
        {
            for (int j = 0;j < MAP_EACH_COL;j++)
            {
                /*if (plantList[i]->samePos(pos))
                {
                    return i;
                }*/
                if(plantList[i]->pos() == pos)
                    return i;
            }
        }
    }
    return -1;
}

void GameScene::createZombie()
{
    if (info->frameNum() == nextLineFrame)
    {
        for (int i = 0;i < MAP_LINE;i++)
        {
            if (nextZombies[i] > 0)
            {
                Zombie* temp = NULL;
                QPointF startPos(MAP_COL * MAP_EACH_COL + ZOMBIE_START_OFFSET + MAP_X_START,
                    (i) * MAP_EACH_LINE + MAP_Y_START);
                switch(nextZombies[i])
                {
                case 1:
                    temp = new Zombie(info->frameNum(), startPos, zombieInfoList[nextZombies[i] - 1]);
                    break;
                case 2:
                    temp = new ConeheadZombie(info->frameNum(), startPos, zombieInfoList[nextZombies[i] - 1]);
                    break;
                }

                addItem(temp);
                zombieList.push_back(temp);
            }
        }
        if (!zombieLine.eof())
        {
            string tempString;
            getline(zombieLine, tempString);
            stringstream ss(tempString);
            ss >> betweenFrame;
            nextLineFrame += betweenFrame;
            for (int i = 0;i < MAP_LINE;i++)
            {
                ss >> nextZombies[i];
            }
        }
        else
        {
            nextLineFrame += betweenFrame;
        }
    }
}

int GameScene::hasZombie(const QPointF pos)
{
    for (int i = 0;i < (int)zombieList.size();i++)
    {
        if (zombieList[i])
        {
            if (zombieList[i]->pos().x() == pos.x())
            {
                return i;
            }
        }
    }
    return -1;
}
int GameScene::hasPlant(const QPointF pos)
{
    for (int i = 0;i < (int)plantList.size();i++)
    {
        if (plantList[i])
        {
            if (plantList[i]->pos().x() == pos.x())
            {
                return i;
            }
        }
    }
    return -1;
}
int GameScene::hasPea(const QPointF pos)
{
    for (int i = 0;i < (int)peaList.size();i++)
    {
        if (peaList[i])
        {
            if (peaList[i]->pos().x() == pos.x())
            {
                return i;
            }
        }
    }
    return -1;
}
void GameScene::clear()
{
    for (int i = 0;i < (int)peaList.size();i++)
    {
        //超出地图后，直接删除
        if (peaList[i]->currentPos().x() > MAP_COL*MAP_EACH_COL + MAP_X_START + EDGE_WIDTH + ZOMBIE_START_OFFSET
                || peaList[i]->dead())
        {
            vector<Pea*>::iterator itera = peaList.begin() + i;
            removeItem(*itera);
            itera = peaList.erase(itera);
            i--;
        }
    }
    for (int i = 0;i < (int)plantList.size();i++)	//删除生命值低于0的植物
    {
        if (plantList[i]->clear())
        {
            vector<Plant*>::iterator itera = plantList.begin() + i;
            removeItem(*itera);
            itera = plantList.erase(itera);
            i--;
        }
    }
    for (int i = 0;i < (int)zombieList.size();i++)	//删除生命值低于0的僵尸
    {
        if (zombieList[i]->clear())
        {
            info->addScore(zombieList[i]->score());	//得分
            vector<Zombie*>::iterator itera = zombieList.begin() + i;
            removeItem(*itera);
            itera = zombieList.erase(itera);
            i--;
        }

    }
    for (int i = 0;i < (int)sunList.size();i++) //删除阳光
    {
        if (sunList[i]->dead())
        {
            shop->sunChange(50);
            vector<Sun*>::iterator itera = sunList.begin() + i;
            removeItem(*itera);
            itera = sunList.erase(itera);
            i--;
        }
        else if(sunList[i]->frameNum() + SUN_DISAPPEAR < info->frameNum())
        {
            vector<Sun*>::iterator itera = sunList.begin() + i;
            removeItem(*itera);
            itera = sunList.erase(itera);
            i--;
        }
    }
}

void GameScene::end()
{
    for (int i = 0;i < (int)zombieList.size();i++)
    {
        if (zombieList[i]->pos().x() <= 5)
        {
            setBackgroundBrush(QPixmap(":/img/ZombiesWon.png"));
            //timer->stop();
        }

    }
}

GameScene::~GameScene()
{

}
