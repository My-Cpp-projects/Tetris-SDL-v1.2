



#ifndef NEXTFIGUREDATA_H
#define NEXTFIGUREDATA_H

#include "Figure.h"

namespace tetris
{
	struct NextFigureData;
}

struct tetris::NextFigureData
{
	Figure* mFigure;
};

#endif // !NEXTFIGUREDATA_H
