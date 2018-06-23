



#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"

namespace tetris
{
	class GameView;
}

class tetris::GameView : public View
{

public:

	GameView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks);

public:

	virtual void Draw();
};

#endif // !GAMEVIEW_H
