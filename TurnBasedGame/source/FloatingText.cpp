#include "../header/FloatingText.h"

FloatingText::FloatingText(string d, int x, int y, int w, TTF_Font *f, SDL_Color c)
{
	textc = d;
	font = f;
	box = ((double)w / 2.0);
	posx = x;
	posy = y;
	color = c;
	double deltaX = SDLR::rand.randomDouble(-100, 100);
	double deltaY = SDLR::rand.randomDouble(-100, 100);
	double magnitude = sqrt(deltaX*deltaX + deltaY * deltaY);
	double speed = 1.5 + SDLR::rand.randomDouble(0, 0.75);
	dirx = speed * (deltaX / magnitude);
	diry = speed * (deltaY / magnitude);
	text.loadFont(textc, color, font, 200);
	text2.loadFont(textc, SDL_Color{ 0,0,0 }, font, 200);
	posx = (int)((posx - box) + (box - ((double)text.width / 2.0)));
}

FloatingText::~FloatingText()
{
}

void FloatingText::update() 
{
	posx -= dirx;
	posy -= diry;
	if (timer >= 20)
	{
		alpha -= 10;
		text.setAlpha(alpha);
		text2.setAlpha(alpha);
	}
	if (++timer >= 40)
	{
		text.free();
		text2.free();
		alive = false;
	}
}

void FloatingText::render()
{
	text2.render(posx - SDLR::camera.x + 1, posy - SDLR::camera.y + 1);
	text.render(posx - SDLR::camera.x, posy - SDLR::camera.y);
}
