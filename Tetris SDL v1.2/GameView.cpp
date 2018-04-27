


#include "GameView.h"
#include "SDL.h"

tetris::GameView::GameView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks)
	: View(display, surfBlocks)
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