



#include "../../include/util/DrawUtil.h"
#include "../../include/view/NextFigureView.h"
#include "../../include/model/NextFigureData.h"


tetris::NextFigureView::NextFigureView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, NextFigureData* data, int x, int y)
	: View(display, surfBlocks, x, y)
	, mHudData(data)
{
}

void tetris::NextFigureView::Draw()
{
	int xmy;
	int ymx;

	// draw the board
	// loop through the positions
	for (xmy = 0; xmy < mHudData->mWidth; ++xmy)
	{
		for (ymx = 0; ymx < mHudData->mHeight; ++ymx)
		{
			::DrawUtil::DrawTile(xmy + mX, ymx + mY, mHudData->mArea[xmy][ymx], getDisplay(), getSurfBlocks());
		}
	}

	// draw next figure
	for (xmy = 0; xmy < mHudData->mNextFigure->FIGURE_WIDTH; ++xmy)
	{
		for (ymx = 0; ymx < mHudData->mNextFigure->FIGURE_HEIGHT; ++ymx)
		{
			if (mHudData->mNextFigure->mFigureMatrix[xmy][ymx] != ::DrawUtil::TILE_NODRAW)
			{
				::DrawUtil::DrawTile(mHudData->mNextFigure->getXCoordinate() + xmy + mX, mHudData->mNextFigure->getYCoordinate() + ymx + mY, mHudData->mNextFigure->mFigureMatrix[xmy][ymx], getDisplay(), getSurfBlocks());
			}
		}
	}

	// Redraw the entire Display
	SDL_Flip(getDisplay());
}
