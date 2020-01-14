#include "../header/Game.h"

void Game::mainGameBuild() {
	newImage("tileset", "bin/images/tilesheet.png");
	newImage("shaders", "bin/images/shaders.png");
	buildTileset();
	//To set specific properties for tiles, do it after buildTileset() but before buildTiles(), since default is false:
	setTileProps({ 7 }, { true, false, true, true, true });
	setTileProps({ 8, 9 }, { true, true, false, true, false });
	buildTiles("bin/maps/map1.csv");

	//Player
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
	player.maxExp = 100;
	player.name = "Player";
	player.setBounds(&mapMaxX, &mapMaxY, &indexMaxX, &indexMaxY, SCREEN_WIDTH, SCREEN_HEIGHT);
	player.setCamera(&camBounds);
	//Player screen variables
	newText("playerLevel", "Level: " + to_string(player.level), fontManager[16], 0, 32);
	newText("playerExp", "Exp: " + to_string(player.exp) + "/" + to_string(player.maxExp), fontManager[16], 0, 48);
	newText("playerGold", "Gold: " + to_string(player.gold), fontManager[16], 0, 64);
	newText("playerTargetName", " ", fontManagerBold[24], 0, 0, { 255, 255, 255 });
	newText("playerTargetLevel", " ", fontManager[24], 0, 0, { 192, 192, 192 });

	//TestEnemy
	testEnemy.loadSpriteImage("bin/images/testenemy.png")
		.setFrameSize(40, 40)
		.setSize(40, 40)
		.setCollide(true)
		.setDelay(3)
		.pushFrame("Idle", 0, 0)
		.pushFrameRow("Moving", 0, 40, 40, 0, 10)
		.setAnimation("Idle");
	testEnemy.setPlayerPtr(&player)
		.setBaseValues(1, 10, 0, 2, "Test Enemy")
		.setDamage(1, 3, 30)
		.setGoldReward(3, 9)
		.setExpReward(9, 15);
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
