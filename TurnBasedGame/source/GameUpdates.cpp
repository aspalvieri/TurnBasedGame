#include "../header/Game.h"

void Game::update() {
	//Update FPS and text
	averageFPS = countedFrames / (FPS.getTicks() / 1000.f);
	fpsText.loadFont("FPS: " + to_string((int)round(averageFPS)), SDL_Color{ 255, 255, 255 }, fontManager[16], SCREEN_WIDTH);

	//Handle updates for the current game screen
	routeManager(1);
}

void Game::render() {
	SDL_RenderClear(gRenderer);

	//Render images for the current game screen
	routeManager(0);

	//Render FPS text
	fpsText.render(0, 0);

	SDL_RenderPresent(gRenderer);
}

//for (unsigned int i = 0; i < vector.size(); i++)
//vector.erase(remove_if(vector.begin(), vector.end(), bool/function/ternary), vector.end());
