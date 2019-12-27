#include "../header/Game.h"

void Game::mainGameUpdate() {
	updateEntity(&player);
	for (unsigned int i = 0; i < enemies.size(); i++) {
		chaseTarget(&enemies[i]);
		updateEntity(&enemies[i]);
	}

	//Update mouse position relative to camera
	mPosCam->x = mPos->x + camera->x;
	mPosCam->y = mPos->y + camera->y;
}

void Game::mainGameRender() {
	//Render all tiles
	for (int y = camBounds.y; y <= camBounds.h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = camBounds.x; x <= camBounds.w; x++) {
			tiles[x + yIndex].render();
		}
	}

	//Render entities
	player.render();
	for (unsigned int i = 0; i < enemies.size(); i++)
		enemies[i].render();

	//test /displays camera outline
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0.5);
	SDL_Rect n;
	for (unsigned int i = 0; i < enemies.size(); i++) {
		n = { enemies[i].camera->x - camera->x, enemies[i].camera->y - camera->y, enemies[i].camera->w, enemies[i].camera->h };
		SDL_RenderDrawRect(gRenderer, &n);
	}
	//test

	//Render all shaders
	for (int y = camBounds.y; y <= camBounds.h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = camBounds.x; x <= camBounds.w; x++) {
			tiles[x + yIndex].shader.render();
			tiles[x + yIndex].shadow.render();
		}
	}
}
