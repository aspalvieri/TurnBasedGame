#ifndef ENTITY_H
#define ENTITY_H

#include "CameraObj.h"

class Entity : public CameraObj {
public:
	Entity();
	~Entity();

	virtual void render();
	virtual void update();
	virtual bool canMove();

	//Entity Variables
	bool isPlayer = false, alive = false;
	double health = 0, healthmax = 0;
	double damagemin = 0, damagemax = 0;
	double xVel = 0, yVel = 0;
	double speed = 0;
	int level = 1, gold = 0;
	int armor = 0;

private:
	
};

#endif//ENTITY_H