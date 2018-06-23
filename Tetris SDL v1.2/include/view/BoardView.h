



#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "View.h"

// forward declaration of BoardData
namespace tetris
{
	struct BoardData;
}

namespace tetris
{
	class BoardView;
}

class tetris::BoardView : public View
{

public:

	BoardView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, BoardData* data, int x, int y);

public:

	virtual void Draw();
	
private:

	BoardData* mBoardData;
};

#endif // !BOARDVIEW_H
