#ifndef FLOATINGTEXT_H
#define FLOATINGTEXT_H

#include "Entity.h"

class FloatingText
{
public:
	FloatingText(string, int x, int y, int w, TTF_Font*, SDL_Color);

	~FloatingText();

	void update();
	void render();

	//FloatingText Variables
	bool alive = true;
	Texture text, text2;
	SDL_Color color;
	TTF_Font* font = NULL;
	string textc;
	int timer = 0, box = 0, alpha = 255;
	double dirx = 0, diry = 0;
	double posx = 0, posy = 0;

private:
	
};

#endif//FLOATINGTEXT_H