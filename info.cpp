#include "info.h"
#include "card.h"
#include "shovel.h"
Info::Info()
{
	frame = 0;
	score = 0;

	clickState.kind = ClickInfo::NONE;
	clickState.choosePos = { 0,0 };
    this->setPos(0, 0);
}

int Info::frameNum()
{
	return frame;
}

void Info::nextFrame()
{
	frame++;
    //if (frame % 100 == 0)
        //sun = (sun + 50) % SUN_MAX;
}

void Info::unclick()
{
	clickState.kind = ClickInfo::NONE;
}
QRectF Info::boundingRect() const
{
    return QRectF(0, 0, CARD_WIDTH, CARD_HEIGHT);
}

int Info::clickStateKind()
{
	return clickState.kind;
}

void Info::clickCut()
{
	unclick();
    /*int line = SHOP_LINE;
	int col = SHOP_COL;
	int lineEach = 1;
	int colEach = SHOP_EACH_COL;
	int edgeWidth = EDGE_WIDTH;
	int shopOffset = MAP_LINE*MAP_EACH_LINE + (MAP_LINE + 1)*EDGE_WIDTH + SHOP_BETWEEN_MAP;
    int totalLine = line*lineEach + edgeWidth*(line + 1);
	int totalCol = col*colEach + edgeWidth*(col + 1);
	int lineWidth = lineEach + edgeWidth;
	int colWidth = colEach + edgeWidth;
    */
    //clickState.choosePos = { totalCol + colWidth - 2,shopOffset + edgeWidth };
	clickState.kind = ClickInfo::CUT;
}

void Info::clickShop(PlantInfo plant)
{
	unclick();
	clickState.kind = ClickInfo::SHOP;
	clickState.choosePlant = plant;
    /*QImage image;
    if(clickState.kind == ClickInfo::SHOP)
    {
        image.load(":/img/" + plant.name + ".png");
        QPixmap pix;
        pix.convertFromImage(image);
        QCursor cursor(pix);
        setCursor(cursor);
    }*/

    update();
}

PlantInfo Info::clickPlant()
{
	return clickState.choosePlant;
}
void Info::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QImage image;
    if(clickState.kind == ClickInfo::SHOP)
    {
        image.load(":/img/" +clickState.choosePlant.name + ".png");
        painter->drawImage(boundingRect(), image);
    }
    else if(clickState.kind == ClickInfo::CUT)
    {
        image.load(":/img/shovel.png");
        painter->drawImage(boundingRect(), image);
    }

    update();


    /*for (int i = 0;i < (int)shopList.size();i++)
    {
        QRectF windowRect(SHOP_CARD_X_START + CARD_WIDTH * i, SHOP_CARD_Y_START, CARD_WIDTH, CARD_HEIGHT);
        //gameScene->addItem(&card);
        painter->drawImage(windowRect, cardImage);

    }*/
}
/*
void Info::refresh()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { SHOP_COL*(SHOP_EACH_COL + EDGE_WIDTH) + EDGE_WIDTH + 2,
		SHOP_BETWEEN_MAP + MAP_LINE*(MAP_EACH_LINE + EDGE_WIDTH) + EDGE_WIDTH * 3 + 2 };
	SetConsoleCursorPosition(handle, cursorPos);
	cout << "             ";	//清空可能的原有输出
	SetConsoleCursorPosition(handle, { cursorPos.X,cursorPos.Y + 1 });
	cout << "             ";	//清空可能的原有输出
	SetConsoleCursorPosition(handle, cursorPos);
	cout << "阳光:" << sun;
	SetConsoleCursorPosition(handle, { cursorPos.X,cursorPos.Y + 1 });
	cout << "得分:" << score;
	if (clickState.kind != ClickInfo::NONE)
	{
		cursorPos = { (short)clickState.choosePos.x, (short)clickState.choosePos.y };
		SetConsoleCursorPosition(handle, cursorPos);
		cout << "<-";
	}
}
*/

void Info::addScore(int score)
{
	this->score += score;
}
int Info::scoreNum()
{
	return score;
}

