#include "../header/Game.h"

void Game::mainGameUpdate() {
	updateEntity(&player);
}

void Game::mainGameRender() {
	//Render all tiles
	for (int y = camBounds.y; y <= camBounds.h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = camBounds.x; x <= camBounds.w; x++) {
			tiles[x + yIndex].render();
			//tiles[x + yIndex].shader.render();
		}
	}

	player.render();

	//Render all shaders
	for (int y = camBounds.y; y <= camBounds.h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = camBounds.x; x <= camBounds.w; x++) {
			tiles[x + yIndex].shader.render();
			tiles[x + yIndex].shadow.render();
		}
	}
}
