#ifndef OBJECT_H
#define OBJECT_H

#include "Sprite.h"

class Object : public Sprite {
public:
	Object();
	~Object();

	virtual void render();
	virtual void update();

private:

};

#endif//OBJECT_H