#include "../header/Game.h"

Game::Game() {
	gRenderer = SDLR::gRenderer;
	gWindow = SDLR::gWindow;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	srand((unsigned)time(0));

	camera = &SDLR::camera;
	mousePos = &SDLR::mousePosition;
	mouseButton = &SDLR::mouseButton;
	mPos = &SDLR::mPos;
}

Game::~Game() {

}

void Game::initialize() {
	gameRunning = true;
	buildFontManager();
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
		fontManager[i] = TTF_OpenFont("bin/fonts/codenewroman.ttf", i);
	}
}

void Game::update() {
	//Update FPS and text
	averageFPS = countedFrames / (FPS.getTicks() / 1000.f);
	fpsText.loadFont(to_string(averageFPS), SDL_Color{ 0,0,0 }, fontManager[18], SCREEN_WIDTH);


}

void Game::render() {
	SDL_RenderClear(gRenderer);

	fpsText.render(0, 0);

	SDL_RenderPresent(gRenderer);
}

