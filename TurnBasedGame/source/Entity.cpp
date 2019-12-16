#include "../header/Entity.h"

Entity::Entity() { 

}

Entity::~Entity() {

}

void Entity::render() {
	Sprite::draw();
}

void Entity::update() {
	Sprite::nextFrame();
}

bool Entity::canMove() {
	return false;
}

void Entity::updateCamera() {

}
