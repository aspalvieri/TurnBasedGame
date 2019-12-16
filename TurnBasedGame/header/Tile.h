#ifndef TILE_H
#define TILE_H

#include "Texture.h"

class Shader {
public:
	Shader();
	Shader(int x, int y, SDL_Rect *clip, Texture *tilesheet);
	~Shader();

	void render();

private:
	Texture *texture;
	SDL_Rect *clip, box;
	bool set = false;
};

class Tile 
{
public:
	Tile();
	Tile(int x, int y, SDL_Rect *clip, bool collide, bool takesShadow, bool castsShadow, Texture *tilesheet);
	~Tile();

	Tile& setClip(SDL_Rect *clip);
	SDL_Rect* getClip();

	Tile& setCollide(bool collide);
	bool getCollide();

	Tile& setTakesShadow(bool takesShadow);
	bool getTakesShadow();

	Tile& setCastsShadow(bool castsShadow);
	bool getCastsShadow();

	Tile& setTexture(Texture *tilesheet);
	Texture getTexture();

	SDL_Rect getBox();

	void render();

	Shader shader;

private:
	bool collide, takesShadow, castsShadow;
	Texture *texture;
	SDL_Rect *clip, box;
};

#endif//TILE_H