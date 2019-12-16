#include "../header/Game.h"

bool Game::checkAllCollision(Entity *ent) {
	bool success = true;

	//All entities have a camera. Remember to update the camBounds for them!
	SDL_Rect *bounds = NULL, *cam = NULL;
	if (ent->isPlayer) {
		bounds = &camBounds;
		cam = camera;
	}
	else {
		bounds = &ent->camBounds;
		cam = &ent->camera;
	}

	//Check all tiles
	for (int y = bounds->y; y <= bounds->h; y++) {
		int yIndex = y * indexMaxX;
		for (int x = bounds->x; x <= bounds->w; x++) {
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
		if (ent->isPlayer && ent->xVel != 0 && ent->yVel != 0) {
			ent->xVel /= sqrt(2.0);
			ent->yVel /= sqrt(2.0);
		}
		double xPos = ent->getSpriteReference().getPosition().first;
		double yPos = ent->getSpriteReference().getPosition().second;
		ent->getSpriteReference().setPosition(xPos + ent->xVel, yPos);
		if (!checkAllCollision(ent)) {
			ent->getSpriteReference().setPosition(xPos, yPos);
		}

		xPos = ent->getSpriteReference().getPosition().first;
		yPos = ent->getSpriteReference().getPosition().second;
		ent->getSpriteReference().setPosition(xPos, yPos + ent->yVel);
		if (!checkAllCollision(ent)) {
			ent->getSpriteReference().setPosition(xPos, yPos);
		}
	}
	//Update camera and camBounds for non-players
	if (!ent->isPlayer) {
		ent->updateCamera();
	}
}

void Game::updateCamera() {
	camera->x = (player.getBox().x + (player.getBox().w / 2) - (SCREEN_WIDTH / 2));
	camera->y = (player.getBox().y + (player.getBox().h / 2) - (SCREEN_HEIGHT / 2));

	if (camera->x < 0)
		camera->x = 0;

	if (camera->y < 0)
		camera->y = 0;

	if (camera->x > mapMaxX - camera->w)
		camera->x = mapMaxX - camera->w;

	if (camera->y > mapMaxY - camera->h)
		camera->y = mapMaxY - camera->h;

	camBounds.x = camera->x / TILE_SIZE;
	camBounds.y = camera->y / TILE_SIZE;
	camBounds.w = (camera->x + camera->w) / TILE_SIZE;
	camBounds.h = (camera->y + camera->h) / TILE_SIZE;
	
	if (camBounds.w + 1 > indexMaxX - 1)
		camBounds.w = indexMaxX - 1;

	if (camBounds.h + 1 > indexMaxY - 1)
		camBounds.h = indexMaxY - 1;
}
