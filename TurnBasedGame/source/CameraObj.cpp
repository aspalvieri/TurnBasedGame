#include "../header/CameraObj.h"

CameraObj::CameraObj() {

}

CameraObj::~CameraObj() {

}

void CameraObj::setBounds(int *mapMaxX, int *mapMaxY, int *indexMaxX, int *indexMaxY) {
	this->mapMaxX = mapMaxX;
	this->mapMaxY = mapMaxY;
	this->indexMaxX = indexMaxX;
	this->indexMaxY = indexMaxY;
}

void CameraObj::setBounds(int *mapMaxX, int *mapMaxY, int *indexMaxX, int *indexMaxY, int width, int height) {
	this->mapMaxX = mapMaxX;
	this->mapMaxY = mapMaxY;
	this->indexMaxX = indexMaxX;
	this->indexMaxY = indexMaxY;
	setCameraBounds(width, height);
}

void CameraObj::setCameraBounds(int width, int height) {
	maxCameraW = width;
	maxCameraH = height;
}

//For Player
void CameraObj::setCamera(SDL_Rect *camBounds) {
	this->camBounds = camBounds;
	this->camera = &SDLR::camera;
	updateCamera();
}

//For Non-Players
void CameraObj::setCamera() {
	this->camBounds = new SDL_Rect;
	this->camera = new SDL_Rect;
	this->camera->w = maxCameraW;
	this->camera->h = maxCameraH;
	updateCamera();
}

void CameraObj::updateCamera() {
	camera->x = (getBox().x + (getBox().w / 2) - (maxCameraW / 2));
	camera->y = (getBox().y + (getBox().h / 2) - (maxCameraH / 2));

	if (camera->x < 0)
		camera->x = 0;

	if (camera->y < 0)
		camera->y = 0;

	if (camera->x > *mapMaxX - camera->w)
		camera->x = *mapMaxX - camera->w;

	if (camera->y > *mapMaxY - camera->h)
		camera->y = *mapMaxY - camera->h;

	camBounds->x = camera->x / TILE_SIZE;
	camBounds->y = camera->y / TILE_SIZE;
	camBounds->w = (camera->x + camera->w) / TILE_SIZE;
	camBounds->h = (camera->y + camera->h) / TILE_SIZE;

	if (camBounds->w + 1 > *indexMaxX - 1)
		camBounds->w = *indexMaxX - 1;

	if (camBounds->h + 1 > *indexMaxY - 1)
		camBounds->h = *indexMaxY - 1;
}
