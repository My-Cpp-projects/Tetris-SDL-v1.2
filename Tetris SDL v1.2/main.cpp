


//=============================================================================
// FALLING BLOCK GAME!
// main.cpp
// Needed for all the SDL stuff
#include <SDL.h>
// need this for srand and rand
#include <stdlib.h>
// Used for Error checking
#include <iostream>

//=============================================================================
#define WWIDTH		288									// Width of Window
#define WHEIGHT		480									// Height of Window
#define WBIT		16									// 16-bit colors
#define WFLAGS		SDL_HWSURFACE | SDL_DOUBLEBUF		// Set up for Video Hardware and Double Buffering

// let's give our window a title...er caption.
#define WINDOWTITLE "A Falling Block Game!"

//=============================================================================
// since we're using square blocks, let's only use a single size.
const int TILESIZE = 16;

// now for the map...
const int MAPWIDTH = 10;
const int MAPHEIGHT = 30;
const int GREY = 8;

const int TILENODRAW = -1;
const int TILEBLACK = 0;
const int TILEGREY = 1;
const int TILEBLUE = 2;
const int TILERED = 3;
const int TILEGREEN = 4;
const int TILEYELLOW = 5;
const int TILEWHITE = 6;
const int TILESTEEL = 7;
const int TILEPURPLE = 8;

//=============================================================================
bool GameInit(); // game initialization function
void GameLoop(); // where the game actually takes place
void GameDone(); // clean up! 
void DrawTile(int x, int y, int tile); // coordinates & tile type
void DrawMap(); // draw the whole map.. render function, basically
void NewBlock(); // create a new block!
void RotateBlock(); // rotate a block.. if you can!
void Move(int x, int y); // coordinates to move.
int CollisionTest(int nx, int ny); // test collision of blocks
void RemoveRow(int row); // remove a row.. that would be the 'x'.
void NewGame(); // make a new game!

// Blitting --- Basically it means copying the image from one surface to another
// Makes it easier to Blit a Surface to another Surface
void Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src);
void Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src, int SrcX, int SrcY, int SrcW, int SrcH);

//-----------------------------------------------------------------------------
// SDL_Surface --- A structure that contains a collection of pixels used in software blitting.
//				   SDL_Surface's represent areas of "graphical" memory, memory that can be drawn to.
SDL_Surface* Display;	// Our main display surface

//-----------------------------------------------------------------------------
int Map[MAPWIDTH][MAPHEIGHT + 1]; // the game map!

//-----------------------------------------------------------------------------
struct Piece
{
	int size[4][4];
	int x;
	int y;
};

Piece sPrePiece; // preview piece.
Piece sPiece; // the 's' prefixes indicate this is a 'structure'

//-----------------------------------------------------------------------------
double start_time;  // used in timing
double press_time; // used to regulate the speed when a key is pressed
bool GAMESTARTED = false; // used by NewBlock()

//-----------------------------------------------------------------------------
SDL_Surface* surfBlocks;

bool GAMERUNNING = true;

//=============================================================================
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

//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	// if function name is not followed with () like here, then the name of function evaluates as its adress
	//
	// int atexit (void (*func)(void)) noexcept;
	// The function pointed by func is automatically called without arguments when the program terminates normally.
	//
	// Make sure when we are done we clean up
	atexit(GameDone);

	//===  Start SDL Routines  ===//
	//
	// SDL_Init(Uint32 flags) --- Use this function to initialize the SDL library. This must be called before using most other SDL functions.
	// SDL_INIT_VIDEO --- Video subsystem; automatically initializes the events subsystem
	//
	// Start up just the Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "OnInit > Cannot Initialize SDL Systems: " << SDL_GetError() << std::endl;
		return 0;
	}

	//===  Create a video surface  ===//
	//
	// SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags) --- Set up a video mode with the specified width, height and bits-per-pixel.
	//
	// Create the Window
	Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, WBIT, WFLAGS);

	if (!Display)
	{
		std::cout << "OnInit > Cannot set Video Mode:" << SDL_GetError() << std::endl;
		return 0;
	}

	//===  Window Stuff  ===//
	//
	// SDL_WM_SetCaption --- Sets the window tile and icon name.
	//
	// Set the Window Caption
	SDL_WM_SetCaption(WINDOWTITLE, WINDOWTITLE);

	// if program initialization failed, then return with 0
	if (!GameInit())
	{
		std::cout << "OnInit > Game Init failed!" << std::endl;
		return 0;
	}

	// Main game loop
	while (GAMERUNNING)
	{
		OnEvent();

		GameLoop();
		DrawMap();
	}

	return 1;
}

