


#include "DrawUtil.h"
#include "BoardView.h"
#include "BoardData.h"

tetris::BoardView::BoardView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, BoardData* data)
	: View(display, surfBlocks)
	, mData(data)
{
}

void tetris::BoardView::Draw()
{
	int xmy;
	int ymx;
	
	// draw the board
	// loop through the positions
	for (xmy = 0; xmy < mData->mWidth; ++xmy)
	{
		for (ymx = 0; ymx < mData->mHeight; ++ymx)
		{
			::DrawUtil::DrawTile(xmy, ymx, mData->mBoard[xmy][ymx], getDisplay(), getSurfBlocks());
		}
	}
	
	// draw moving block
	for (xmy = 0; xmy < mData->mFigure->FIGURE_WIDTH; ++xmy)
	{
		for (ymx = 0; ymx < mData->mFigure->FIGURE_HEIGHT; ++ymx)
		{
			if (mData->mFigure->mFigureMatrix[xmy][ymx] != ::DrawUtil::TILE_NODRAW)
			{
				::DrawUtil::DrawTile(mData->mFigure->getXCoordinate() + xmy, mData->mFigure->getYCoordinate() + ymx, mData->mFigure->mFigureMatrix[xmy][ymx], getDisplay(), getSurfBlocks());
			}
		}
	}  

	// Redraw the entire Display
	SDL_Flip(getDisplay());
}

