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
	virtual void takeDamage(double dam, int lvl);

	//Enemy functions
	Enemy& setGoldReward(int min, int max);
	Enemy& setExpReward(int min, int max);
	Enemy& setPlayerPtr(Entity* ptr);
	Enemy& setProjectileMap(unordered_map<string, Projectile> * ptr);
	// .. Level .. Health .. Armor .. Speed .. Name
	Enemy& setBaseValues(int level, double health, int armor, double speed, string name);
	Enemy& setDamage(double min, double max, int rate);

	//target ptr is only used in chasing
	Entity *target = NULL, *playerPtr = NULL;
	int targetID = -1;
	unordered_map<string, Projectile> *projectileMap = NULL;
	vector<Projectile> *projectiles = NULL;

	//Enemy variables
	bool isBoss = false, recentlyHit = false;
	int goldRewardMin = 0, goldRewardMax = 0, goldReward = 0;
	int expRewardMin = 0, expRewardMax = 0, expReward = 0;
	int recentlyHitTimer = 0, recentlyHitID = -1;

private:

};

#endif//ENEMY_H