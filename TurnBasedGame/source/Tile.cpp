#include "../header/Tile.h"

Tile::Tile() { }

Tile::Tile(int x, int y, SDL_Rect *clip, bool collide, bool takesShadow, bool castsShadow, Texture * tilesheet)
{
	box.x = x;
	box.y = y;
	box.w = TILE_SIZE;
	box.h = TILE_SIZE;
	this->clip = clip;
	this->collide = collide;
	this->takesShadow = takesShadow;
	this->castsShadow = castsShadow;
	texture = tilesheet;
	texture->camera = true;
}

Tile::~Tile() { }

Tile & Tile::setClip(SDL_Rect *clip)
{
	this->clip = clip;
	return *this;
}

SDL_Rect* Tile::getClip()
{
	return clip;
}

Tile & Tile::setCollide(bool collide)
{
	this->collide = collide;
	return *this;
}

bool Tile::getCollide()
{
	return collide;
}

Tile & Tile::setTakesShadow(bool takesShadow)
{
	this->takesShadow = takesShadow;
	return *this;
}

bool Tile::getTakesShadow()
{
	return takesShadow;
}

Tile & Tile::setCastsShadow(bool castsShadow)
{
	this->castsShadow = castsShadow;
}

bool Tile::getCastsShadow()
{
	return castsShadow;
}

Tile & Tile::setTexture(Texture * tilesheet)
{
	texture = tilesheet;
	return *this;
}

Texture Tile::getTexture()
{
	return *texture;
}

SDL_Rect Tile::getBox()
{
	return box;
}

void Tile::render()
{
	texture->render(box.x, box.y, clip);
}

Shader::Shader()
{
}

Shader::Shader(int x, int y, SDL_Rect * clip, Texture * tilesheet)
{
	box.x = x;
	box.y = y;
	box.w = TILE_SIZE;
	box.h = TILE_SIZE;
	this->clip = clip;
	texture = tilesheet;
	texture->camera = true;
	set = true;
}

Shader::~Shader()
{
}

void Shader::render()
{
	if (set)
		texture->render(box.x, box.y, clip);
}
