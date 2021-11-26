#ifndef TILE_H
#define TILE_H

#include "Texture.h"

class Light {
public:
	Light();
	Light(int v1, int v2, double dis = 1, double str = 1);
	void buildBounds();
	void setPosition(int x, int y);

	SDL_Rect bbox;
	double strength = 1;
	double distance = 1;
	double x = 0, y = 0;
	int bbound = 0;
};

class Shader {
public:
	Shader();
	Shader(int x, int y, SDL_Rect *clip, Texture *tilesheet, bool useAlpha = false, bool inverseShader = false, Uint8 maxAlpha = 255);
	~Shader();

	void render();
	void calculateLight(vector<Light> &lights, Uint8 &maxAlpha, bool ignoreLights = false);

private:
	Texture *texture;
	SDL_Rect *clip, box;
	bool set = false, useAlpha = false, inverseShader = false;
	Uint8 alpha = 0, maxAlpha = 255;
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

	Shader shader, shadow, black[4]; //Reduce black to 1 if lagging (fix other sections to 1 as well)

private:
	bool collide;
	//Tile takes a casted shadow, tile casts a shadow, tile has an inner shadow, tile requires same tile for inner shadow
	bool takesShadow, castsShadow, hasInner, requiresSame;
	int clipID;
	Texture *texture;
	SDL_Rect *clip, box;
};

#endif//TILE_H