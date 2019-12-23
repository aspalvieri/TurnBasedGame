#include "../header/Game.h"

bool Game::checkAllCollision(Entity *ent) {
	bool success = true;

	//Check all tiles
	for (int y = ent->camBounds->y; y <= ent->camBounds->h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = ent->camBounds->x; x <= ent->camBounds->w; x++) {
			if (tiles[x+yIndex].getCollide() /*&& checkCollision(cam, &tiles[x+yIndex].getBox())*/ && checkCollision(&ent->getSpriteReference().getBox(), &tiles[x+yIndex].getBox())) {
				success = false;
			}
		}
	}

	//Map bounds for Player
	if (ent->isPlayer) {
		if (ent->getSpriteReference().getBox().x < 0 || ent->getSpriteReference().getBox().y < 0
			|| ent->getSpriteReference().getBox().x + ent->getSpriteReference().getBox().w > mapMaxX
			|| ent->getSpriteReference().getBox().y + ent->getSpriteReference().getBox().h > mapMaxY) {
			success = false;
		}
	}

	return success;
}

void Game::updateEntity(Entity *ent) {
	ent->update();
	if (ent->canMove()) {
		//Move entity's X position then check for collisions
		double xPos = ent->getSpriteReference().getPosition().first;
		double yPos = ent->getSpriteReference().getPosition().second;
		ent->getSpriteReference().setPosition(xPos + ent->xVel, yPos);
		if (!checkAllCollision(ent)) {
			//If it collided, undo it
			ent->getSpriteReference().setPosition(xPos, yPos);
		}

		//Move entity's Y position then check for collisions
		xPos = ent->getSpriteReference().getPosition().first;
		yPos = ent->getSpriteReference().getPosition().second;
		ent->getSpriteReference().setPosition(xPos, yPos + ent->yVel);
		if (!checkAllCollision(ent)) {
			//If it collided, undo it
			ent->getSpriteReference().setPosition(xPos, yPos);
		}
	}
	//Update camera and camBounds
	ent->updateCamera();
}
