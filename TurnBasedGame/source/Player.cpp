#include "../header/Player.h"

Player::Player() {
	isPlayer = true;
	alive = true;
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

Player & Player::setProjectileMap(unordered_map<string, Projectile> * ptr)
{
	projectileMap = ptr;
	return *this;
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

	//Recently hit timeout
	if (recentlyHitTarget) {
		recentlyHitTargetTimer--;
		if (recentlyHitTargetTimer <= 0 || (hitTarget && !hitTarget->alive) || !hitTarget) {
			recentlyHitTarget = false;
			recentlyHitTargetTimer = 0;
			hitTarget = NULL;
		}
	}
}

bool Player::canMove() {
	if (up || down || left || right)
		return true;
	return false;
}

void Player::onDeath() {
	cout << "Player: I was killed.\n";
}
