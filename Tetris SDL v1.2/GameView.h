



#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "SDL.h"
#include "View.h"
#include <vector>

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
