#ifndef GAME_H
#define GAME_H

#include "Sprite.h"
#include "Timer.h"
#include "RDevice.h"

class Game {
public:
	Game();
	~Game();

	//Engine functions
	void initialize();
	bool running();
	void handleEvents();
	void update();
	void render();

private:
	//Player variables
	SDL_Rect *camera;

	//Static variables
	pair<int, int> *mousePos;
	SDL_Rect *mPos;
	int *mouseButton;
	map<int, TTF_Font*> fontManager;
	bool gameRunning;

	//SDL variables
	SDL_Event e;
	SDL_Renderer *gRenderer = NULL;
	SDL_Window *gWindow = NULL;
};

#endif//GAME_H