//-----------------------------------------------------------------------------
bool GameInit()
{
	surfBlocks = SDL_LoadBMP("blocks.bmp");

	if (!surfBlocks)
	{
		std::cout << "GameInit > File not Found: blocks.bmp" << std::endl;
		return false;
	}

	NewGame();

	return(true); // return success
}

//-----------------------------------------------------------------------------
void GameDone()
{
	// Free all the Surfaces we created
	SDL_FreeSurface(Display);
	SDL_FreeSurface(surfBlocks);

	// Shut down SDL
	SDL_Quit();
}

//-----------------------------------------------------------------------------
void GameLoop()
{
	// Uint32 SDL_GetTicks(void) --- Use this function to get the number of milliseconds since the SDL library initialization.
	if ((SDL_GetTicks() - start_time) > 1000)
	{
		Move(0, 1);
		start_time = SDL_GetTicks();
	}
}
//-----------------------------------------------------------------------------
void NewGame()
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

//-----------------------------------------------------------------------------
void DrawTile(int x, int y, int tile)
{
	// Draw the Tile
	Blit(Display, x * TILESIZE, y * TILESIZE, surfBlocks, tile * TILESIZE, 0, TILESIZE, TILESIZE);
}

//-----------------------------------------------------------------------------
void DrawMap()
{
	int xmy;
	int ymx;

	// place the toolbar
	for (xmy = MAPWIDTH; xmy < MAPWIDTH + GREY; ++xmy)
	{
		for (ymx = 0; ymx < MAPHEIGHT; ++ymx)
		{
			DrawTile(xmy, ymx, TILEGREY);
		}
	}

	// draw preview block
	for (xmy = 0; xmy < 4; ++xmy)
	{
		for (ymx = 0; ymx < 4; ++ymx)
		{
			if (sPrePiece.size[xmy][ymx] != TILENODRAW)
			{
				DrawTile(sPrePiece.x + xmy, sPrePiece.y + ymx, sPrePiece.size[xmy][ymx]);
			}
		}
	}

	// draw the map
	// loop through the positions
	for (xmy = 0; xmy < MAPWIDTH; ++xmy)
	{
		for (ymx = 0; ymx < MAPHEIGHT; ++ymx)
		{
			DrawTile(xmy, ymx, Map[xmy][ymx]);
		}
	}

	// draw moving block
	for (xmy = 0; xmy < 4; ++xmy)
	{
		for (ymx = 0; ymx < 4; ++ymx)
		{
			if (sPiece.size[xmy][ymx] != TILENODRAW)
			{
				DrawTile(sPiece.x + xmy, sPiece.y + ymx, sPiece.size[xmy][ymx]);
			}
		}
	}

	// Redraw the entire Display
	SDL_Flip(Display);
}

