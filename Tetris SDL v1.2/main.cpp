



#include "include/controller/GameController.h"
#include "include/logger/Logger.h"
#include "include/model/Board.h"
#include "include/model/NextFigure.h"
#include "include/view/BoardView.h"
#include "include/view/NextFigureView.h"
#include "include/view/GameView.h"


#include <iostream>
#include "SDL.h"

#define WWIDTH		336									// Width of Window
#define WHEIGHT		480									// Height of Window
#define WBIT		16									// 16-bit colors
#define WFLAGS		SDL_HWSURFACE | SDL_DOUBLEBUF		// Set up for Video Hardware and Double Buffering
#define WINDOWTITLE "Tetris"

SDL_Surface* display;	// Our main display surface
SDL_Surface* surfBlocks; // used to read from bmp

void GameDone();

int main(int argc, char *args[])
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{

		Logger::print("Cannot Initialize SDL Systems: ");
		Logger::print(SDL_GetError());
		return 0;
	}

	display = SDL_SetVideoMode(WWIDTH, WHEIGHT, WBIT, WFLAGS);

	if (!display)
	{
		Logger::print("Cannot set Video Mode: ");
		Logger::print(SDL_GetError());
		return 0;
	}

	surfBlocks = SDL_LoadBMP("blocks.bmp");

	if (!surfBlocks)
	{
		Logger::print("File not Found: blocks.bmp: ");
		Logger::print(SDL_GetError());
		return false;
	}

	SDL_WM_SetCaption(WINDOWTITLE, WINDOWTITLE);

	// sizes in tiles
	tetris::Board board(12, 30);
	tetris::NextFigure nextFigure(9, 30);

	// appropriate views for each model
	tetris::BoardView boardView(display, surfBlocks, board.getBoardData(), 0, 0);
	tetris::NextFigureView nextFigureView(display, surfBlocks, nextFigure.getNextFigureData(), 12, 0);

	tetris::GameView gameView(display, surfBlocks);

	gameView.addChild(&boardView);
	gameView.addChild(&nextFigureView);
		
	tetris::GameController gameController(board.getBoardData(), nextFigure.getNextFigureData());


	while (gameController.isRunning())
	{
		board.start();
		nextFigure.start();

		gameController.gameLoop();
		gameController.onEvent();
		gameView.Draw();
	}

	atexit(GameDone);

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

