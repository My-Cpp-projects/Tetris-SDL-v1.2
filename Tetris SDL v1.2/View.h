



#ifndef VIEW_H
#define VIEW_H

#include "AbstractView.h"
#include "SDL.h"
#include <vector>

namespace tetris
{
	class View;
}

class tetris::View : public UI::AbstractView
{

public:

	typedef std::vector<View*> VIEWS;

	typedef SDL_Surface* DISPLAY_REF;
	typedef SDL_Surface* SURF_BLOCKS_REF;

public:

	View(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks)
		: mDisplay(display)
		, mSurfBlocks(surfBlocks)
	{

	}

public:

	virtual void addChild(View* childView)
	{
		mViews.push_back(childView);
	}

	VIEWS* getViews()
	{
		return &mViews;
	}

	DISPLAY_REF getDisplay()
	{
		return mDisplay;
	}

	SURF_BLOCKS_REF getSurfBlocks()
	{
		return mSurfBlocks;
	}

private:

	VIEWS mViews;
	DISPLAY_REF mDisplay;
	SURF_BLOCKS_REF mSurfBlocks;
};

#endif // !VIEW_H

