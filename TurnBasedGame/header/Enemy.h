#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Projectile.h"

class Enemy : public Entity {
public:
	Enemy();
	~Enemy();

	//Polymorphism from Entity
	virtual void update();
	virtual bool canMove();
	virtual void onDeath();

	//Enemy functions
	Enemy& setGoldReward(int min, int max);
	Enemy& setExpReward(int min, int max);
	Enemy& setPlayerPtr(Entity* ptr);
	// .. Level .. Health .. Armor .. Speed .. Name
	Enemy& setBaseValues(int level, double health, int armor, double speed, string name);
	Enemy& setDamage(double min, double max, int rate);

	Entity *target = NULL, *playerPtr = NULL;

	//Enemy variables
	bool isBoss = false;
	int goldRewardMin = 0, goldRewardMax = 0;
	int expRewardMin = 0, expRewardMax = 0;

private:

};

#endif//ENEMY_H