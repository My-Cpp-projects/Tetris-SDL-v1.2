


#include "NextFigureView.h"
#include "NextFigureData.h"
#include "DrawUtil.h"


void tetris::NextFigureView::Draw()
{
	int xmy;
	int ymx;

	// draw preview block
	for (xmy = 0; xmy < 4; ++xmy)
	{
		for (ymx = 0; ymx < 4; ++ymx)
		{
			if (mFigureData->mFigure.size[xmy][ymx] != ::DrawUtil::TILE_NODRAW)
			{
				::DrawUtil::DrawTile(mData->mFigure->getXCoordinate() + xmy, mData->mFigure->getYCoordinate() + ymx, mData->mFigure->mFigureMatrix[xmy][ymx], getDisplay(), getSurfBlocks());
			}
		}
	}

	// Redraw the entire Display
	SDL_Flip(getDisplay());
}