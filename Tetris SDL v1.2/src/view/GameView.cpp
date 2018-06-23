


#include "../../include/view/GameView.h"

#include "SDL.h"

tetris::GameView::GameView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks)
	: View(display, surfBlocks, 0, 0)
{
}

void tetris::GameView::Draw()
{
	View::VIEWS::iterator it;

	for(it = getViews()->begin(); it != getViews()->end(); ++it)
	{
		(*it)->Draw();
	}
}