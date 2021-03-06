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

	//Player variables
	Entity *target = NULL;

	//Update variables
	void changeTarget(Entity *tar = NULL);
	bool targetChanged = false;
	
private:
	bool up = false, down = false, right = false, left = false;
};

#endif//PLAYER_H