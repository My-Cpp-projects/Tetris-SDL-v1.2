

#include <stdlib.h>
#include <time.h>
#include "FigureFactory.h"
#include "DrawUtil.h"

tetris::Figure* tetris::FigureFactory::createFigure(Figure::FigureType type)
{
	int** figureMatrix = new int*[Figure::FIGURE_HEIGHT];
	for (int i = 0; i < Figure::FIGURE_HEIGHT; ++i)
	{
		figureMatrix[i] = new int[Figure::FIGURE_WIDTH];
	}

	for (int i = 0; i < Figure::FIGURE_WIDTH; ++i)
	{
		for (int j = 0; j < Figure::FIGURE_HEIGHT; ++j)
		{
			figureMatrix[i][j] = ::DrawUtil::TILE_NODRAW;
		}
	}

	switch (type)
	{
		case tetris::Figure::STICK:
		{
			figureMatrix[1][0] = ::DrawUtil::TILE_RED;
			figureMatrix[1][1] = ::DrawUtil::TILE_RED;
			figureMatrix[1][2] = ::DrawUtil::TILE_RED;
			figureMatrix[1][3] = ::DrawUtil::TILE_RED;

		} break;

		case tetris::Figure::BOX:
		{
			figureMatrix[1][1] = ::DrawUtil::TILE_BLUE;
			figureMatrix[1][2] = ::DrawUtil::TILE_BLUE;
			figureMatrix[2][1] = ::DrawUtil::TILE_BLUE;
			figureMatrix[2][2] = ::DrawUtil::TILE_BLUE;

		} break;

		case tetris::Figure::PYRAMID:
		{
			figureMatrix[1][1] = ::DrawUtil::TILE_STEEL;
			figureMatrix[0][2] = ::DrawUtil::TILE_STEEL;
			figureMatrix[1][2] = ::DrawUtil::TILE_STEEL;
			figureMatrix[2][2] = ::DrawUtil::TILE_STEEL;

		} break;

		case tetris::Figure::LEFT_SNAKE:
		{
			figureMatrix[0][1] = ::DrawUtil::TILE_YELLOW;
			figureMatrix[1][1] = ::DrawUtil::TILE_YELLOW;
			figureMatrix[1][2] = ::DrawUtil::TILE_YELLOW;
			figureMatrix[2][2] = ::DrawUtil::TILE_YELLOW;

		} break;

		case tetris::Figure::RIGHT_SNAKE:
		{
			figureMatrix[2][1] = ::DrawUtil::TILE_GREEN;
			figureMatrix[1][1] = ::DrawUtil::TILE_GREEN;
			figureMatrix[1][2] = ::DrawUtil::TILE_GREEN;
			figureMatrix[0][2] = ::DrawUtil::TILE_GREEN;

		} break;

		case tetris::Figure::LEFT_KNIGHT:
		{
			figureMatrix[1][1] = ::DrawUtil::TILE_WHITE;
			figureMatrix[2][1] = ::DrawUtil::TILE_WHITE;
			figureMatrix[2][2] = ::DrawUtil::TILE_WHITE;
			figureMatrix[2][3] = ::DrawUtil::TILE_WHITE;

		} break;

		case tetris::Figure::RIGHT_KNIGHT:
		{
			figureMatrix[2][1] = ::DrawUtil::TILE_PURPLE;
			figureMatrix[1][1] = ::DrawUtil::TILE_PURPLE;
			figureMatrix[1][2] = ::DrawUtil::TILE_PURPLE;
			figureMatrix[1][3] = ::DrawUtil::TILE_PURPLE;

		} break;

		default:
		{
			throw "Invalid Figure Type";
		} break;
	}

	Figure*	newFigure = new Figure(figureMatrix);
	return newFigure;
}

tetris::Figure* tetris::FigureFactory::createRandomFigure()
{
	srand(time(NULL));
	Figure::FigureType randomEnum = static_cast<Figure::FigureType>(rand() % Figure::MAX_FIGURES);
	return createFigure(randomEnum);
}

