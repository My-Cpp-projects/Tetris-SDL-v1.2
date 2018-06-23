



#include "../../include/util/DrawUtil.h"
#include "../../include/model/Board.h"
#include "../../include/model/BoardData.h"
#include "../../include/model/Figure.h"
#include "../../include/factory/FigureFactory.h"

#include <iostream>

tetris::Board::Board(int width, int height)
	: mIsInitialized(false)
	, mBoardData(new BoardData(width, height))
{
	init();
	startNewGame(true);
}


void tetris::Board::setWidth(int width)
{
	if (setWidth_NoThrow(width))
	{
		mBoardData->mWidth = width;
	}
	else
	{
		throw std::invalid_argument("Width can't be negative or 0");
	}
}

void tetris::Board::setHeight(int height)
{
	if (setHeight_NoThrow(height))
	{
		mBoardData->mHeight = height;
	}
	else
	{
		throw std::invalid_argument("Height can't be negative or 0");
	}
}

bool tetris::Board::isValidSize(int number)
{
	bool retVal = true;

	if (number <= 0)
	{
		retVal = false;
	}
	
	return retVal;
}

void tetris::Board::start()
{
	if (isNewGame())
	{
		clearBoard();

		// create new figure
		FigureFactory factory;
		Figure* figure = factory.createRandomFigure();

		figure->setCoordinates(mBoardData->mWidth / 2 - 1, 0);
		mBoardData->mFigure = figure;

		// new game is already started
		startNewGame(false);
	}
}


void tetris::Board::startNewGame(bool start)
{
	mBoardData->newGame = start;
}

bool tetris::Board::isNewGame()
{
	return mBoardData->newGame;
}

tetris::BoardData* tetris::Board::getBoardData()
{
	return mBoardData;
}

void tetris::Board::clearBoard()
{
	// clear board to black
	for (int i = 0; i < mBoardData->mWidth; ++i)
	{
		for (int j = 0; j < mBoardData->mHeight; ++j)
		{
			mBoardData->mBoard[i][j] = ::DrawUtil::TILE_BLACK;
		}
	}
}

///////////////////////////////////////////////
// PRIVATE FUNCTIONS
///////////////////////////////////////////////

bool tetris::Board::setWidth_NoThrow(int width)
{
	if (width <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool tetris::Board::setHeight_NoThrow(int height)
{
	if (height <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void tetris::Board::init()
{
	if (!(isValidSize(mBoardData->mHeight) && isValidSize(mBoardData->mWidth)))
	{
		mIsInitialized = false;
	}
	else
	{
		mBoardData->mBoard = new int*[mBoardData->mWidth];

		for (int i = 0; i < mBoardData->mWidth; ++i)
		{
			mBoardData->mBoard[i] = new int[mBoardData->mHeight];

			for (int j = 0; j < mBoardData->mHeight; ++j)
			{
				mBoardData->mBoard[i][j] = ::DrawUtil::TILE_BLACK;
			}
		}

		mIsInitialized = true;
	}
}

