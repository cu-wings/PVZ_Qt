#include "shop.h"
Shop::Shop()
{
    //读取植物信息，创建植物商店卡片
    QFile file("plant.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ss(&file);
    int cardStartX = SHOP_X_START + SHOP_CARD_X_START;
    int cardStartY = SHOP_Y_START + SHOP_CARD_Y_START;
    int i = 0;
    while (!ss.atEnd())
	{
		PlantInfo tempInfo;
        ss >> tempInfo.no >> tempInfo.name >> tempInfo.fullhp >> tempInfo.atk >> tempInfo.atkspeed >> tempInfo.cost;
        Card temp(tempInfo, QPointF(cardStartX + i * CARD_WIDTH, cardStartY));
        shopList.push_back(temp);
        i++;
    }
    sun = 999;
    this->setPos(SHOP_X_START, SHOP_Y_START);
    shopImage.load(":/img/shop.png");
    cardImage.load(":/img/card.png");
    shovel = new Shovel(QPointF(SHOP_X_START + SHOP_WIDTH, 0));
    file.close();
}
void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawImage(boundingRect(), shopImage);
    for (int i = 0;i < (int)shopList.size();i++)
    {
        QRectF cardRect(SHOP_CARD_X_START + CARD_WIDTH * i, SHOP_CARD_Y_START, CARD_WIDTH, CARD_HEIGHT);
        //gameScene->addItem(&card);
        painter->drawImage(cardRect, cardImage);
        QRectF costRect(SHOP_CARD_X_START + CARD_IMG_X_START + CARD_WIDTH * i,
                          SHOP_CARD_Y_START+ CARD_IMG_HEIGHT + CARD_IMG_Y_START, CARD_WIDTH, SHOP_SUN_HEIGHT);
        QString cost = QString::number(shopList[i].plantInfo().cost);
        painter->drawText(costRect, cost);
    }
    QString s = QString::number(sun);
    QRectF sunRect(SHOP_SUN_X_START, SHOP_SUN_Y_START, SHOP_SUN_WIDTH, SHOP_SUN_HEIGHT);
    painter->drawText(sunRect, s);
}

bool Shop::enoughSun(int needSun)
{
    return sun >= needSun;
}

void Shop::sunChange(int changeSun)
{
    sun = (sun + changeSun) % SUN_MAX;
}

QRectF Shop::boundingRect() const
{
    return QRectF(0, 0, SHOP_WIDTH, SHOP_HEIGHT);
}
void Shop::start(QGraphicsScene* gameScene)
{

    //将所有卡片添加入场景
    for (int i = 0;i < (int)shopList.size();i++)
	{
        scene()->addItem(&shopList[i]);
    }
    scene()->addItem(shovel);
}

void Shop::nextFrame(int frame)
{
    /*if(clickStateKind == ClickInfo::SHOP)
    {
        //确认当前选中卡片
        int currentChosen = -1;
        for (int i = 0;i < (int)shopList.size();i++)
        {
            if(shopList[i].ifchosen())
            {
                if(info.no != shopList[i].plantInfo().no)
                    currentChosen = i;
            }
        }
        if(currentChosen != -1)
        {
            for (int i = 0;i < (int)shopList.size();i++)
            {
                if(shopList[i].ifchosen() && i != currentChosen)
                {
                    shopList[i].cancel();
                }
            }
        }
    }*/

}

PlantInfo Shop::clickPlant()
{
    for (int i = 0;i < (int)shopList.size();i++)
    {
        if(shopList[i].ifchosen())
        {
            return shopList[i].plantInfo();
        }
    }
}

int Shop::clickKind()
{
    return ClickInfo::SHOP;
}

vector<Card>* Shop::cards()
{
    return &shopList;
}

void Shop::unclick()
{
    for (int i = 0;i < (int)shopList.size();i++)
    {
        if(shopList[i].ifchosen())
        {
            shopList[i].cancel();
        }
    }
    shovel->cancel();
}
