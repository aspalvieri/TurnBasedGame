#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public CameraObj {
public:
	Projectile();
	~Projectile();

	virtual void update();
	virtual void render();
	void setVariables(double xVel, double yVel, double angle, double maxDistance, int level, double damage, int ID = -1, double lifeSteal = 0);
	void setSender(int type, int id);
	//Standard animations: Idle, Time, Die
	void setToDie(string anim);

	int senderType = -1, senderID = -1, targetID = -1;
	//Try not to use this outside of EntityFunctions
	//because the pointer reference isn't set to a new one when an enemy is
	//removed from the vector. Use IDs for picking them.
	Entity *hitTarget = NULL; //If projectile hit something

	double damage = 0, lifeSteal = 0;
	double xVel = 0, yVel = 0, angle = 0, distance = 0, maxDistance = 0;
	int level = 0;
	int ID = -1;

	bool alive = true, die = false;

private:

};

#endif//PROJECTILE_H