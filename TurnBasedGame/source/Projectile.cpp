#include "../header/Projectile.h"

Projectile::Projectile() {

}

Projectile::~Projectile() {

}

void Projectile::update() {
	CameraObj::update();
}

void Projectile::render() {
	CameraObj::render();
}

void Projectile::setVariables(double xVel, double yVel, double angle, double maxDistance, int level, double damage, int ID, double lifeSteal) {
	this->xVel = xVel;
	this->yVel = yVel;
	this->angle = angle;
	this->maxDistance = maxDistance;
	this->level = level;
	this->damage = damage;
	this->lifeSteal = lifeSteal;
	this->ID = ID;
	setAngle(this->angle);
}

void Projectile::setSender(int type, int id)
{
	senderType = type;
	senderID = id;
}

void Projectile::setToDie(string anim)
{
	alive = false;
	die = true;
	setAnimation(anim);
}
