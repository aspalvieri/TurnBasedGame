#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public CameraObj {
public:
	Projectile();
	~Projectile();

	Entity *sender = NULL;

private:

};

#endif//PROJECTILE_H