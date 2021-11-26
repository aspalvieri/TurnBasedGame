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

	//Recently hit timeout
	if (recentlyHit) {
		recentlyHitTimer--;
		if (recentlyHitTimer <= 0 || recentlyHitID == -1) {
			recentlyHit = false;
			recentlyHitID = -1;
		}
	}
}

bool Enemy::canMove()
{
	if (xVel != 0 || yVel != 0)
		return true;
	return false;
}

void Enemy::onDeath() {
#if DISPLAY_DEBUG
	cout << "Enemy: I was killed. ID: " << ID << "\n";
#endif
	goldReward = SDLR::rand.randomInt(goldRewardMin, goldRewardMax);
	expReward = SDLR::rand.randomInt(expRewardMin, expRewardMax);
	playerPtr->changeGold(goldReward);
	playerPtr->changeExp(expReward);
}

void Enemy::takeDamage(double dam, int lvl) {
	Entity::takeDamage(dam, lvl);
	recentlyHit = true;
	recentlyHitTimer = RECENTLY_HIT_TIMEOUT;
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

Enemy & Enemy::setProjectileMap(unordered_map<string, Projectile> * ptr)
{
	projectileMap = ptr;
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