//-----------------------------------------------------------------------------
void NewBlock()
{
	int newBlock;
	int i;
	int j;

	//  0   1   2   3   4    5   6    
	//   X                             These
	//   X   XX   X  XX   XX  XX   XX  are
	//   X   XX  XXX  XX XX    X   X   block
	//   X                     X   X   types
	//
	// begin game! make generate a block and then one in preview.

	srand(SDL_GetTicks());

	// initialize the piece to all blank.
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			sPiece.size[i][j] = TILENODRAW;
		}
	}

	sPiece.x = MAPWIDTH / 2 - 2;
	sPiece.y = -1;

	// let's see if the game's started yet
	if (GAMESTARTED == false)
	{
		// guess not..  
		// Generate a piece right off.
		// From now on, use previous preview block.
		GAMESTARTED = true;

		newBlock = rand() % 7;

		switch (newBlock)
		{
			case 0: // Tower!
			{
				sPiece.size[1][0] = TILERED;
				sPiece.size[1][1] = TILERED;
				sPiece.size[1][2] = TILERED;
				sPiece.size[1][3] = TILERED;
				sPiece.y = 0;
			} break;

			case 1: // Box!
			{
				sPiece.size[1][1] = TILEBLUE;
				sPiece.size[1][2] = TILEBLUE;
				sPiece.size[2][1] = TILEBLUE;
				sPiece.size[2][2] = TILEBLUE;
			} break;

			case 2: // Pyramid!
			{
				sPiece.size[1][1] = TILESTEEL;
				sPiece.size[0][2] = TILESTEEL;
				sPiece.size[1][2] = TILESTEEL;
				sPiece.size[2][2] = TILESTEEL;
			} break;

			case 3: // Left Leaner
			{
				sPiece.size[0][1] = TILEYELLOW;
				sPiece.size[1][1] = TILEYELLOW;
				sPiece.size[1][2] = TILEYELLOW;
				sPiece.size[2][2] = TILEYELLOW;
			} break;

			case 4: // Right Leaner
			{
				sPiece.size[2][1] = TILEGREEN;
				sPiece.size[1][1] = TILEGREEN;
				sPiece.size[1][2] = TILEGREEN;
				sPiece.size[0][2] = TILEGREEN;
			} break;

			case 5: // Left Knight
			{
				sPiece.size[1][1] = TILEWHITE;
				sPiece.size[2][1] = TILEWHITE;
				sPiece.size[2][2] = TILEWHITE;
				sPiece.size[2][3] = TILEWHITE;
			} break;

			case 6: // Right Knight
			{
				sPiece.size[2][1] = TILEPURPLE;
				sPiece.size[1][1] = TILEPURPLE;
				sPiece.size[1][2] = TILEPURPLE;
				sPiece.size[1][3] = TILEPURPLE;
			} break;
		}
	}
	else
	{
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 4; ++j)
			{
				sPiece.size[i][j] = sPrePiece.size[i][j];
			}
		}

	}

	newBlock = rand() % 7;

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			sPrePiece.size[i][j] = TILENODRAW;
		}
	}

	sPrePiece.x = MAPWIDTH + GREY / 4;
	sPrePiece.y = GREY / 4;

	switch (newBlock)
	{
		case 0: // Tower!
		{
			sPrePiece.size[1][0] = TILERED;
			sPrePiece.size[1][1] = TILERED;
			sPrePiece.size[1][2] = TILERED;
			sPrePiece.size[1][3] = TILERED;
		} break;

		case 1: // Box!
		{
			sPrePiece.size[1][1] = TILEBLUE;
			sPrePiece.size[1][2] = TILEBLUE;
			sPrePiece.size[2][1] = TILEBLUE;
			sPrePiece.size[2][2] = TILEBLUE;
		} break;

		case 2: // Pyramid!
		{
			sPrePiece.size[1][1] = TILESTEEL;
			sPrePiece.size[0][2] = TILESTEEL;
			sPrePiece.size[1][2] = TILESTEEL;
			sPrePiece.size[2][2] = TILESTEEL;
		} break;

		case 3: // Left Leaner
		{
			sPrePiece.size[0][1] = TILEYELLOW;
			sPrePiece.size[1][1] = TILEYELLOW;
			sPrePiece.size[1][2] = TILEYELLOW;
			sPrePiece.size[2][2] = TILEYELLOW;
		} break;

		case 4: // Right Leaner
		{
			sPrePiece.size[2][1] = TILEGREEN;
			sPrePiece.size[1][1] = TILEGREEN;
			sPrePiece.size[1][2] = TILEGREEN;
			sPrePiece.size[0][2] = TILEGREEN;
		} break;

		case 5: // Left Knight
		{
			sPrePiece.size[1][1] = TILEWHITE;
			sPrePiece.size[2][1] = TILEWHITE;
			sPrePiece.size[2][2] = TILEWHITE;
			sPrePiece.size[2][3] = TILEWHITE;
		} break;

		case 6: // Right Knight
		{
			sPrePiece.size[2][1] = TILEPURPLE;
			sPrePiece.size[1][1] = TILEPURPLE;
			sPrePiece.size[1][2] = TILEPURPLE;
			sPrePiece.size[1][3] = TILEPURPLE;
		} break;
	}

	DrawMap();
}

//-----------------------------------------------------------------------------
void RotateBlock()
{
	int i;
	int j;
	int temp[4][4];

	// copy & rotate the piece to the temporary array
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			temp[3 - j][i] = sPiece.size[i][j];
		}
	}

	// check collision of the temporary array with map borders
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			if (temp[i][j] != TILENODRAW)
			{
				if (sPiece.x + i < 0 || sPiece.x + i > MAPWIDTH - 1 ||
					sPiece.y + j < 0 || sPiece.y + j > MAPHEIGHT - 1)
				{
					return;
				}
			}
		}
	}

	// check collision of the temporary array with the blocks on the map
	for (int x = 0; x < MAPWIDTH; ++x)
	{
		for (int y = 0; y < MAPHEIGHT; ++y)
		{
			if (x >= sPiece.x && x < sPiece.x + 4)
			{
				if (y >= sPiece.y && y < sPiece.y + 4)
				{
					if (Map[x][y] != TILEBLACK)
					{
						if (temp[x - sPiece.x][y - sPiece.y] != TILENODRAW)
						{
							return;
						}
					}
				}
			}
		}
	}

	// end collision check

	// successful!  copy the rotated temporary array to the original piece
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			sPiece.size[i][j] = temp[i][j];
		}
	}

	DrawMap();
}

