#include "../header/Game.h"

void Game::mainGameUpdate() {
	updateEntity(&player);
	//Move player's light
	lights[0].setPosition(player.getBox().x + (player.getBox().w / 2.0), player.getBox().y + (player.getBox().h / 2.0));
	for (unsigned int i = 0; i < enemies.size(); i++) {
		chaseTarget(&enemies[i]);
		updateEntity(&enemies[i]);
	}

	for (unsigned int i = 0; i < projectiles.size(); i++) {
		updateProjectile(&projectiles[i]);
	}

	for (unsigned int i = 0; i < fTexts.size(); i++) {
		fTexts[i].update();
	}

	//Update mouse position relative to camera
	mPosCam->x = mPos->x + camera->x;
	mPosCam->y = mPos->y + camera->y;

	////  [BEGIN] CORE GAME UPDATES: ORDER MATTERS

	//Check if projectile died, remove if it did
	for (auto projectile = projectiles.begin(); projectile != projectiles.end(); projectile++) {
		if (projectile->die && projectile->finishedAnimation()) {
			projectiles.erase(projectile);
			projectile--;
		}
	}

	//Check if floating text expired
	for (auto fText = fTexts.begin(); fText != fTexts.end(); fText++)
	{
		if (!fText->alive)
		{
			fTexts.erase(fText);
			fText--;
		}
	}

	//Check if enemy died, remove if it did
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
		if (!enemy->alive) {
			//Remove any target references
			if (enemy._Ptr == player.hitTarget)
				player.hitTarget = NULL;
			if (enemy._Ptr == player.mouseTarget)
				player.mouseTarget = NULL;
			if (enemy._Ptr == player.target)
				player.target = NULL;
			enemy->onDeath();
			fTexts.push_back(FloatingText("+" + to_string((int)round(enemy->expReward)), enemy->getBox().x + enemy->getBox().w / 2,
				enemy->getBox().y + enemy->getBox().h / 4, enemy->getBox().w, fontManagerBold[24], SDL_Color{ 255,0,255 }));
			enemies.erase(enemy);
			enemy--;
		}
	}

	//Mock hover target
	player.mouseTarget = NULL;
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (checkCollision(mPosCam, &enemies[i].getBox()) && enemies[i].alive) {
			player.mouseTarget = &enemies[i];
		}
	}
	//Mock hover target

	////  [END] CORE GAME UPDATES

	//Update all shaders
	for (int y = camBounds.y; y <= camBounds.h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = camBounds.x; x <= camBounds.w; x++) {
			tiles[x + yIndex].shadow.calculateLight(lights, TimeClock::maxAlpha, true);
			for (int i = 0; i < 4; i++) {
				tiles[x + yIndex].black[i].calculateLight(lights, TimeClock::maxAlpha);
			}
		}
	}

	//Update clock
	updateText("clock", TimeClock::display());
	updateText("clockAlpha", to_string(TimeClock::alpha));

	//Update player variables on UI
	if (player.levelChanged) {
		player.levelChanged = false;
		updateText("playerLevel", "Level: " + to_string(player.level));
	}
	if (player.expChanged) {
		player.expChanged = false;
		updateText("playerExp", "Exp: " + to_string(player.exp) + "/" + to_string(player.maxExp));
	}
	if (player.goldChanged) {
		player.goldChanged = false;
		updateText("playerGold", "Gold: " + to_string(player.gold));
	}
	//If the game crashes here due to memory access violation, try re-writing this block
	if ((player.hitTarget && player.hitTarget->alive) || (player.mouseTarget && player.mouseTarget->alive)) {
		player.target = findEntityByID(((player.mouseTarget && player.mouseTarget->alive) ? player.mouseTarget->ID : player.hitTarget->ID));
		if (player.target) {
			//Update the text first, then the position since position is based on text size
			updateText("playerTargetName", player.target->name);
			updateText("playerTargetName", HALF_WIDTH - (int)(dynamicMap["playerTargetName"].width / 2.0), 0);
			updateText("playerTargetLevel", "Level: " + to_string(player.target->level));
			updateText("playerTargetLevel", HALF_WIDTH - (int)(dynamicMap["playerTargetLevel"].width / 2.0), 28);
			updateText("playerTargetHealth", "Health: " + to_string((int)round(player.target->health)) + " / " + to_string((int)round(player.target->maxHealth)));
			updateText("playerTargetHealth", HALF_WIDTH - (int)(dynamicMap["playerTargetHealth"].width / 2.0), 48);
		}
	}
	else {
		player.target = NULL;
	}

	//Test shooting
	if (*leftReleased) {
		projectiles.push_back(projectileMap["testBullet"]);
		projectiles.back().setPosition(player.getBox().x + (player.getBox().w / 2) - (projectileMap["testBullet"].getBox().w / 2), 
			player.getBox().y + (player.getBox().h / 2) - (projectileMap["testBullet"].getBox().h / 2));
		projectiles.back().setCamera();
		double speed = 12;
		double dist = 400;
		double deltaX = (mPos->x + camera->x) - (player.getPosition().first + (player.getBox().w / 2));
		double deltaY = (mPos->y + camera->y) - (player.getPosition().second + (player.getBox().h / 2));
		double xAng = (atan2(deltaY, deltaX)*180.0000) / 3.1416 + 90;
		double magnitude = sqrt(deltaX*deltaX + deltaY * deltaY);
		double xVelB = speed * (deltaX / magnitude);
		double yVelB = speed * (deltaY / magnitude);
		double dmg = rdevice.randomDouble(2, 5);
		projectiles.back().setSender(SENDER_TYPE_PLAYER, player.ID);
		projectiles.back().setVariables(xVelB, yVelB, xAng, dist, player.level, dmg);
	}

	//Pass time
	TimeClock::tick();
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
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i].render();
		//Mock highlight if target
		if ((Entity*)&enemies[i] == player.target) {
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 128);
			SDL_Rect n;
			n = { enemies[i].getBox().x - camera->x, enemies[i].getBox().y - camera->y, enemies[i].getBox().w, enemies[i].getBox().h };
			SDL_RenderDrawRect(gRenderer, &n);
		}
	}

	//Render tile shadows
	for (int y = camBounds.y; y <= camBounds.h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = camBounds.x; x <= camBounds.w; x++) {
			tiles[x + yIndex].shader.render();
			tiles[x + yIndex].shadow.render();
		}
	}

	//Render projectiles
	for (unsigned int i = 0; i < projectiles.size(); i++)
		projectiles[i].render();

	//Render day/night
	for (int y = camBounds.y; y <= camBounds.h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = camBounds.x; x <= camBounds.w; x++) {
			for (int i = 0; i < 4; i++) {
				tiles[x + yIndex].black[i].render();
			}
		}
	}

	//Render floating texts
	for (unsigned int i = 0; i < fTexts.size(); i++)
		fTexts[i].render();

	//test /displays camera outline
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 128);
	SDL_Rect n;
	for (unsigned int i = 0; i < enemies.size(); i++) {
		n = { enemies[i].camera->x - camera->x, enemies[i].camera->y - camera->y, enemies[i].camera->w, enemies[i].camera->h };
		SDL_RenderDrawRect(gRenderer, &n);
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 128);
	SDL_Rect d;
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		d = { projectiles[i].camera->x - camera->x, projectiles[i].camera->y - camera->y, projectiles[i].camera->w, projectiles[i].camera->h };
		SDL_RenderDrawRect(gRenderer, &d);
	}
	//test

	//Render UI
	dynamicMap["playerLevel"].render();
	dynamicMap["playerExp"].render();
	dynamicMap["playerGold"].render();
	if (player.target != NULL) {
		dynamicMap["playerTargetName"].render();
		dynamicMap["playerTargetLevel"].render();
		dynamicMap["playerTargetHealth"].render();
	}
	dynamicMap["clock"].render();
	dynamicMap["clockAlpha"].render();
}
