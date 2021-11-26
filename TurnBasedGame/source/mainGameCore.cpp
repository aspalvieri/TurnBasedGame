#include "../header/Game.h"

void Game::mainGameBuild() {
	newImage("tileset", "bin/images/tilesheet.png");
	newImage("shaders", "bin/images/shaders.png");
	buildTileset();
	//To set specific properties for tiles, do it after buildTileset() but before buildTiles(), since default is false:
	setTileProps({ 6, 7 }, { true, false, true, true, true });
	buildMap("bin/maps/map1.csv");
	newText("clock", TimeClock::display(), fontManagerBold[18], 0, 128, { 255, 255, 255 });
	newText("clockAlpha", to_string(TimeClock::alpha), fontManager[18], 0, 152, { 255, 255, 255 });

	//Projectiles
	#pragma region Projectiles
	projectileMap["testBullet"].loadSpriteImage("bin/images/bulletsheet.png")
		.setFrameSize(40, 40)
		.setPosition(0, 0)
		.setSize(10, 20)
		.setDelay(1)
		.pushFrameRow("Idle", 0, 0, 40, 0, 4) //Standard for when moving
		.pushFrameRow("Time", 0, 40, 40, 0, 4) //If bullet timed out (reached travel distance)
		.pushFrameRow("Die", 0, 80, 40, 0, 5) //If bullet hit something
		.setAnimation("Idle");
	projectileMap["testBullet"].setBounds(&mapMaxX, &mapMaxY, &indexMaxX, &indexMaxY, 100, 100);
	#pragma endregion

	//Player
	#pragma region Player
	player.loadSpriteImage("bin/images/player.png")
		.setFrameSize(PLAYER_SIZE, PLAYER_SIZE)
		.setSize(PLAYER_SIZE, PLAYER_SIZE)
		.setCollide(true)
		.setDelay(3)
		.pushFrame("Idle", 0, 0)
		.pushFrameRow("Moving", 0, 40, 40, 0, 10)
		.setAnimation("Idle")
		.setPosition(144, 144);
	player.setProjectileMap(&projectileMap);
	player.ID = Entity::globalID++;
	player.speed = 4;
	player.maxExp = 100;
	player.name = "Player";
	player.setBounds(&mapMaxX, &mapMaxY, &indexMaxX, &indexMaxY, SCREEN_WIDTH, SCREEN_HEIGHT);
	player.setCamera(&camBounds);
	lights.push_back(Light(player.getBox().x + (player.getBox().w / 2.0), player.getBox().y + (player.getBox().h / 2.0), 1.7, 1.8)); //Player's light
	//Player screen variables
	newText("playerLevel", "Level: " + to_string(player.level), fontManager[16], 0, 32, { 255, 255, 255 });
	newText("playerExp", "Exp: " + to_string(player.exp) + "/" + to_string(player.maxExp), fontManager[16], 0, 48, { 255,255,255 });
	newText("playerGold", "Gold: " + to_string(player.gold), fontManager[16], 0, 64, { 255,255,255 });
	newText("playerTargetName", " ", fontManagerBold[24], 0, 0, { 255, 255, 255 });
	newText("playerTargetLevel", " ", fontManager[18], 0, 0, { 192, 192, 192 });
	newText("playerTargetHealth", " ", fontManager[24], 0, 0, { 255, 255, 0 });
	#pragma endregion

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
		.setProjectileMap(&projectileMap)
		.setBaseValues(1, 25, 0, 2, "Test Enemy")
		.setDamage(1, 3, 30)
		.setGoldReward(3, 9)
		.setExpReward(9, 15);
	testEnemy.setBounds(&mapMaxX, &mapMaxY, &indexMaxX, &indexMaxY, 300, 300);

	enemies.push_back(testEnemy);
	enemies.back().ID = Entity::globalID++;
	enemies.back().setPosition(600, 420);
	enemies.back().setCamera();

	enemies.push_back(testEnemy);
	enemies.back().ID = Entity::globalID++;
	enemies.back().setPosition(120, 500);
	enemies.back().setCamera();

#if DISPLAY_DEBUG
	cout << "Built mainGame.\n";
#endif
}

void Game::mainGameDestroy() {
	clearTiles();
	clearClipsets();
	clearDynamicMap(); //Destroys all newTexts and newImages
	enemies.clear();
	projectiles.clear();
	fTexts.clear();
	lights.clear();
#if DISPLAY_DEBUG
	cout << "Destroyed mainGame.\n";
#endif
}