//-----------------------------------------------------------------------------
void Move(int x, int y)
{
	if (CollisionTest(x, y))
	{
		if (1 == y)
		{
			if (sPiece.y < 1)
			{
				NewGame(); // you lose!  new game.
			}
			else
			{
				bool killBlock = false;
				int i;
				int j;

				// new block time! add this one to the list!
				for (i = 0; i < 4; ++i)
				{
					for (j = 0; j < 4; ++j)
					{
						if (sPiece.size[i][j] != TILENODRAW)
						{
							Map[sPiece.x + i][sPiece.y + j] = sPiece.size[i][j];
						}
					}
				}

				// check for cleared row!
				for (j = 0; j < MAPHEIGHT; ++j)
				{
					bool filled = true;

					for (i = 0; i < MAPWIDTH; ++i)
					{
						if (Map[i][j] == TILEBLACK)
						{
							filled = false;
						}
					}

					if (filled)
					{
						RemoveRow(j);
						killBlock = true;
					}
				}

				if (killBlock)
				{
					for (i = 0; i < 4; ++i)
					{
						for (j = 0; j < 4; ++j)
						{
							sPiece.size[i][j] = TILENODRAW;
						}
					}
				}

				NewBlock();
			}
		}

	}
	else
	{
		sPiece.x += x;
		sPiece.y += y;
	}

	DrawMap();
}

//-----------------------------------------------------------------------------
int CollisionTest(int nx, int ny)
{
	int newx = sPiece.x + nx;
	int newy = sPiece.y + ny;

	int i;
	int j;
	int x;
	int y;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (sPiece.size[i][j] != TILENODRAW)
			{
				if (newx + i < 0 || newx + i > MAPWIDTH - 1 ||
					newy + j < 0 || newy + j > MAPHEIGHT - 1)
				{
					return 1;
				}
			}
		}
	}

	for (x = 0; x < MAPWIDTH; x++)
	{
		for (y = 0; y < MAPHEIGHT; y++)
		{
			if (x >= newx && x < newx + 4)
			{
				if (y >= newy && y < newy + 4)
				{
					if (Map[x][y] != TILEBLACK)
					{
						if (sPiece.size[x - newx][y - newy] != TILENODRAW)
						{
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------
void RemoveRow(int row)
{
	int x;
	int y;
	int counter = 0;

	for (x = 0; x < MAPWIDTH; x++)
	{
		for (y = row; y > 0; y--)
		{
			Map[x][y] = Map[x][y - 1];
		}
	}
}

//-----------------------------------------------------------------------------
void Blit(SDL_Surface *Dest, int DestX, int DestY, SDL_Surface *Src)
{
	// Create a Rect, and store the coordinates in it.
	// Because SDL likes it this way. 
	SDL_Rect DestR;
	DestR.x = DestX; 
	DestR.y = DestY;

	// Use this function to perform a fast surface copy to a destination surface.
	// int SDL_BlitSurface( SDL_Surface*    src,
	//						const SDL_Rect* srcrect,
	//						SDL_Surface*    dst,
	//						SDL_Rect*       dstrect
	//						)
	//
	// src --- SDL_surface structure to be copied from
	// srcrect --- the rectangle to be copied, or NULL to copy the entire surface
	// dst --- destination target
	// dstrect --- representing the rectangle that is copied into
	//
	// Draw to the Dest
	SDL_BlitSurface(Src, NULL, Dest, &DestR);
}

//-----------------------------------------------------------------------------
void Blit(SDL_Surface *Dest, int DestX, int DestY, SDL_Surface *Src, int SrcX, int SrcY, int SrcW, int SrcH)
{
	// Create 2 Rects. The first is for where we want to Blit to.
	// The other is for clipping the 'Src' so we only draw the portion we want

	SDL_Rect DestR; 
	DestR.x = DestX;
	DestR.y = DestY;
	 
	SDL_Rect SrcR;
	SrcR.x = SrcX;
	SrcR.y = SrcY;
	SrcR.w = SrcW;
	SrcR.h = SrcH;

	// Draw to the Dest
	SDL_BlitSurface(Src, &SrcR, Dest, &DestR);
}

//=============================================================================