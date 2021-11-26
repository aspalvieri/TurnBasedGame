#include "../header/Game.h"

//Returns false if it hit something
bool Game::checkAllCollision(CameraObj *ent) {
	bool success = true;

	//Dynamic casts for later use
	Projectile* proj = dynamic_cast<Projectile*>(ent);
	Entity* entit = dynamic_cast<Entity*>(ent);
	Enemy* enem = dynamic_cast<Enemy*>(ent);

	//Check all tiles within camera bounds
	for (int y = ent->camBounds->y; y <= ent->camBounds->h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = ent->camBounds->x; x <= ent->camBounds->w; x++) {
			if (tiles[x+yIndex].getCollide() /*&& checkCollision(ent->camera, &tiles[x+yIndex].getBox())*/ && checkCollision(&ent->getBox(), &tiles[x+yIndex].getBox())) {
				success = false;
			}
		}
	}

	////Entity collision
	//Player, other enemies, player projectiles, collide with Enemy
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if ((entit && entit != ((Entity*)&enemies[i]) && enemies[i].getCollide()) || (proj && proj->senderType == SENDER_TYPE_PLAYER)) {
			if (checkCollision(ent->camera, &enemies[i].getBox()) && checkCollision(&ent->getBox(), &enemies[i].getBox())) {
				success = false;
				if (proj)
					proj->hitTarget = &enemies[i];
			}
		}
	}
	//Enemy, enemy projectiles, collide with Player
	if ((enem && ent->getCollide()) || (proj && proj->senderType == SENDER_TYPE_ENEMY)) {
		if (checkCollision(ent->camera, &player.getBox()) && checkCollision(&ent->getBox(), &player.getBox())) {
			success = false;
			if (proj)
				proj->hitTarget = &player;
		}
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
		//Reset velocities
		if (ent->xVel != 0 || ent->yVel != 0) {
			ent->xVel = 0;
			ent->yVel = 0;
		}
		//Find recentlyHitID
		if (ent->recentlyHitID > -1) {
			ent->target = findEntityByID(ent->recentlyHitID);
			if (ent->target == NULL) {
				ent->recentlyHitID = -1;
				ent->recentlyHit = false;
			}
		}
		//Find player
		else if (checkCollision(ent->camera, &player.getBox())) {
			ent->target = &player;
		}
		
		//Set targetID
		if (ent->target)
			ent->targetID = ent->target->ID;
		else
			ent->targetID = -1;
	}
	//Chase target
	if (ent->target != NULL && (ent->targetID > -1 && findEntityByID(ent->targetID) && ent->target->ID == ent->targetID)) {
		//If an error occurs here, the enemy is trying to chase a target that exists in memory, but on ingame. This is due to vectors re-using memory addresses.
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

void Game::updateProjectile(Projectile * proj) {
	proj->update();
	if (proj->alive) {
		double xPos = proj->getPosition().first;
		double yPos = proj->getPosition().second;
		proj->setPosition(xPos + proj->xVel, yPos + proj->yVel);
		proj->distance += sqrt((abs(proj->xVel)*abs(proj->xVel)) + (abs(proj->yVel)*abs(proj->yVel)));
		if (!checkAllCollision(proj)) {
			proj->setToDie("Die");
			//Set projectile's size to a box for the 'explosion' effect
			if (proj->getSize().first < proj->getSize().second)
			{
				proj->setSize(proj->getSize().second, proj->getSize().second);
				proj->setPosition(proj->getBox().x - proj->getSize().second / 4.0, proj->getBox().y);
			}
			else if (proj->getSize().first > proj->getSize().second)
			{
				proj->setSize(proj->getSize().first, proj->getSize().first);
				proj->setPosition(proj->getBox().x, proj->getBox().y - proj->getSize().first / 4.0);
			}
			//If projectile hit an entity, deliver damage
			if (proj->hitTarget) {
				proj->hitTarget->takeDamage(proj->damage, proj->level);
				fTexts.push_back(FloatingText(to_string((int)round(proj->damage)), proj->hitTarget->getBox().x + proj->hitTarget->getBox().w / 2, 
					proj->hitTarget->getBox().y + proj->hitTarget->getBox().h / 4, proj->hitTarget->getBox().w, fontManager[18], SDL_Color{ 255,255,255 }));
				//If sender was player, update target UI
				if (proj->senderType == SENDER_TYPE_PLAYER) {
					player.recentlyHitTarget = true;
					player.recentlyHitTargetTimer = RECENTLY_HIT_TARGET_TIMEOUT;
					player.hitTarget = proj->hitTarget;
				}
				//If hitTarget is an enemy, update their recentlyHitID
				if (Enemy* enem = dynamic_cast<Enemy*>(proj->hitTarget)) {
					enem->recentlyHitID = proj->senderID;
				}
			}
		}
		if (proj->distance >= proj->maxDistance && proj->alive) {
			proj->setToDie("Time");
		}
	}
	proj->updateCamera();
}

Entity* Game::findEntityByID(int ID)
{
	//If player matches the ID
	if (player.ID == ID)
		return &player;
	//If any enemies match the ID
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (enemies[i].ID == ID)
			return &enemies[i];
	}
	//NULL if nothing matches ID
	return NULL;
}
