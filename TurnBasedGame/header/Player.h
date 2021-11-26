#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Projectile.h"

class Player : public Entity {
public:
	Player();
	~Player();

	//Polymorphism from Entity
	void update();
	bool canMove();
	void onDeath();

	//Player functions
	void handleEvents(SDL_Event *e);
	Player& setProjectileMap(unordered_map<string, Projectile> *ptr);

	//Player variables
	Entity *hitTarget = NULL, *mouseTarget = NULL, *target = NULL;
	unordered_map<string, Projectile> *projectileMap = NULL;
	vector<Projectile> *projectiles = NULL;

	//Update variables
	bool recentlyHitTarget = false;
	int recentlyHitTargetTimer = 0;
	
private:
	bool up = false, down = false, right = false, left = false;
};

#endif//PLAYER_H