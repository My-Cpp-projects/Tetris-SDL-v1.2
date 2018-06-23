


#include "../../include/factory/FigureFactory.h"
#include "../../include/util/DrawUtil.h"

#include <random>
#include <cmath>

static void createStick(int** figureMatrix)
{
	figureMatrix[1][0] = ::DrawUtil::TILE_RED;
	figureMatrix[1][1] = ::DrawUtil::TILE_RED;
	figureMatrix[1][2] = ::DrawUtil::TILE_RED;
	figureMatrix[1][3] = ::DrawUtil::TILE_RED;
}

static void createBox(int** figureMatrix)
{
	figureMatrix[1][1] = ::DrawUtil::TILE_BLUE;
	figureMatrix[1][2] = ::DrawUtil::TILE_BLUE;
	figureMatrix[2][1] = ::DrawUtil::TILE_BLUE;
	figureMatrix[2][2] = ::DrawUtil::TILE_BLUE;
}

static void createPyramid(int** figureMatrix)
{
	figureMatrix[1][1] = ::DrawUtil::TILE_STEEL;
	figureMatrix[0][2] = ::DrawUtil::TILE_STEEL;
	figureMatrix[1][2] = ::DrawUtil::TILE_STEEL;
	figureMatrix[2][2] = ::DrawUtil::TILE_STEEL;
}

static void createLeftSnake(int** figureMatrix)
{
	figureMatrix[0][1] = ::DrawUtil::TILE_YELLOW;
	figureMatrix[1][1] = ::DrawUtil::TILE_YELLOW;
	figureMatrix[1][2] = ::DrawUtil::TILE_YELLOW;
	figureMatrix[2][2] = ::DrawUtil::TILE_YELLOW;
}

static void createRightSnake(int** figureMatrix)
{
	figureMatrix[2][1] = ::DrawUtil::TILE_GREEN;
	figureMatrix[1][1] = ::DrawUtil::TILE_GREEN;
	figureMatrix[1][2] = ::DrawUtil::TILE_GREEN;
	figureMatrix[0][2] = ::DrawUtil::TILE_GREEN;
}

static void createLeftKnight(int** figureMatrix)
{
	figureMatrix[1][1] = ::DrawUtil::TILE_WHITE;
	figureMatrix[2][1] = ::DrawUtil::TILE_WHITE;
	figureMatrix[2][2] = ::DrawUtil::TILE_WHITE;
	figureMatrix[2][3] = ::DrawUtil::TILE_WHITE;
}

static void createRightKnight(int** figureMatrix)
{
	figureMatrix[2][1] = ::DrawUtil::TILE_PURPLE;
	figureMatrix[1][1] = ::DrawUtil::TILE_PURPLE;
	figureMatrix[1][2] = ::DrawUtil::TILE_PURPLE;
	figureMatrix[1][3] = ::DrawUtil::TILE_PURPLE;
}

// an array of pointers to functions
static void(*figureCreators[tetris::Figure::COUNT])(int**)
{
	createStick,
	createBox,
	createPyramid,
	createLeftSnake,
	createRightSnake,
	createLeftKnight,
	createRightKnight,
};

tetris::Figure* tetris::FigureFactory::createFigure(Figure::FigureType type)
{
	int** figureMatrix = new int*[Figure::FIGURE_WIDTH];

	for (int i = 0; i < Figure::FIGURE_WIDTH; ++i)
	{
		figureMatrix[i] = new int[Figure::FIGURE_HEIGHT];
	}

	for (int i = 0; i < Figure::FIGURE_WIDTH; ++i)
	{
		for (int j = 0; j < Figure::FIGURE_HEIGHT; ++j)
		{
			figureMatrix[i][j] = ::DrawUtil::TILE_NODRAW;
		}
	}

	figureCreators[(int)type](figureMatrix);

	Figure*	newFigure = new Figure(figureMatrix, type);
	return newFigure;
}

tetris::Figure* tetris::FigureFactory::createRandomFigure()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, Figure::COUNT - 1);
	int mean = uniform_dist(e1);

	Figure::FigureType randomEnum = static_cast<Figure::FigureType>(mean);

	return createFigure(randomEnum);
}

