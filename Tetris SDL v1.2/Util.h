//
//
//
//
//// This class contains SDL variables and some functions that use SDL
//// Which are used in almost all other classes
//
//#ifndef UTIL_H
//#define UTIL_H
//
//#include <SDL.h>
//
//class Util
//{
//public:
//
//	// Blitting --- Basically it means copying the image from one surface to another
//	// Makes it easier to Blit a Surface to another Surface
//	static void Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src);
//	static void Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src, int SrcX, int SrcY, int SrcW, int SrcH);
//
//	//-----------------------------------------------------------------------------
//	// SDL_Surface --- A structure that contains a collection of pixels used in software blitting.
//	//				   SDL_Surface's represent areas of "graphical" memory, memory that can be drawn to.
//	// TODO initialise in main
//	static SDL_Surface* Display;	// Our main display surface
//
//	static SDL_Surface* surfBlocks; // Initialised in GameController.cpp New
//};
//
//#endif // !UTIL_H
//
