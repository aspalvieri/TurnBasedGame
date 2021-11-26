#include "../header/Tile.h"

Tile::Tile() { }

Tile::Tile(int x, int y, SDL_Rect *clip, int clipID, bool collide, bool takesShadow, bool castsShadow, bool hasInner, bool requiresSame, Texture * tilesheet)
{
	box.x = x;
	box.y = y;
	box.w = TILE_SIZE;
	box.h = TILE_SIZE;
	this->clip = clip;
	this->clipID = clipID;
	this->collide = collide;
	this->takesShadow = takesShadow;
	this->castsShadow = castsShadow;
	this->hasInner = hasInner;
	this->requiresSame = requiresSame;
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

Tile & Tile::setClipID(int clipID)
{
	this->clipID = clipID;
	return *this;
}

int Tile::getClipID()
{
	return clipID;
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

Tile & Tile::setHasInner(bool hasInner)
{
	this->hasInner = hasInner;
	return *this;
}

bool Tile::getHasInner()
{
	return hasInner;
}

Tile & Tile::setRequiresSame(bool requiresSame)
{
	this->requiresSame = requiresSame;
	return *this;
}

bool Tile::getRequiresSame()
{
	return requiresSame;
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

Shader::Shader(int x, int y, SDL_Rect * clip, Texture * tilesheet, bool useAlpha, bool inverseShader, Uint8 maxAlpha)
{
	box.x = x;
	box.y = y;
	box.w = TILE_SIZE;
	box.h = TILE_SIZE;
	this->clip = clip;
	texture = tilesheet;
	texture->camera = true;
	set = true;
	this->useAlpha = useAlpha;
	this->inverseShader = inverseShader;
	this->maxAlpha = maxAlpha;
}

Shader::~Shader()
{
}

void Shader::render()
{
	if (set) {
		if (useAlpha)
			texture->setAlpha((inverseShader) ? maxAlpha - alpha : alpha);
		texture->render(box.x, box.y, clip);
		if (useAlpha)
			texture->setAlpha(255);
	}
}

Light::Light()
{
}

Light::Light(int v1, int v2, double dis, double str)
{
	x = v1;
	y = v2;
	distance = dis;
	strength = str;
	buildBounds();
}

void Light::buildBounds()
{
	int holdv = (distance * 10.0);
	holdv = ((holdv % 2 == 0) ? holdv + 1 : holdv) + 1;
	bbox = { (int)x - (holdv / 2) * TILE_SIZE, (int)y - (holdv / 2) * TILE_SIZE, (holdv)* TILE_SIZE, (holdv)* TILE_SIZE };
	bbound = holdv;
}

void Light::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	buildBounds();
}

void Shader::calculateLight(vector<Light> &lights, Uint8 &maxAlpha, bool ignoreLights)
{
	int maxA = min(maxAlpha, this->maxAlpha);
	int currMax = maxA;
	if (!ignoreLights) {
		for (unsigned int i = 0; i < lights.size(); i++)
		{
			if (checkCollision(&box, &lights[i].bbox))
			{
				double diffx = abs((box.x + QUARTER_TILE_SIZE) - lights[i].x);
				double diffy = abs((box.y + QUARTER_TILE_SIZE) - lights[i].y);
				double diff = sqrt((diffx*diffx) + (diffy*diffy));
				double amt = min(diff / lights[i].strength, (double)maxA);
				if (amt < maxA)
				{
					amt = amt / (lights[i].strength - min(max((diff / 250), 0.0), lights[i].strength));
					if (amt > maxA)
						amt = maxA;
				}
				currMax = min((int)amt, currMax);
			}
		}
	}
	alpha = currMax;
}
