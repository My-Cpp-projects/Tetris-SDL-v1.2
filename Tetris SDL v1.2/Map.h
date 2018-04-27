//
//
//
//
//#ifndef MAP_H
//#define MAP_H
//
//#include "Util.h"
//
//class Map
//{
//
//public:
//
//	Map(int mapWidth = 10, int mapHeight = 30, int greyWidth = 8);
//
//	void DrawMap(); // draw the whole map.. render function, basically
//	void RemoveRow(int row); // remove a row.. that would be the 'x'.
//	int CollisionTest(int nx, int ny); // test collision of blocks
//
//
//	// sets map width in terms of Tiles
//	void setMapWidth(int mapWidth);
//
//	// sets map height in terms of Tiles
//	void setMapHeight(int mapHeight);
//
//	// sets width of the grey part in terms of Tiles
//	void setGreyWidth(int greyWidth);
//
//	int getMapWidth();
//	int getMapHeight();
//	int getGreyWidth();
//
//private:
//
//	Util util;
//
//	int mMapWidth;
//	int mMapHeight;
//	int mGreyWidth;
//
//	int** mMapArray; // the game map!
//};
//
//#endif
