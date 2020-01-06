#include "../header/Enemy.h"

Enemy::Enemy() {
	target = NULL;
	alive = true;
}

Enemy::~Enemy() { }

void Enemy::update()
{
	Entity::update();

	//Animations
	if (canMove())
		Sprite::setAnimationRaw("Moving");
	else
		Sprite::setAnimationRaw("Idle");
}

bool Enemy::canMove()
{
	if (xVel != 0 || yVel != 0)
		return true;
	return false;
}
