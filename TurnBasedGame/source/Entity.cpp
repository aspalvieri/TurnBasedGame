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

