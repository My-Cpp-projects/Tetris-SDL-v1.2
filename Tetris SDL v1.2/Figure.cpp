


#include "Figure.h"

tetris::Figure::Figure(int** figureMatrix)
{
	for (int i = 0; i < FIGURE_WIDTH; ++i)
	{
		for (int j = 0; j < FIGURE_HEIGHT; ++j)
		{
			mFigureMatrix[i][j] = figureMatrix[i][j];
		}
	}
}

void tetris::Figure::setCoordinates(int x, int y)
{
	setXCoordinate(x);
	setYCoordinate(y);
}

void tetris::Figure::setXCoordinate(int x)
{
	mX = x;
}

void tetris::Figure::setYCoordinate(int y)
{
	mY = y;
}

int tetris::Figure::getXCoordinate()
{
	return mX;
}

int tetris::Figure::getYCoordinate()
{
	return mY;
}
