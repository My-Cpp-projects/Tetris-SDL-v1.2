



#include "../../include/controller/GameController.h"
#include "../../include/model/BoardData.h"
#include "../../include/model/NextFigureData.h"
#include "../../include/util/DrawUtil.h"

#include "SDL.h"

tetris::GameController::GameController(BoardData* boardData, NextFigureData* nextFigureData)
	: mBoardData(boardData)
	, mNextFigureData(nextFigureData)
	, gameRunning(true)
{
}

void tetris::GameController::gameLoop()
{
	static int startTime = 0;

	if ((SDL_GetTicks() - startTime) > 1000)
	{
		move(0, 1);
		startTime = SDL_GetTicks();
	}
}

void tetris::GameController::onEvent()
{
	// used to regulate the speed when a key is pressed
	static int pressTime = 0;

	// used to regulate direction.
	// static because the function is called everytime and we dont need to loose previous values
	static int moveDirectionY = 0;
	static int moveDirectionX = 0;

	static bool isRotate = false;

	SDL_Event Event;

	//===  Event loop ===//
	// Grab any events in the queue
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
			case SDL_QUIT:		// Found a quit event
			{
				gameRunning = false;
			} break;

			case SDL_KEYDOWN:	// A key has been pressed
			{
				int Sym = Event.key.keysym.sym;

				switch (Sym)
				{
					case SDLK_ESCAPE:
					{
						gameRunning = false;
					} break;

					case SDLK_DOWN:
					{
						moveDirectionY = 1;
					} break;

					case SDLK_UP:
					{
						isRotate = true;
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
						if (isRotate)
						{
							isRotate = false;
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
	if ((SDL_GetTicks() - pressTime) > 60)
	{
		move(moveDirectionX, 0);
		move(0, moveDirectionY);

		if (isRotate)
		{
			rotate();
		}

		pressTime = SDL_GetTicks();
	}

}

bool tetris::GameController::isRunning()
{
	return gameRunning;
}

////////////////////////
// Private functions
///////////////////////

void tetris::GameController::move(int x, int y)
{
	if (collisionTest(x, y))
	{
		if (1 == y)
		{
			if (mBoardData->mFigure->getYCoordinate() < 1)
			{
				mBoardData->newGame = true; // you lose!  new game.
			}
			else
			{
				bool killBlock = false;
				int i;
				int j;

				// new block time! add this one to the list!
				for (i = 0; i < mBoardData->mFigure->FIGURE_WIDTH; ++i)
				{
					for (j = 0; j < mBoardData->mFigure->FIGURE_HEIGHT; ++j)
					{
						if (mBoardData->mFigure->mFigureMatrix[i][j] != ::DrawUtil::TILE_NODRAW)
						{
							mBoardData->mBoard[mBoardData->mFigure->getXCoordinate() + i][mBoardData->mFigure->getYCoordinate() + j] = mBoardData->mFigure->mFigureMatrix[i][j];
						}
					}
				}

				// check for cleared row!
				for (j = 0; j < mBoardData->mHeight; ++j)
				{
					bool filled = true;

					for (i = 0; i < mBoardData->mWidth; ++i)
					{
						if (mBoardData->mBoard[i][j] == ::DrawUtil::TILE_BLACK)
						{
							filled = false;
						}
					}

					if (filled)
					{
						removeRow(j);
						killBlock = true;
					}
				}

				if (killBlock)
				{
					for (i = 0; i < mBoardData->mFigure->FIGURE_WIDTH; ++i)
					{
						for (j = 0; j < mBoardData->mFigure->FIGURE_HEIGHT; ++j)
						{
							mBoardData->mFigure->mFigureMatrix[i][j] = ::DrawUtil::TILE_NODRAW;
						}
					}
				}

				mBoardData->mFigure = mNextFigureData->mNextFigure;

				// adjust X coordinate according to board
				mBoardData->mFigure->setCoordinateX(mBoardData->mWidth / 2 - 1);

				mNextFigureData->generateNew = true;
			}
		}

	}
	else
	{
		
		mBoardData->mFigure->setCoordinateX(mBoardData->mFigure->getXCoordinate() + x);
		mBoardData->mFigure->setCoordinateY(mBoardData->mFigure->getYCoordinate() + y);
	}
}

void tetris::GameController::rotate()
{
	// WTF ???
	const int a = mBoardData->mFigure->FIGURE_WIDTH;
	const int b = mBoardData->mFigure->FIGURE_HEIGHT;
	int i;
	int j;
	int temp[a][b]; // <- WTF ????

	// copy & rotate the piece to the temporary array
	for (i = 0; i < mBoardData->mFigure->FIGURE_WIDTH; ++i)
	{
		for (j = 0; j < mBoardData->mFigure->FIGURE_HEIGHT; ++j)
		{
			temp[3 - j][i] = mBoardData->mFigure->mFigureMatrix[i][j];
		}
	}

	// check collision of the temporary array with map borders
	for (i = 0; i < mBoardData->mFigure->FIGURE_WIDTH; ++i)
	{
		for (j = 0; j < mBoardData->mFigure->FIGURE_HEIGHT; ++j)
		{
			if (temp[i][j] != ::DrawUtil::TILE_NODRAW)
			{
				if (mBoardData->mFigure->getXCoordinate() + i < 0 || mBoardData->mFigure->getXCoordinate() + i > mBoardData->mWidth - 1 ||
					mBoardData->mFigure->getYCoordinate() + j < 0 || mBoardData->mFigure->getYCoordinate() + j > mBoardData->mHeight - 1)
				{
					return;
				}
			}
		}
	}

	// check collision of the temporary array with the blocks on the map
	for (int x = 0; x < mBoardData->mWidth; ++x)
	{
		for (int y = 0; y < mBoardData->mHeight; ++y)
		{
			if (x >= mBoardData->mFigure->getXCoordinate() && x < mBoardData->mFigure->getXCoordinate() + mBoardData->mFigure->FIGURE_WIDTH)
			{
				if (y >= mBoardData->mFigure->getYCoordinate() && y < mBoardData->mFigure->getYCoordinate() + mBoardData->mFigure->FIGURE_HEIGHT)
				{
					if (mBoardData->mBoard[x][y] != ::DrawUtil::TILE_BLACK)
					{
						if (temp[x - mBoardData->mFigure->getXCoordinate()][y - mBoardData->mFigure->getYCoordinate()] != ::DrawUtil::TILE_NODRAW)
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
	for (i = 0; i < mBoardData->mFigure->FIGURE_WIDTH; ++i)
	{
		for (j = 0; j < mBoardData->mFigure->FIGURE_HEIGHT; ++j)
		{
			mBoardData->mFigure->mFigureMatrix[i][j] = temp[i][j];
		}
	}
}

int tetris::GameController::collisionTest(int nx, int ny)
{
	int newx = mBoardData->mFigure->getXCoordinate() + nx;
	int newy = mBoardData->mFigure->getYCoordinate() + ny;

	int i;
	int j;
	int x;
	int y;

	for (i = 0; i < mBoardData->mFigure->FIGURE_WIDTH; i++)
	{
		for (j = 0; j < mBoardData->mFigure->FIGURE_HEIGHT; j++)
		{
			if (mBoardData->mFigure->mFigureMatrix[i][j] != ::DrawUtil::TILE_NODRAW)
			{
				if (newx + i < 0 || newx + i > mBoardData->mWidth - 1 ||
					newy + j < 0 || newy + j > mBoardData->mHeight - 1)
				{
					return 1;
				}
			}
		}
	}

	for (x = 0; x < mBoardData->mWidth; x++)
	{
		for (y = 0; y < mBoardData->mHeight; y++)
		{
			if (x >= newx && x < newx + mBoardData->mFigure->FIGURE_WIDTH)
			{
				if (y >= newy && y < newy + mBoardData->mFigure->FIGURE_HEIGHT)
				{
					if (mBoardData->mBoard[x][y] != ::DrawUtil::TILE_BLACK)
					{
						if (mBoardData->mFigure->mFigureMatrix[x - newx][y - newy] != ::DrawUtil::TILE_NODRAW)
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

void tetris::GameController::removeRow(int row)
{
	int x;
	int y;
	int counter = 0;

	for (x = 0; x < mBoardData->mWidth; x++)
	{
		for (y = row; y > 0; y--)
		{
			mBoardData->mBoard[x][y] = mBoardData->mBoard[x][y - 1];
		}
	}
}