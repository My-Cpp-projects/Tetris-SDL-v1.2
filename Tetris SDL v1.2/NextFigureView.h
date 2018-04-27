



#ifndef NEXTFIGUREVIEW_H
#define NEXTFIGUREVIEW_H

#include "View.h"

namespace tetris
{
	struct NextFigureData;
}

namespace tetris
{
	class NextFigureView;
}

class tetris::NextFigureView : public View
{

public:

	NextFigureView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, NextFigureData* data);

public:

	virtual void Draw();

private:

	NextFigureData* mFigureData;

};

#endif // !NEXTFIGUREVIEW_H
