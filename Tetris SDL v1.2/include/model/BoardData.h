


#ifndef BOARDDATA_H
#define BOARDDATA_H

#include "Figure.h"

namespace tetris
{
	struct BoardData;
}

//////////////
// BoardData
//////////////

struct tetris::BoardData
{
	BoardData(int w, int h)
		: mWidth(w)
		, mHeight(h)
	{

	}

	int mWidth;
	int mHeight;

	// contains the colours of every tile
	int** mBoard;

	bool newGame;

	Figure* mFigure;
};


#endif // !BoardData.h

