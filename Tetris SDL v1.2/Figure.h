



#ifndef FIGURE_H
#define FIGURE_H

namespace tetris
{
	class Figure;
}

class tetris::Figure
{

public:

	static const int FIGURE_WIDTH = 4;
	static const int FIGURE_HEIGHT = 4;

public:

	Figure(int** figureMatrix);

public:

	void setCoordinates(int x, int y);
	void setXCoordinate(int x);
	void setYCoordinate(int y);
	int getXCoordinate();
	int getYCoordinate();

public:

	//   0   1    2   3   4   5   6    
	//   X                            These
	//   X   XX   X  XX   XX  XX  XX  are
	//   X   XX  XXX  XX XX    X  X   figure
	//   X                     X  X   types
	//

	enum FigureType
	{
		STICK,
		BOX,
		PYRAMID,
		LEFT_SNAKE,
		RIGHT_SNAKE,
		LEFT_KNIGHT,
		RIGHT_KNIGHT,


		MAX_FIGURES, // number of Figure Types
	};

	int mFigureMatrix[FIGURE_WIDTH][FIGURE_HEIGHT];

private:

	int mX;
	int mY;
};

#endif // !FIGURE_H

