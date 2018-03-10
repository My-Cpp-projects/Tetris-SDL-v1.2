



#include "GameController.h"
#include <SDL.h>
#include <iostream>

bool GameController::GameInit()
{
	util.surfBlocks = SDL_LoadBMP("blocks.bmp");

	if (!util.surfBlocks)
	{
		std::cout << "GameInit > File not Found: blocks.bmp" << std::endl;
		return false;
	}

	NewGame();

	return true; // return success
}

void GameController::GameLoop()
{
	// Uint32 SDL_GetTicks(void) --- Use this function to get the number of milliseconds since the SDL library initialization.
	if ((SDL_GetTicks() - start_time) > 1000)
	{
		Move(0, 1);
		start_time = SDL_GetTicks();
	}
}

void GameController::GameDone()
{
	// Free all the Surfaces we created
	SDL_FreeSurface(util.Display);
	SDL_FreeSurface(util.surfBlocks);

	// Shut down SDL
	SDL_Quit();
}

void GameController::NewGame()
{
	start_time = SDL_GetTicks();
	GAMESTARTED = false;

	// start out the map
	for (int x = 0; x < MAPWIDTH; ++x)
	{
		for (int y = 0; y < MAPHEIGHT + 1; ++y)
		{
			if (y == MAPHEIGHT) // makes Y-collision easier.
			{
				Map[x][y] = TILEGREY;
			}
			else
			{
				Map[x][y] = TILEBLACK;
			}
		}
	}

	NewBlock();
	DrawMap();
}

void GameController::OnEvent()
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

					case SDLK_DOWN:
					{
						moveDirectionY = 1;

					} break;

					case SDLK_UP:
					{
						rotate = true;
					} break;

					case SDLK_LEFT:
					{
						moveDirectionX = -1;
					} break;

					case SDLK_RIGHT:
					{
						moveDirectionX = 1;
					} break;
				}
			} break;

			// when the pressed key is released we need to stop moving at that direction
			case SDL_KEYUP:	// A key has been released
			{
				int Sym = Event.key.keysym.sym;

				switch (Sym)
				{
					case SDLK_DOWN:
					{
						if (moveDirectionY > 0)
						{
							moveDirectionY = 0;
						}
					} break;

					case SDLK_UP:
					{
						if (rotate)
						{
							rotate = false;
						}
					} break;

					case SDLK_LEFT:
					{
						if (moveDirectionX < 0)
						{
							moveDirectionX = 0;
						}
					} break;

					case SDLK_RIGHT:
					{
						if (moveDirectionX > 0)
						{
							moveDirectionX = 0;
						}
					} break;
				}
			} break;
		}
	}

	// regulate the speed
	if ((SDL_GetTicks() - press_time) > 50)
	{
		Move(moveDirectionX, 0);
		Move(0, moveDirectionY);

		if (rotate)
		{
			RotateBlock();
		}

		press_time = SDL_GetTicks();
	}
}

