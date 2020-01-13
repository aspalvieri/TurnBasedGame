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
	virtual void onDeath();

	//Entity Variables
	bool isPlayer = false, alive = false;
	string name = "";
	double health = 0, maxHealth = 0;
	double damageMin = 0, damageMax = 0;
	int reload = 0; //The rate at which bullets fire. Ex: 60 reload means 1 shot per second
	int reloading = 0; //The current reloading timer, stops when it hits "reload" number
	double xVel = 0, yVel = 0;
	double speed = 0;
	int level = 1, gold = 0;
	int exp = 0, maxExp = 0;
	int armor = 0;

	//Update Variables
	void changeGold(int);
	bool goldChanged = false;
	void changeExp(int);
	bool expChanged = false;
	void levelUp();
	bool levelChanged = false;

private:
	
};

#endif//ENTITY_H