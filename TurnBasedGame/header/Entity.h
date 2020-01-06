#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Tile.h"

class Entity : public Sprite {
public:
	Entity();
	~Entity();

	void render();
	virtual void update();
	virtual bool canMove();
	//Updates camera and camBounds for non-players
	virtual void updateCamera();

	void setBounds(int *mapMaxX, int *mapMaxY, int *indexMaxX, int *indexMaxY);
	void setBounds(int *mapMaxX, int *mapMaxY, int *indexMaxX, int *indexMaxY, int width, int height);
	//Can use setBounds instead 
	void setCameraBounds(int width, int height);
	void setCamera(SDL_Rect*); //For Player
	void setCamera(); //For Enemies

	//Entity Variables
	bool isPlayer = false, alive = false;
	SDL_Rect *camera, *camBounds;
	double health = 0, healthmax = 0;
	double damagemin = 0, damagemax = 0;
	double xVel = 0, yVel = 0;
	double speed = 0;
	int level = 1, gold = 0;
	int armor = 0;

protected:
	int *mapMaxX, *mapMaxY, *indexMaxX, *indexMaxY;
	int maxCameraW, maxCameraH;
};

#endif//ENTITY_H