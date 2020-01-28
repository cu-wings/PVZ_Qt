#include "map.h"
Map::Map()
{
	line = MAP_LINE;
	col = MAP_COL;
	lineEach = MAP_EACH_LINE;
	colEach = MAP_EACH_COL;
	edgeWidth = EDGE_WIDTH;
    this->setPos(0, 0);
    image.load(":/img/background.jpg");
}
void Map::start()
{
    /*HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 0,0 };
	int totalLine = line*lineEach + edgeWidth*(line + 1);
	int totalCol = col*colEach + edgeWidth*(col + 1);
	int lineWidth = lineEach + edgeWidth;
	int colWidth = colEach + edgeWidth;
	for (int i = 0;i < totalLine;i++)
	{
		for (int j = 0;j < totalCol;j++)
		{
			if ((i % lineWidth == 0) ||  (j % colWidth == 0 && i%lineWidth == 1))
			{
				cursorPos = { (short)j,(short)i };
				SetConsoleCursorPosition(handle, cursorPos);
				cout << "#";
			}
		}
    }*/
}
void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QRectF windowRect(100, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    painter->drawImage(boundingRect(), image, windowRect);
    //painter->drawText(windowRect,"12345");
}
QRectF Map::boundingRect() const
{
    return QRectF(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
QPointF Map::click(QPointF clickPos)
{
    int lineWidth = MAP_EACH_LINE;
    int colWidth = MAP_EACH_COL;
    int startX = MAP_X_START;
    int startY = MAP_Y_START;
    int line = ((int)clickPos.y() - startY) / lineWidth;
    int col = ((int)clickPos.x() - startX) / colWidth;
    if (line < MAP_LINE && col < MAP_COL)
	{
        clickPos.setY(line*lineWidth + startY);
        clickPos.setX(col*colWidth + startX);
	}
    else
    {
        clickPos.setY(0);
        clickPos.setX(0);
    }
	return clickPos;
}

void Map::refresh()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 0,0 };
	int totalLine = line*lineEach + edgeWidth*(line + 1);
	int totalCol = col*colEach + edgeWidth*(col + 1);
	int lineWidth = lineEach + edgeWidth;
	int colWidth = colEach + edgeWidth;
	for (int i = 0;i < totalLine;i++)
	{
		for (int j = 0;j < totalCol;j++)
		{
			if ((i % lineWidth == 0) || (j % colWidth == 0 && i%lineWidth ==1))
			{
				cursorPos = { (short)j,(short)i };
				SetConsoleCursorPosition(handle, cursorPos);
				cout << "#";
			}
		}
	}
}
