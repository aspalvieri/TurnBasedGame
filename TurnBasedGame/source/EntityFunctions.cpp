#include "../header/Game.h"

bool Game::checkAllCollision(Entity *ent) {
	bool success = true;

	//Check all tiles
	for (int y = ent->camBounds->y; y <= ent->camBounds->h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = ent->camBounds->x; x <= ent->camBounds->w; x++) {
			if (tiles[x+yIndex].getCollide() /*&& checkCollision(cam, &tiles[x+yIndex].getBox())*/ && checkCollision(&ent->getBox(), &tiles[x+yIndex].getBox())) {
				success = false;
			}
		}
	}

	////Entity collision
	//All collides with enemy
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (ent != ((Entity*)&enemies[i])) {
			if (enemies[i].getCollide() && checkCollision(camera, &enemies[i].getBox()) && checkCollision(&ent->getBox(), &enemies[i].getBox())) {
				success = false;
			}
		}
	}
	//Enemy collides with player
	if (!ent->isPlayer && ent->getCollide() && checkCollision(ent->camera, &player.getBox()) && checkCollision(&ent->getBox(), &player.getBox())) {
		success = false;
	}

	return success;
}

void Game::updateEntity(Entity *ent) {
	ent->update();
	if (ent->canMove()) {
		//Move entity's X position then check for collisions
		double xPos = ent->getPosition().first;
		double yPos = ent->getPosition().second;
		ent->setPosition(xPos + ent->xVel, yPos);
		if (!checkAllCollision(ent)) {
			//If it collided, undo it
			ent->setPosition(xPos, yPos);
		}

		//Move entity's Y position then check for collisions
		xPos = ent->getPosition().first;
		yPos = ent->getPosition().second;
		ent->setPosition(xPos, yPos + ent->yVel);
		if (!checkAllCollision(ent)) {
			//If it collided, undo it
			ent->setPosition(xPos, yPos);
		}
	}
	//Update camera and camBounds
	ent->updateCamera();
}

void Game::chaseTarget(Enemy *ent) {
	//Find target
	if (ent->target == NULL) {
		ent->xVel = 0;
		ent->yVel = 0;
		if (checkCollision(ent->camera, &player.getBox())) {
			ent->target = &player;
		}
	}
	//Chase target
	if (ent->target != NULL) {
		deltaX = (ent->target->getBox().x + (ent->target->getBox().w / 2)) - (ent->getBox().x + (ent->getBox().w / 2));// +(player.xVel * ((double)player.getBox().w / divvy));
		deltaY = (ent->target->getBox().y + (ent->target->getBox().h / 2)) - (ent->getBox().y + (ent->getBox().h / 2));// +(player.yVel * ((double)player.getBox().h / divvy));
		magnitude = sqrt(deltaX*deltaX + deltaY * deltaY);
		ent->xVel = ent->speed * (deltaX / magnitude);
		ent->yVel = ent->speed * (deltaY / magnitude);
		//Ensure target
		if (!checkCollision(ent->camera, &ent->target->getBox())) {
			ent->target = NULL;
		}
	}
}
