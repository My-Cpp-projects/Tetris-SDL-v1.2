



#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// forward declarations
namespace tetris
{
	struct BoardData;
	struct NextFigureData;
}

namespace tetris
{
	class GameController;
}

class tetris::GameController
{

public:

	GameController(BoardData* boardData, NextFigureData* nextFigureData);
	void gameLoop();
	void onEvent();
	bool isRunning();

private:

	//void newGame();
	void move(int x, int y);
	void rotate();
	int collisionTest(int nx, int ny);
	void removeRow(int row);

private:

	BoardData* mBoardData;
	NextFigureData* mNextFigureData;
	bool gameRunning;
};

#endif

