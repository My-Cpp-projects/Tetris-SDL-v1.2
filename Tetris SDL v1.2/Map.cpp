//
//
//
//
//#include "Map.h"
//#include <SDL.h>
//
//Map::Map(int mapWidth, int mapHeight, int greyWidth)
//{
//	setMapWidth(mapWidth);
//	setMapHeight(mapHeight);
//	setGreyWidth(greyWidth);
//
//	mMapArray = new int*[mMapWidth];
//	for (int i = 0; i < mMapHeight + 1; ++i)
//	{
//		mMapArray[i] = new int[mMapHeight + 1];
//	}
//}
//
//void Map::DrawMap()
//{
//	int xmy;
//	int ymx;
//
//	// place the toolbar
//	for (xmy = mMapWidth; xmy < mMapWidth + mGreyWidth; ++xmy)
//	{
//		for (ymx = 0; ymx < mMapHeight; ++ymx)
//		{
//			DrawTile(xmy, ymx, TILEGREY);
//		}
//	}
//
//	// draw preview block
//	for (xmy = 0; xmy < 4; ++xmy)
//	{
//		for (ymx = 0; ymx < 4; ++ymx)
//		{
//			if (sPrePiece.size[xmy][ymx] != TILENODRAW)
//			{
//				DrawTile(sPrePiece.x + xmy, sPrePiece.y + ymx, sPrePiece.size[xmy][ymx]);
//			}
//		}
//	}
//
//	// draw the map
//	// loop through the positions
//	for (xmy = 0; xmy < mMapWidth; ++xmy)
//	{
//		for (ymx = 0; ymx < mMapHeight; ++ymx)
//		{
//			DrawTile(xmy, ymx, mMapArray[xmy][ymx]);
//		}
//	}
//
//	// draw moving block
//	for (xmy = 0; xmy < 4; ++xmy)
//	{
//		for (ymx = 0; ymx < 4; ++ymx)
//		{
//			if (sPiece.size[xmy][ymx] != TILENODRAW)
//			{
//				DrawTile(sPiece.x + xmy, sPiece.y + ymx, sPiece.size[xmy][ymx]);
//			}
//		}
//	}
//
//	// Redraw the entire Display
//	SDL_Flip(util.Display);
//}
//
//void Map::RemoveRow(int row)
//{
//	int x;
//	int y;
//	int counter = 0;
//
//	for (x = 0; x < mMapWidth; x++)
//	{
//		for (y = row; y > 0; y--)
//		{
//			mMapArray[x][y] = mMapArray[x][y - 1];
//		}
//	}
//}
//
//int Map::CollisionTest(int nx, int ny)
//{
//	int newx = sPiece.x + nx;
//	int newy = sPiece.y + ny;
//
//	int i;
//	int j;
//	int x;
//	int y;
//
//	for (i = 0; i < 4; i++)
//	{
//		for (j = 0; j < 4; j++)
//		{
//			if (sPiece.size[i][j] != TILENODRAW)
//			{
//				if (newx + i < 0 || newx + i > mMapWidth - 1 ||
//					newy + j < 0 || newy + j > mMapHeight - 1)
//				{
//					return 1;
//				}
//			}
//		}
//	}
//
//	for (x = 0; x < mMapWidth; x++)
//	{
//		for (y = 0; y < mMapHeight; y++)
//		{
//			if (x >= newx && x < newx + 4)
//			{
//				if (y >= newy && y < newy + 4)
//				{
//					if (mMapArray[x][y] != TILEBLACK)
//					{
//						if (sPiece.size[x - newx][y - newy] != TILENODRAW)
//						{
//							return 1;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//
//
//
//// ====================================================
//// =================== SET FUNCTIONS ==================
//// ====================================================
//
//void Map::setMapWidth(int mapWidth)
//{
//	// if invalid input, use default value
//	mMapWidth = (mapWidth > 0) ? mapWidth : 10;
//}
//void Map::setMapHeight(int mapHeight)
//{
//	// if invalid input, use default value
//	mMapHeight = (mapHeight > 0) ? mapHeight : 30;
//}
//
//void Map::setGreyWidth(int greyWidth)
//{
//	// if invalid input, use default value
//	mGreyWidth = (greyWidth > 0) ? greyWidth : 8;
//}
//
//
//
//
//// ===================================================
//// =================== GET FUNCTIONS =================
//// ===================================================
//
//int Map::getMapWidth()
//{
//	return mMapWidth;
//}
//
//int Map::getMapHeight()
//{
//	return mMapHeight;
//}
//
//int Map::getGreyWidth()
//{
//	return mGreyWidth;
//}
//
//
//
