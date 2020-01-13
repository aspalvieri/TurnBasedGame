#include "../header/Enemy.h"

Enemy::Enemy() {
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

void Enemy::onDeath() {
	cout << "Enemy: I was killed.\n";
	playerPtr->changeGold(SDLR::rand.randomInt(goldRewardMin, goldRewardMax));
	playerPtr->changeExp(SDLR::rand.randomInt(expRewardMin, expRewardMax));
}

Enemy& Enemy::setGoldReward(int min, int max)
{
	goldRewardMin = min;
	goldRewardMax = max;
	return *this;
}

Enemy& Enemy::setExpReward(int min, int max)
{
	expRewardMin = min;
	expRewardMax = max;
	return *this;
}

Enemy & Enemy::setPlayerPtr(Entity * ptr)
{
	playerPtr = ptr;
	return *this;
}

Enemy & Enemy::setBaseValues(int level, double health, int armor, double speed, string name)
{
	this->level = level;
	this->health = health;
	this->maxHealth = health;
	this->armor = armor;
	this->speed = speed;
	this->name = name;
	return *this;
}

Enemy & Enemy::setDamage(double min, double max, int rate)
{
	damageMin = min;
	damageMax = max;
	reload = rate;
	return *this;
}
