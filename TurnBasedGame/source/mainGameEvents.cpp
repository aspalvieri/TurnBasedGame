#include "../header/Game.h"

void Game::mainGameEvents() {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		//Test::kill enemy on cursor
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
	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		//Test::create enemy on cursor
		case SDLK_e:
			for (int i = 0; i < 10; i++) {
				enemies.push_back(testEnemy);
				enemies.back().ID = Entity::globalID++;
				enemies.back().setPosition(mPosCam->x - 20, mPosCam->y - 20);
				enemies.back().setCamera();
				//Test spawn block prevention
				while (spawnCheck == true) {
					forceMoved = false;
					if (enemies.back().forceMove(collisionCases[collisionBlock].first * collisionMod, collisionCases[collisionBlock].second * collisionMod))
						forceMoved = true;
					enemies.back().updateCamera();
					if (checkAllCollision(&enemies.back()) == false) {
						if (forceMoved)
							enemies.back().forceMove(-collisionCases[collisionBlock].first * collisionMod, -collisionCases[collisionBlock].second * collisionMod);
						if (++collisionBlock >= 8) {
							collisionBlock = 0;
							collisionMod += 5;
						}
					}
					else {
						spawnCheck = false;
						collisionBlock = 0;
						collisionMod = 5;
					}
				}
				spawnCheck = true;
				cout << "Created enemy with ID: " << enemies.back().ID << ".\n";
			}
			break;
		//Test::Show all dynamic map keys
		case SDLK_PERIOD:
			cout << "\nALL KNOWN dynamicMap KEYS:\n";
			for (auto map = dynamicMap.begin(); map != dynamicMap.end(); map++) {
				cout << map->first << "\n";
			}
			cout << endl;
			break;
		default:
			break;
		}
	}

	player.handleEvents(&e);
}
