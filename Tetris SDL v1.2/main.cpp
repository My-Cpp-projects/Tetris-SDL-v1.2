


#include "SDL.h"
#include <iostream>

#include "Board.h"
#include "BoardView.h"
#include "GameView.h"

#define WWIDTH		288									// Width of Window
#define WHEIGHT		480									// Height of Window
#define WBIT		16									// 16-bit colors
#define WFLAGS		SDL_HWSURFACE | SDL_DOUBLEBUF		// Set up for Video Hardware and Double Buffering
#define WINDOWTITLE "A Falling Block Game!"




SDL_Surface* display;	// Our main display surface
SDL_Surface* surfBlocks; // used to read from bmp


void GameDone();
void OnEvent();
bool GAMERUNNING = true;

int main(int argc, char *args[])
{

	atexit(GameDone);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "OnInit > Cannot Initialize SDL Systems: " << SDL_GetError() << std::endl;
		return 0;
	}

	display = SDL_SetVideoMode(WWIDTH, WHEIGHT, WBIT, WFLAGS);

	if (!display)
	{
		std::cout << "OnInit > Cannot set Video Mode:" << SDL_GetError() << std::endl;
		return 0;
	}

	surfBlocks = SDL_LoadBMP("blocks.bmp");

	if (!surfBlocks)
	{
		std::cout << "GameInit > File not Found: blocks.bmp" << std::endl;
		return false;
	}

	SDL_WM_SetCaption(WINDOWTITLE, WINDOWTITLE);

	// board size in tiles
	tetris::Board board(18, 30);

	tetris::BoardView boardView(display, surfBlocks, board.getBoardData());
	tetris::GameView gameView(display, surfBlocks);

	gameView.addChild(&boardView);
	
	double start_time = SDL_GetTicks();

	// create ONE figure
	board.start();

	while (GAMERUNNING)
	{
		OnEvent();

		if ((SDL_GetTicks() - start_time) > 1000)
		{
			//Move(0, 1);
			start_time = SDL_GetTicks();
		}
		
		gameView.Draw();
	}

	return 0;
}

void GameDone()
{
	// Free all the Surfaces we created
	SDL_FreeSurface(display);
	SDL_FreeSurface(surfBlocks);

	// Shut down SDL
	SDL_Quit();
}

void OnEvent()
{
	// used to regulate direction.
	// static because the function is called everytime and we dont need to loose previous values
	static int moveDirectionY = 0;
	static int moveDirectionX = 0;
	static bool rotate = false;

	// SDL_Event --- A union that contains structures for the different event types.
	SDL_Event Event;

	// int SDL_PollEvent(SDL_Event* event) --- Use this function to poll for currently pending events.
	//										   Returns 1 if there is a pending event or 0 if there are none available.
	//
	//===  Event loop ===//
	// Grab any events in the queue
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
			case SDL_QUIT:		// Found a quit event
			{
				GAMERUNNING = false;
			} break;

			// !!! In SDL 1.2 (may not apply to new versions) Keyboard events only take place when a keys state changes from being unpressed to pressed, and vice versa. !!!
			// More info here: ( https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html )
			case SDL_KEYDOWN:	// A key has been pressed
			{
				// key --- A structure that contains keyboard button event information. The information on what key was pressed or released is in the keysym member.
				// keysym --- A structure that contains key information used in key events.
				// sym --- The SDL virtual key representation.
				int Sym = Event.key.keysym.sym;

				switch (Sym)
				{
					case SDLK_ESCAPE:
					{
						GAMERUNNING = false;
					} break;

	//				case SDLK_DOWN:
	//				{
	//					moveDirectionY = 1;

	//				} break;

	//				case SDLK_UP:
	//				{
	//					rotate = true;
	//				} break;

	//				case SDLK_LEFT:
	//				{
	//					moveDirectionX = -1;
	//				} break;

	//				case SDLK_RIGHT:
	//				{
	//					moveDirectionX = 1;
	//				} break;
				}
	//		} break;

	//		// when the pressed key is released we need to stop moving at that direction
	//		case SDL_KEYUP:	// A key has been released
	//		{
	//			int Sym = Event.key.keysym.sym;

	//			switch (Sym)
	//			{
	//				case SDLK_DOWN:
	//				{
	//					if (moveDirectionY > 0)
	//					{
	//						moveDirectionY = 0;
	//					}
	//				} break;

	//				case SDLK_UP:
	//				{
	//					if (rotate)
	//					{
	//						rotate = false;
	//					}
	//				} break;

	//				case SDLK_LEFT:
	//				{
	//					if (moveDirectionX < 0)
	//					{
	//						moveDirectionX = 0;
	//					}
	//				} break;

	//				case SDLK_RIGHT:
	//				{
	//					if (moveDirectionX > 0)
	//					{
	//						moveDirectionX = 0;
	//					}
	//				} break;
	//			}
	//		} break;
		}
	}

	//// regulate the speed
	//if ((SDL_GetTicks() - press_time) > 50)
	//{
	//	Move(moveDirectionX, 0);
	//	Move(0, moveDirectionY);

	//	if (rotate)
	//	{
	//		RotateBlock();
	//	}

	//	press_time = SDL_GetTicks();
	}
}

