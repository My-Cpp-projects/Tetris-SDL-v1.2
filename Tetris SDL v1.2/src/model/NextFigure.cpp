



#include "../../include/util/DrawUtil.h"
#include "../../include/model/NextFigure.h"
#include "../../include/model/NextFigureData.h"
#include "../../include/model/Figure.h"
#include "../../include/factory/FigureFactory.h"

#include <iostream>

tetris::NextFigure::NextFigure(int width, int height)
	: mIsInitialized(false)
	, mNextFigureData(new tetris::NextFigureData(width, height))
{
	init();
	generateNewFigure(true);
}

void tetris::NextFigure::setWidth(int width)
{
	if (setWidth_NoThrow(width))
	{
		mNextFigureData->mWidth = width;
	}
	else
	{
		throw std::invalid_argument("Width can't be negative or 0");
	}
}

void tetris::NextFigure::setHeight(int height)
{
	if (setHeight_NoThrow(height))
	{
		mNextFigureData->mHeight = height;
	}
	else
	{
		throw std::invalid_argument("Height can't be negative or 0");
	}
}

bool tetris::NextFigure::isValidSize(int number)
{
	bool retVal = true;

	if (number <= 0)
	{
		retVal = false;
	}

	return retVal;
}

void tetris::NextFigure::start()
{
	if (isNewFigure())
	{
		FigureFactory factory;
		Figure* figure = factory.createRandomFigure();

		figure->setCoordinates(mNextFigureData->mWidth / 2 - 1, 0);
		mNextFigureData->mNextFigure = figure;

		generateNewFigure(false);
	}
}

void tetris::NextFigure::generateNewFigure(bool generate)
{
	mNextFigureData->generateNew = generate;
}

bool tetris::NextFigure::isNewFigure()
{
	return mNextFigureData->generateNew;
}

///////////////////////////////////////////////
// PRIVATE FUNCTIONS
///////////////////////////////////////////////

bool tetris::NextFigure::setWidth_NoThrow(int width)
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

bool tetris::NextFigure::setHeight_NoThrow(int height)
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

void tetris::NextFigure::init()
{
	if (!(isValidSize(mNextFigureData->mHeight) && isValidSize(mNextFigureData->mWidth)))
	{
		mIsInitialized = false;
	}
	else
	{
		mNextFigureData->mArea = new int*[mNextFigureData->mWidth];

		for (int i = 0; i < mNextFigureData->mWidth; ++i)
		{
			mNextFigureData->mArea[i] = new int[mNextFigureData->mHeight];

			for (int j = 0; j < mNextFigureData->mHeight; ++j)
			{
				mNextFigureData->mArea[i][j] = ::DrawUtil::TILE_GREY;
			}
		}

		mIsInitialized = true;
	}
}

tetris::NextFigureData* tetris::NextFigure::getNextFigureData()
{
	return mNextFigureData;
}
