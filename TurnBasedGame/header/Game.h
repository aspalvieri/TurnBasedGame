#ifndef GAME_H
#define GAME_H

#include "Sprite.h"
#include "Timer.h"

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

	//Build functions
	void buildFontManager();

	void limitFPS();

private:
	//Player variables
	SDL_Rect *camera;

	//Engine variables
	double averageFPS = 0;
	Timer FPS, capFPS;
	int countedFrames = 0;
	Texture fpsText;

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