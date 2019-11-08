#include "../header/Game.h"

void Game::update() {
	//Update FPS and text
	averageFPS = countedFrames / (FPS.getTicks() / 1000.f);
	fpsText.loadFont(to_string(averageFPS), SDL_Color{ 0,0,0 }, fontManager[16], SCREEN_WIDTH);

	
}

void Game::render() {
	SDL_RenderClear(gRenderer);

	fpsText.render(0, 0);

	//Render all line layers on layer 0. there are MAX_STATICTEXT_LAYERS # of layers.
	//Line layers are split like this so you can layer images overtop the text layer
	//The purpose of line layers is to loadFont once and render many times
	for (auto& line : staticText[0])
		line.texture.render(line.x, line.y);

	SDL_RenderPresent(gRenderer);
}

//for (unsigned int i = 0; i < vector.size(); i++)
//vector.erase(remove_if(vector.begin(), vector.end(), bool/function/ternary), vector.end());