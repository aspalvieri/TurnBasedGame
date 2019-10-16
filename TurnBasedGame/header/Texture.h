#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDLR.h"

class Texture
{
public:
	Texture();
	~Texture();

	//Functions
	bool loadImage(string);

	bool loadFont(std::string textureText, SDL_Color textColor, TTF_Font* gFont, int wrapLength);

	void render(int = 0, int = 0, SDL_Rect* = NULL, double = 0.0, SDL_Point* = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

	void free();

	void setSize(double w, double h);

	void setScale(double w, double h);

	void setAlpha(Uint8 a);

	//Variables
	int width = 0;
	int height = 0;
	SDL_Texture *texture = NULL;
	double scaleWidth = 0.0;
	double scaleHeight = 0.0;
	pair<double, double> scale;

private:
	SDL_Renderer *gRenderer = NULL;
};

//Just a regular texture, but with x/y coordinates
struct StaticTexture {
	StaticTexture();
	~StaticTexture();

	Texture texture;
	int x = 0, y = 0;
};

#endif//TEXTURE_H