



#ifndef NEXTFIGURE_H

// forward declaration of BoardData
// we can do this because we only have pointer to BoardData type 
namespace tetris
{
	struct NextFigureData;
}

namespace tetris
{
	class NextFigure;
}

////////////////////
// CLASS
////////////////////

class tetris::NextFigure
{

public:

	NextFigure(int width, int height);

public:

	void setWidth(int width);
	void setHeight(int height);
	bool isValidSize(int number);
	void start();
	void generateNewFigure(bool generate);
	bool isNewFigure();
	NextFigureData* getNextFigureData();
	
////////////////////////
// PRIVATES
////////////////////////

private:

	bool setWidth_NoThrow(int width);
	bool setHeight_NoThrow(int height);
	void init();

private:

	NextFigureData* mNextFigureData;
	bool mIsInitialized;
};

#endif // !NEXTFIGURE_H

