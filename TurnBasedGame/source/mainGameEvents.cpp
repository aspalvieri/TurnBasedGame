#include "../header/Game.h"

void Game::mainGameEvents() {
	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_e:
			enemies.push_back(testEnemy);
			enemies.back().setPosition(mPosCam->x - 20, mPosCam->y - 20);
			enemies.back().setCamera();
			break;
		case SDLK_q:
			for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
				if (checkCollision(mPosCam, &enemy->getBox())) {
					enemy->alive = false;
				}
			}
			break;
		default:
			break;
		}
	}

	player.handleEvents(&e);
}
