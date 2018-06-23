



#ifndef FIGURE_H
#define FIGURE_H

namespace tetris
{
	class Figure;
}

class tetris::Figure
{

public:

	//   0   1    2   3   4   5   6    
	//   X                            These
	//   X   XX   X  XX   XX  XX  XX  are
	//   X   XX  XXX  XX XX    X  X   figure
	//   X                     X  X   types
	//

	enum FigureType : int
	{
		STICK,
		BOX,
		PYRAMID,
		LEFT_SNAKE,
		RIGHT_SNAKE,
		LEFT_KNIGHT,
		RIGHT_KNIGHT,


		COUNT, // number of Figure Types
	};

public:

	static const int FIGURE_WIDTH = 4;
	static const int FIGURE_HEIGHT = 4;

public:

	// constructor
	Figure(int** figureMatrix, FigureType type);

public:

	void setCoordinates(int x, int y);
	void setCoordinateX(int x);
	void setCoordinateY(int y);
	int getXCoordinate();
	int getYCoordinate();

public:

	int mFigureMatrix[FIGURE_WIDTH][FIGURE_HEIGHT];

	FigureType mType;

private:

	int mX;
	int mY;

};

#endif // !FIGURE_H

