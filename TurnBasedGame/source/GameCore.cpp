#include "../header/Game.h"

Game::Game() {
	gRenderer = SDLR::gRenderer;
	gWindow = SDLR::gWindow;

	camera = &SDLR::camera;
	mousePos = &SDLR::mousePosition;
	mouseButton = &SDLR::mouseButton;
	mPos = &SDLR::mPos;
}

Game::~Game() {

}

void Game::initialize() {
	buildFontManager();
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	srand((unsigned)time(0));
	gameRunning = true;
	FPS.start();

	newline(0, "I was created in the initialize function.", fontManager[16], 0, 30);
	newline(0, "I exist forever without any new updates.", fontManager[16], 0, 60);
	newline(0, "Just render me. Off I go.", fontManager[16], 0, 90);
}

bool Game::running() {
	return gameRunning;
}

void Game::buildFontManager() {
	//Load font sizes into fontManager for later use
	for (int i = 12; i <= 24; i += 2) {
		//Old font
		//fontManager[i] = TTF_OpenFont("bin/fonts/codenewroman.ttf", i);
		fontManager[i] = TTF_OpenFont("bin/fonts/montserratmedium.ttf", i);
		fontManagerBold[i] = TTF_OpenFont("bin/fonts/montserratbold.ttf", i);
	}
}

void Game::newline(int layer, std::string text, TTF_Font * gFont, int x, int y, SDL_Color textColor, int wrapLength) {
	//Creates a new texture in the staticText vector for being written once and printed at location
	staticText[layer].push_back(StaticTexture());
	staticText[layer].back().texture.loadFont(text, textColor, gFont, wrapLength);
	staticText[layer].back().x = x;
	staticText[layer].back().y = y;
}

void Game::clearLineLayer(int layer) {
	//add iterate through vector and call texture.free()
	staticText[layer].clear();
}

void Game::clearAllLineLayers() {
	for (int i = 0; i < MAX_STATICTEXT_LAYERS; i++) {
		//add iterate through vector and call texture.free()
		staticText[i].clear();
	}
}
