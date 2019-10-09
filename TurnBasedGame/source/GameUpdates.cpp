#include "../header/Game.h"

void Game::update() {
	//Update FPS and text
	averageFPS = countedFrames / (FPS.getTicks() / 1000.f);
	fpsText.loadFont(to_string(averageFPS), SDL_Color{ 0,0,0 }, fontManager[16], SCREEN_WIDTH);


}

void Game::render() {
	SDL_RenderClear(gRenderer);

	fpsText.render(0, 0);

	SDL_RenderPresent(gRenderer);
}
