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
	Tile(int x, int y, SDL_Rect *clip, int clipID, bool collide, bool takesShadow, bool castsShadow, bool hasInner, bool requiresSame, Texture *tilesheet);
	~Tile();

	Tile& setClip(SDL_Rect *clip);
	SDL_Rect* getClip();

	Tile& setClipID(int clipID);
	int getClipID();

	Tile& setCollide(bool collide);
	bool getCollide();

	Tile& setTakesShadow(bool takesShadow);
	bool getTakesShadow();

	Tile& setCastsShadow(bool castsShadow);
	bool getCastsShadow();

	Tile& setHasInner(bool hasInner);
	bool getHasInner();

	Tile& setRequiresSame(bool requiresSame);
	bool getRequiresSame();

	Tile& setTexture(Texture *tilesheet);
	Texture getTexture();

	SDL_Rect getBox();

	void render();

	Shader shader, shadow;

private:
	bool collide;
	//Tile takes a casted shadow, tile casts a shadow, tile has an inner shadow, tile requires same tile for inner shadow
	bool takesShadow, castsShadow, hasInner, requiresSame;
	int clipID;
	Texture *texture;
	SDL_Rect *clip, box;
};

#endif//TILE_H