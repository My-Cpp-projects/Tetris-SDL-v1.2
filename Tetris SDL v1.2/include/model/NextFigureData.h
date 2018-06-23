



#ifndef NEXTFIGUREDATA_H

#include "Figure.h"

namespace tetris
{
	struct NextFigureData;
}

//////////////
// HudData
//////////////

struct tetris::NextFigureData
{
	NextFigureData(int w, int h)
		: mWidth(w)
		, mHeight(h)
	{

	}

	int mWidth;
	int mHeight;

	// contains the colours of every tile
	int** mArea;

	Figure* mNextFigure;
	bool generateNew;
};

#endif // !NEXTFIGUREDATA_H
