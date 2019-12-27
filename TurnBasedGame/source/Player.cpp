#include "../header/Player.h"

Player::Player() {
	isPlayer = true;
}

Player::~Player() { }

void Player::handleEvents(SDL_Event * e) {
	if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.sym) {
		case SDLK_w:
			up = true;
			break;
		case SDLK_s:
			down = true;
			break;
		case SDLK_d:
			right = true;
			break;
		case SDLK_a:
			left = true;
			break;
		default:
			break;
		}
	}

	if (e->type == SDL_KEYUP) {
		switch (e->key.keysym.sym) {
		case SDLK_w:
			up = false;
			break;
		case SDLK_s:
			down = false;
			break;
		case SDLK_d:
			right = false;
			break;
		case SDLK_a:
			left = false;
			break;
		default:
			break;
		}
	}
}

void Player::update() {
	Entity::update();
	xVel = speed * (right - left);
	yVel = speed * (down - up);

	//Triangular correct 2D movements
	if (xVel != 0 && yVel != 0) {
		xVel /= sqrt(2.0);
		yVel /= sqrt(2.0);
	}

	//Animations
	if (canMove())
		Sprite::setAnimationRaw("Moving");
	else
		Sprite::setAnimationRaw("Idle");
}

bool Player::canMove() {
	if (up || down || left || right)
		return true;
	return false;
}
