#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy();
	~Enemy();

	void update();
	bool canMove();

	Entity *target;
private:

};

#endif//ENEMY_H