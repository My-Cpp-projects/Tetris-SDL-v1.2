



#ifndef MAP_H
#define MAP_H

class Map
{

public:

	void DrawMap(); // draw the whole map.. render function, basically
	void RemoveRow(int row); // remove a row.. that would be the 'x'.
	int CollisionTest(int nx, int ny); // test collision of blocks

private:

	const int MAP_WIDTH;
	const int MAP_HEIGHT;
	const int GREY;
	int Map[MAP_WIDTH][MAP_HEIGHT + 1]; // the game map!

};

#endif
