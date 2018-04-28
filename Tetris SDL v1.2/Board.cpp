



#include <iostream>
#include "DrawUtil.h"
#include "Board.h"
#include "BoardData.h"
#include "Figure.h"
#include "FigureFactory.h"


tetris::Board::Board(int width, int height)
	: mIsInitialized(false)
	, mData(new tetris::BoardData(width, height))
{
	init();
}


void tetris::Board::setWidth(int width)
{
	if (setWidth_NoThrow(width))
	{
		mData->mWidth = width;
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
		mData->mHeight = height;
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
	FigureFactory factory;
	Figure* figure = factory.createFigure(Figure::STICK);

	figure->setCoordinates(mData->mWidth / 2 - 1, 0);
	mData->mFigure = figure;
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
	if (!(isValidSize(mData->mHeight) && isValidSize(mData->mWidth)))
	{
		mIsInitialized = false;
	}
	else
	{
		mData->mBoard = new int*[mData->mWidth];

		for (int i = 0; i < mData->mWidth; ++i)
		{
			mData->mBoard[i] = new int[mData->mHeight];

			for (int j = 0; j < mData->mHeight; ++j)
			{
				mData->mBoard[i][j] = ::DrawUtil::TILE_BLACK;
			}
		}

		mIsInitialized = true;
	}
}

tetris::BoardData* tetris::Board::getBoardData()
{
	return mData;
}
