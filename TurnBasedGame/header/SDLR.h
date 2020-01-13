#ifndef SDLR_H
#define SDLR_H

#include "Includes.h"
#include "Globals.h"
#include "RDevice.h"

//Static SDL Renderer, easier to pass around
struct SDLR
{
	SDLR();

	//Randomization functions
	static RDevice rand;

	//Rendering software
	static SDL_Renderer* gRenderer;

	//Window pane
	static SDL_Window* gWindow;

	//User's mouse buttons
	static bool leftDown;
	static bool leftReleased;
	static bool rightDown;
	static bool rightReleased;

	//Player's camera
	static SDL_Rect camera;

	//Mouse position relative to the window
	static SDL_Rect mPos;
	//Mouse position relative to the game world
	static SDL_Rect mPosCam; 
};

#endif//SDLR_H