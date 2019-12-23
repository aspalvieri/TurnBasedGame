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
		.setCamera(true)
		.setDelay(3)
		.pushFrame("Idle", 0, 0)
		.pushFrameRow("Moving", 0, 40, 40, 0, 10)
		.setAnimation("Idle")
		.setPosition(96, 96);
	player.speed = 3;
	player.setBounds(&mapMaxX, &mapMaxY, &indexMaxX, &indexMaxY, SCREEN_WIDTH, SCREEN_HEIGHT);
	player.setCamera(&camBounds);
}

void Game::mainGameDestroy() {
	clearTiles();
	clearClipsets();
	clearDynamicMap(); //Destroys all newTexts and newImages
}

void Game::mainGameEvents() {
	player.handleEvents(&e);
}
