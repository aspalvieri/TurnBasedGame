#include "../header/Game.h"

void Game::mainGameBuild() {
	newImage("tileset", "bin/images/tilesheet.png");
	newImage("shaders", "bin/images/shaders.png");
	buildTileset();
	//To set specific collision for tiles, do it after buildTileset() but before buildTiles(), since default is false:
	//First bool is collision
	//Second bool is if the tile can have shadows cast on it
	//Third bool is if the tile casts a shadow
	tileClips[5].second = { true, false, true };
	buildTiles("bin/maps/map1.csv");

	player.loadSpriteImage("bin/images/player.png")
		.setFrameSize(PLAYER_SIZE, PLAYER_SIZE)
		.setSize(PLAYER_SIZE, PLAYER_SIZE)
		.setCollide(true)
		.setCamera(true)
		.setDelay(3)
		.pushFrame("Idle", 0, 0)
		.pushFrameRow("Moving", 0, 40, 40, 0, 10)
		.setAnimation("Idle")
		.setPosition(0, 0);
	player.speed = 4;

	updateCamera(); //Initial update to set bounds
}

void Game::mainGameDestroy() {
	clearTiles();
	clearDynamicMap(); //Destroys all newTexts and newImages
	tileClips.clear();
}

void Game::mainGameEvents() {
	player.handleEvents(&e);
}
