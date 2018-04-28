


#include "DrawUtil.h"
#include "BoardView.h"
#include "BoardData.h"


tetris::BoardView::BoardView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, BoardData* data)
	: View(display, surfBlocks)
	, mBoardData(data)
{
}

void tetris::BoardView::Draw()
{
	int xmy;
	int ymx;
	
	// draw the board
	// loop through the positions
	for (xmy = 0; xmy < mBoardData->mWidth; ++xmy)
	{
		for (ymx = 0; ymx < mBoardData->mHeight; ++ymx)
		{
			::DrawUtil::DrawTile(xmy, ymx, mBoardData->mBoard[xmy][ymx], getDisplay(), getSurfBlocks());
		}
	}
	
	// draw moving block
	for (xmy = 0; xmy < mBoardData->mFigure->FIGURE_WIDTH; ++xmy)
	{
		for (ymx = 0; ymx < mBoardData->mFigure->FIGURE_HEIGHT; ++ymx)
		{
			if (mBoardData->mFigure->mFigureMatrix[xmy][ymx] != ::DrawUtil::TILE_NODRAW)
			{
				::DrawUtil::DrawTile(mBoardData->mFigure->getXCoordinate() + xmy, mBoardData->mFigure->getYCoordinate() + ymx, mBoardData->mFigure->mFigureMatrix[xmy][ymx], getDisplay(), getSurfBlocks());
			}
		}
	}  

	// Redraw the entire Display
	SDL_Flip(getDisplay());
}

