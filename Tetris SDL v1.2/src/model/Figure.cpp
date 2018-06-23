


#include "../../include/factory/FigureFactory.h"

tetris::Figure::Figure(int** figureMatrix, FigureType type)
	: mType(type)
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
	setCoordinateX(x);
	setCoordinateY(y);
}

void tetris::Figure::setCoordinateX(int x)
{
	mX = x;
}

void tetris::Figure::setCoordinateY(int y)
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
