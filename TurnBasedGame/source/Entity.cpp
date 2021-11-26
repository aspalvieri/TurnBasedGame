#include "../header/Entity.h"

Entity::Entity() { 

}

Entity::~Entity() {

}

void Entity::render() {
	Object::render();
}

void Entity::update() {
	Object::update();
}

bool Entity::canMove() {
	return false;
}

void Entity::onDeath() {

}

void Entity::takeDamage(double dam, int lvl) {
	//Implement armor reduction
	health -= dam;
	healthChanged = true;
	if (health <= 0)
		alive = false;
}

bool Entity::forceMove(double x, double y) {
	if (Sprite::getPosition().first + x >= 0 && Sprite::getPosition().first + Sprite::getBox().w + x <= *mapMaxX
	&& Sprite::getPosition().second + y >= 0 && Sprite::getPosition().second + Sprite::getBox().h + y <= *mapMaxY) {
		Sprite::setPosition(Sprite::getPosition().first + x, Sprite::getPosition().second + y);
		return true;
	}
	return false;
}

void Entity::changeGold(int amt) {
	gold += amt;
	goldChanged = true;
}

void Entity::changeExp(int amt) {
	exp += amt;
	expChanged = true;
	if (exp >= maxExp) {
		exp -= maxExp;
		levelUp();
	}
}

void Entity::levelUp() {
	level++;
	//Implement some xp curve
	maxExp = (int)(maxExp * 1.45);
	levelChanged = true;
	expChanged = true;
	healthChanged = true;
}
