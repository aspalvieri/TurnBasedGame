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
}

bool Game::running() {
	return gameRunning;
}

void Game::buildFontManager()
{
	//Load font sizes into fontManager for later use
	for (int i = 12; i <= 24; i += 2)
	{
		//Old font
		//fontManager[i] = TTF_OpenFont("bin/fonts/codenewroman.ttf", i); //All even sizes works
		fontManager[i] = TTF_OpenFont("bin/fonts/pressstarttoplay.ttf", i); //12,16,20,24 works
	}
}
