#include "../header/Texture.h"

Texture::Texture()
{
	gRenderer = SDLR::gRenderer;
	scale = { 1, 1 };
}

Texture::~Texture()
{
	//free();
}

StaticTexture::StaticTexture() : Texture() {

}

StaticTexture::~StaticTexture() {
	//texture.free();
}

void StaticTexture::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	Texture::render(x, y, clip, angle, center, flip);
}

bool Texture::loadImage(string path)
{
	//Get rid of preexisting texture
	free();

	//Load path into surface
	SDL_Surface *loadFile = IMG_Load(path.c_str());

	//Print out if the path couldn't be loaded
	if (!loadFile)
	{
		cout << "Path: " << path << ", not found!\n";
		return false;
	}

	//Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(gRenderer, loadFile);

	//Get image dimensions
	width = loadFile->w;
	height = loadFile->h;
	scaleWidth = width;
	scaleHeight = height;

	//Get rid of old surface
	SDL_FreeSurface(loadFile);

	//Return success
	return texture != NULL;
}

bool Texture::loadFont(std::string textureText, SDL_Color textColor, TTF_Font * gFont, int wrapLength)
{
	//Get rid of preexisting texture
	free();

	// README IF CRASH
	//
	// if textureText is blank string, loading font will crash
	//
	// README IF CRASH

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), textColor, wrapLength);

	//Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

	//Get image dimensions
	width = textSurface->w;
	height = textSurface->h;
	scaleWidth = width;
	scaleHeight = height;

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	//Return success
	return texture != NULL;
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, (int)width, (int)height };

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Add camera bounds
	if (camera) {
		renderQuad.x -= SDLR::camera.x;
		renderQuad.y -= SDLR::camera.y;
	}

	renderQuad.w = (int)(renderQuad.w * scale.first);
	renderQuad.h = (int)(renderQuad.h * scale.second);

	SDL_RenderCopyEx(gRenderer, texture, clip, &renderQuad, angle, center, flip);
}

void Texture::free()
{
	//Remove texture if it exists
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::setSize(double w, double h)
{
	scaleWidth = w;
	scaleHeight = h;
	scale.first = scaleWidth / width;
	scale.second = scaleHeight / height;
}

void Texture::setScale(double w, double h)
{
	scale = { w, h };
}

void Texture::setAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(texture, a);
}


/*
bool checkCollision(SDL_Rect *A, SDL_Rect *B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A->x;
	rightA = A->x + A->w;
	topA = A->y;
	bottomA = A->y + A->h;

	//Calculate the sides of rect B
	leftB = B->x;
	rightB = B->x + B->w;
	topB = B->y;
	bottomB = B->y + B->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
*/

//Attempted to make it cleaner
bool checkCollision(SDL_Rect *A, SDL_Rect *B)
{
	//If any of the sides from A are outside of B
	if ((A->y + A->h) <= B->y)
	{
		return false;
	}

	if (A->y >= (B->y + B->h))
	{
		return false;
	}

	if ((A->x + A->w) <= B->x)
	{
		return false;
	}

	if (A->x >= (B->x + B->w))
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

double distanceCheck(int &x1, int &y1, int &x2, int &y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

/*
bool checkCollision(Circle &a, SDL_Rect &b)
{
	int cX, cY;

	//Find closest x offset
	if (a.x < b.x)
	{
		cX = b.x;
	}
	else if (a.x > b.x + b.w)
	{
		cX = b.x + b.w;
	}
	else
	{
		cX = a.x;
	}

	//Find closest y offset
	if (a.y < b.y)
	{
		cY = b.y;
	}
	else if (a.y > b.y + b.h)
	{
		cY = b.y + b.h;
	}
	else
	{
		cY = a.y;
	}

	//If the closest point is inside the circle
	if (distanceCheck(a.x, a.y, cX, cY) < a.r * a.r)
	{
		return true;
	}

	return false;
}
*/

bool isEqualBox(SDL_Rect *a, SDL_Rect *b) {
	if (a->x == b->x && a->y == b->y && a->w == b->w && a->h == b->h)
		return true;
	return false;
}
