#include "../header/Object.h"

Object::Object() {
	Sprite::setCamera(true);
}

Object::~Object() {

}

void Object::render() {
	Sprite::draw();
}

void Object::update() {
	Sprite::nextFrame();
}
