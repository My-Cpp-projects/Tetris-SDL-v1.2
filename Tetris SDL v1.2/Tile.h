



#ifndef TILE_H
#define TILE_H

class Tile
{

public:

	void DrawTile(int x, int y, int tile); // coordinates & tile type
	
private:

	const int TILE_SIZE;

	const int TILE_NODRAW;;
	const int TILE_BLACK;
	const int TILE_GREY;
	const int TILE_BLUE;
	const int TILE_RED;
	const int TILE_GREEN;
	const int TILE_YELLOW;
	const int TILE_WHITE;
	const int TILE_STEEL;
	const int TILE_PURPLE;
};

#endif
