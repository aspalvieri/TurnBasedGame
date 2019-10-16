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
	void newline(int layer, std::string text, TTF_Font* gFont, int x = 0, int y = 0, SDL_Color textColor = { 0, 0, 0 }, int wrapLength = SCREEN_WIDTH);
	void clearLineLayer(int layer);
	void clearAllLineLayers();

	//Build functions
	void buildFontManager();

	void limitFPS();

private:
	//Player variables
	SDL_Rect *camera;

	//Game variables

	//Engine variables
	double averageFPS = 0;
	Timer FPS, capFPS;
	int countedFrames = 0;
	Texture fpsText;
	vector<StaticTexture> staticText[MAX_STATICTEXT_LAYERS];

	//Static variables
	pair<int, int> *mousePos;
	SDL_Rect *mPos;
	int *mouseButton;
	map<int, TTF_Font*> fontManager, fontManagerBold;
	bool gameRunning;

	//SDL variables
	SDL_Event e;
	SDL_Renderer *gRenderer = NULL;
	SDL_Window *gWindow = NULL;
};

#endif//GAME_H