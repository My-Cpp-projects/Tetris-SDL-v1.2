



#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

#include "../../include/model/Figure.h"

namespace tetris
{
	class FigureFactory;
}

class tetris::FigureFactory
{
public:

	Figure* createFigure(Figure::FigureType type);
	Figure* createRandomFigure();
};

#endif // !FIGUREFACTORY_H

