//
//
//
//
//#include "Block.h"
//#include <SDL.h>
//#include <stdlib.h>
//
//void Block::NewBlock()
//{
//	int newBlock;
//	int i;
//	int j;
//
//	//   0   1   2   3   4    5   6    
//	//   X                             These
//	//   X   XX   X  XX   XX  XX   XX  are
//	//   X   XX  XXX  XX XX    X   X   block
//	//   X                     X   X   types
//	//
//	// begin game! make generate a block and then one in preview.
//
//	srand(SDL_GetTicks());
//
//	// initialize the piece to all blank.
//	for (i = 0; i < 4; ++i)
//	{
//		for (j = 0; j < 4; ++j)
//		{
//			sPiece.size[i][j] = TILENODRAW;
//		}
//	}
//
//	sPiece.x = MAPWIDTH / 2 - 2;
//	sPiece.y = -1;
//
//	// let's see if the game's started yet
//	if (GAMESTARTED == false)
//	{
//		// guess not..  
//		// Generate a piece right off.
//		// From now on, use previous preview block.
//		GAMESTARTED = true;
//
//		newBlock = rand() % 7;
//
//		switch (newBlock)
//		{
//			case 0: // Tower!
//			{
//				sPiece.size[1][0] = TILERED;
//				sPiece.size[1][1] = TILERED;
//				sPiece.size[1][2] = TILERED;
//				sPiece.size[1][3] = TILERED;
//				sPiece.y = 0;
//			} break;
//
//			case 1: // Box!
//			{
//				sPiece.size[1][1] = TILEBLUE;
//				sPiece.size[1][2] = TILEBLUE;
//				sPiece.size[2][1] = TILEBLUE;
//				sPiece.size[2][2] = TILEBLUE;
//			} break;
//
//			case 2: // Pyramid!
//			{
//				sPiece.size[1][1] = TILESTEEL;
//				sPiece.size[0][2] = TILESTEEL;
//				sPiece.size[1][2] = TILESTEEL;
//				sPiece.size[2][2] = TILESTEEL;
//			} break;
//
//			case 3: // Left Leaner
//			{
//				sPiece.size[0][1] = TILEYELLOW;
//				sPiece.size[1][1] = TILEYELLOW;
//				sPiece.size[1][2] = TILEYELLOW;
//				sPiece.size[2][2] = TILEYELLOW;
//			} break;
//
//			case 4: // Right Leaner
//			{
//				sPiece.size[2][1] = TILEGREEN;
//				sPiece.size[1][1] = TILEGREEN;
//				sPiece.size[1][2] = TILEGREEN;
//				sPiece.size[0][2] = TILEGREEN;
//			} break;
//
//			case 5: // Left Knight
//			{
//				sPiece.size[1][1] = TILEWHITE;
//				sPiece.size[2][1] = TILEWHITE;
//				sPiece.size[2][2] = TILEWHITE;
//				sPiece.size[2][3] = TILEWHITE;
//			} break;
//
//			case 6: // Right Knight
//			{
//				sPiece.size[2][1] = TILEPURPLE;
//				sPiece.size[1][1] = TILEPURPLE;
//				sPiece.size[1][2] = TILEPURPLE;
//				sPiece.size[1][3] = TILEPURPLE;
//			} break;
//		}
//	}
//	else
//	{
//		for (i = 0; i < 4; ++i)
//		{
//			for (j = 0; j < 4; ++j)
//			{
//				sPiece.size[i][j] = sPrePiece.size[i][j];
//			}
//		}
//
//	}
//
//	newBlock = rand() % 7;
//
//	for (i = 0; i < 4; ++i)
//	{
//		for (j = 0; j < 4; ++j)
//		{
//			sPrePiece.size[i][j] = TILENODRAW;
//		}
//	}
//
//	sPrePiece.x = MAPWIDTH + GREY / 4;
//	sPrePiece.y = GREY / 4;
//
//	switch (newBlock)
//	{
//		case 0: // Tower!
//		{
//			sPrePiece.size[1][0] = TILERED;
//			sPrePiece.size[1][1] = TILERED;
//			sPrePiece.size[1][2] = TILERED;
//			sPrePiece.size[1][3] = TILERED;
//		} break;
//
//		case 1: // Box!
//		{
//			sPrePiece.size[1][1] = TILEBLUE;
//			sPrePiece.size[1][2] = TILEBLUE;
//			sPrePiece.size[2][1] = TILEBLUE;
//			sPrePiece.size[2][2] = TILEBLUE;
//		} break;
//
//		case 2: // Pyramid!
//		{
//			sPrePiece.size[1][1] = TILESTEEL;
//			sPrePiece.size[0][2] = TILESTEEL;
//			sPrePiece.size[1][2] = TILESTEEL;
//			sPrePiece.size[2][2] = TILESTEEL;
//		} break;
//
//		case 3: // Left Leaner
//		{
//			sPrePiece.size[0][1] = TILEYELLOW;
//			sPrePiece.size[1][1] = TILEYELLOW;
//			sPrePiece.size[1][2] = TILEYELLOW;
//			sPrePiece.size[2][2] = TILEYELLOW;
//		} break;
//
//		case 4: // Right Leaner
//		{
//			sPrePiece.size[2][1] = TILEGREEN;
//			sPrePiece.size[1][1] = TILEGREEN;
//			sPrePiece.size[1][2] = TILEGREEN;
//			sPrePiece.size[0][2] = TILEGREEN;
//		} break;
//
//		case 5: // Left Knight
//		{
//			sPrePiece.size[1][1] = TILEWHITE;
//			sPrePiece.size[2][1] = TILEWHITE;
//			sPrePiece.size[2][2] = TILEWHITE;
//			sPrePiece.size[2][3] = TILEWHITE;
//		} break;
//
//		case 6: // Right Knight
//		{
//			sPrePiece.size[2][1] = TILEPURPLE;
//			sPrePiece.size[1][1] = TILEPURPLE;
//			sPrePiece.size[1][2] = TILEPURPLE;
//			sPrePiece.size[1][3] = TILEPURPLE;
//		} break;
//	}
//
//	DrawMap();
//}
//
//void Block::RotateBlock()
//{
//	int i;
//	int j;
//	int temp[4][4];
//
//	// copy & rotate the piece to the temporary array
//	for (i = 0; i < 4; ++i)
//	{
//		for (j = 0; j < 4; ++j)
//		{
//			temp[3 - j][i] = sPiece.size[i][j];
//		}
//	}
//
//	// check collision of the temporary array with map borders
//	for (i = 0; i < 4; ++i)
//	{
//		for (j = 0; j < 4; ++j)
//		{
//			if (temp[i][j] != TILENODRAW)
//			{
//				if (sPiece.x + i < 0 || sPiece.x + i > MAPWIDTH - 1 ||
//					sPiece.y + j < 0 || sPiece.y + j > MAPHEIGHT - 1)
//				{
//					return;
//				}
//			}
//		}
//	}
//
//	// check collision of the temporary array with the blocks on the map
//	for (int x = 0; x < MAPWIDTH; ++x)
//	{
//		for (int y = 0; y < MAPHEIGHT; ++y)
//		{
//			if (x >= sPiece.x && x < sPiece.x + 4)
//			{
//				if (y >= sPiece.y && y < sPiece.y + 4)
//				{
//					if (Map[x][y] != TILEBLACK)
//					{
//						if (temp[x - sPiece.x][y - sPiece.y] != TILENODRAW)
//						{
//							return;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// end collision check
//
//	// successful!  copy the rotated temporary array to the original piece
//	for (i = 0; i < 4; ++i)
//	{
//		for (j = 0; j < 4; ++j)
//		{
//			sPiece.size[i][j] = temp[i][j];
//		}
//	}
//
//	DrawMap();
//}
//
//void Block::Move(int x, int y)
//{
//	if (CollisionTest(x, y))
//	{
//		if (1 == y)
//		{
//			if (sPiece.y < 1)
//			{
//				NewGame(); // you lose!  new game.
//			}
//			else
//			{
//				bool killBlock = false;
//				int i;
//				int j;
//
//				// new block time! add this one to the list!
//				for (i = 0; i < 4; ++i)
//				{
//					for (j = 0; j < 4; ++j)
//					{
//						if (sPiece.size[i][j] != TILENODRAW)
//						{
//							Map[sPiece.x + i][sPiece.y + j] = sPiece.size[i][j];
//						}
//					}
//				}
//
//				// check for cleared row!
//				for (j = 0; j < MAPHEIGHT; ++j)
//				{
//					bool filled = true;
//
//					for (i = 0; i < MAPWIDTH; ++i)
//					{
//						if (Map[i][j] == TILEBLACK)
//						{
//							filled = false;
//						}
//					}
//
//					if (filled)
//					{
//						RemoveRow(j);
//						killBlock = true;
//					}
//				}
//
//				if (killBlock)
//				{
//					for (i = 0; i < 4; ++i)
//					{
//						for (j = 0; j < 4; ++j)
//						{
//							sPiece.size[i][j] = TILENODRAW;
//						}
//					}
//				}
//
//				NewBlock();
//			}
//		}
//
//	}
//	else
//	{
//		sPiece.x += x;
//		sPiece.y += y;
//	}
//
//	DrawMap();
//}