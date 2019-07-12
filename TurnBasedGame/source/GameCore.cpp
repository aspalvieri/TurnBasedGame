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
}

bool Game::running() {
	return gameRunning;
}

void Game::handleEvents() {
	while (SDL_PollEvent(&e) != 0) {
		//Update the user's mouse properties
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			*mouseButton = SDL_GetMouseState(&mousePos->first, &mousePos->second);
			mPos->x = mousePos->first;
			mPos->y = mousePos->second;
		}

		//User presses exit
		if (e.type == SDL_QUIT)
			gameRunning = false;
	}
}

void Game::update() {

}

void Game::render() {
	SDL_RenderClear(gRenderer);



	SDL_RenderPresent(gRenderer);
}
