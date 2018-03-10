



#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include "Util.h"

class Tile
{

public:

	void DrawTile(int x, int y, int tile); // coordinates & tile type
	
private:

	Util util;

	// TODO change this static consts to some other structure
	static const int TILE_SIZE = 16;

	static const int TILE_NODRAW = -1;
	static const int TILE_BLACK = 0;
	static const int TILE_GREY = 1;
	static const int TILE_BLUE = 2;
	static const int TILE_RED = 3;
	static const int TILE_GREEN = 4;
	static const int TILE_YELLOW = 5;
	static const int TILE_WHITE = 6;
	static const int TILE_STEEL = 7;
	static const int TILE_PURPLE = 8;
}; 

#endif
