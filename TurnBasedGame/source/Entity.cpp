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
	maxExp = (int)(maxExp * 1.45);
	levelChanged = true;
	expChanged = true;
}

