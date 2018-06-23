


#ifndef BOARD_H
#define BOARD_H

// forward declaration of BoardData
// we can do this because we only have pointer to BoardData type 
namespace tetris
{
	struct BoardData;
}

namespace tetris
{
	class Board;
}

////////////////////
// CLASS
////////////////////

class tetris::Board
{

public:

	Board(int width, int height);

public:

	void setWidth(int width);
	void setHeight(int height);
	bool isValidSize(int number);
	void start();
	void startNewGame(bool start);
	bool isNewGame();
	BoardData* getBoardData();


	////////////////////////
	// PRIVATES
	////////////////////////

private:

	bool setWidth_NoThrow(int width);
	bool setHeight_NoThrow(int height);
	void init();

private:
	
	BoardData* mBoardData;
	bool mIsInitialized;
};

#endif // !BOARD_H

