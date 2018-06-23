



#ifndef NEXTFIGUREVIEW_H

#include "View.h"

// forward declaration of BoardData, DrawUtil
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

	NextFigureView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, NextFigureData* data, int x, int y);

public:

	virtual void Draw();

private:

	NextFigureData* mHudData;
};

#endif // !NEXTFIGUREVIEW_H

