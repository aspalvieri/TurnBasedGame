#include "../header/Game.h"

void Game::mainGameBuild() {
	newImage("tileset", "bin/images/tilesheet.png");
	newImage("shaders", "bin/images/shaders.png");
	buildTileset();
	//To set specific properties for tiles, do it after buildTileset() but before buildTiles(), since default is false:
	setTileProps({ 7 }, { true, false, true, true, true });
	setTileProps({ 8, 9 }, { true, true, false, true, false });
	buildTiles("bin/maps/map1.csv");

	player.loadSpriteImage("bin/images/player.png")
		.setFrameSize(PLAYER_SIZE, PLAYER_SIZE)
		.setSize(PLAYER_SIZE, PLAYER_SIZE)
		.setCollide(true)
		.setDelay(3)
		.pushFrame("Idle", 0, 0)
		.pushFrameRow("Moving", 0, 40, 40, 0, 10)
		.setAnimation("Idle")
		.setPosition(96, 96);
	player.speed = 4;
	player.setBounds(&mapMaxX, &mapMaxY, &indexMaxX, &indexMaxY, SCREEN_WIDTH, SCREEN_HEIGHT);
	player.setCamera(&camBounds);

	testEnemy.loadSpriteImage("bin/images/testenemy.png")
		.setFrameSize(40, 40)
		.setSize(40, 40)
		.setCollide(true)
		.setDelay(3)
		.pushFrame("Idle", 0, 0)
		.pushFrameRow("Moving", 0, 40, 40, 0, 10)
		.setAnimation("Idle");
	testEnemy.speed = 2;
	testEnemy.setBounds(&mapMaxX, &mapMaxY, &indexMaxX, &indexMaxY, 300, 300);

	enemies.push_back(testEnemy);
	enemies.back().setPosition(600, 420);
	enemies.back().setCamera();

	enemies.push_back(testEnemy);
	enemies.back().setPosition(120, 500);
	enemies.back().setCamera();
}

void Game::mainGameDestroy() {
	clearTiles();
	clearClipsets();
	clearDynamicMap(); //Destroys all newTexts and newImages
}

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
				if (checkCollision(mPosCam, &enemy._Ptr->getBox())) {
					enemies.erase(enemy);
					enemy--;
				}
			}
			break;
		default:
			break;
		}
	}

	player.handleEvents(&e);
}
