#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
	Player();
	~Player();

	void handleEvents(SDL_Event *e);
	void update();
	bool canMove();
	void setCamera(SDL_Rect*);

private:
	bool up = false, down = false, right = false, left = false;
};

#endif//PLAYER_H