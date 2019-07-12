#include "../header/Sprite.h"

Sprite::Sprite()
{
	angle = 0.0;
	position = { 0.0, 0.0 };
	frameSize = { 0, 0 };
	scale = { 1.0, 1.0 };
	center = { 0, 0 };
	currentFrame = 0;
	currentAnimation = "";
	location = "";
	delay = 1;
	ticks = 0;
	box = { 0, 0, 0, 0 }; //X, Y, W, H
	collide = false;
	visible = true;
	inManager = false;
	enabled = true;
}

Sprite::~Sprite()
{
	if (inManager) {
		Sprite::spriteManager.erase(remove(Sprite::spriteManager.begin(), Sprite::spriteManager.end(), this), Sprite::spriteManager.end());
	}
}

Sprite & Sprite::addToManager()
{
	Sprite::spriteManager.push_back(this);
	inManager = true;
	return *this;
}

Sprite & Sprite::removeFromManager()
{
	if (inManager) {
		Sprite::spriteManager.erase(remove(Sprite::spriteManager.begin(), Sprite::spriteManager.end(), this), Sprite::spriteManager.end());
	}
	return *this;
}

Sprite& Sprite::loadSpriteImage(std::string fileLocation)
{
	location = fileLocation;
	if (images.find(fileLocation) == images.end())
	{
		images[fileLocation].loadImage(fileLocation);
	}
	return *this;
}

Sprite& Sprite::setFrameSize(int width, int height)
{
	frameSize = { width, height };
	center = { (int)ceil((frameSize.first * scale.first) / 2.0), (int)ceil((frameSize.second * scale.second) / 2.0) };
	box.w = (int)(frameSize.first * scale.first);
	box.h = (int)(frameSize.second * scale.second);
	return *this;
}

Sprite & Sprite::setPosition(double x, double y)
{
	position = { x, y };
	box.x = (int)x;
	box.y = (int)y;
	return *this;
}

std::pair<double, double> Sprite::getPosition()
{
	return position;
}

Sprite & Sprite::setSize(double width, double height)
{
	images[location].setScale(width / frameSize.first, height / frameSize.second);
	scale = { width / (double)frameSize.first, height / (double)frameSize.second };
	center = { (int)ceil((frameSize.first * scale.first) / 2.0), (int)ceil((frameSize.second * scale.second) / 2.0) };
	box.w = (int)(frameSize.first * scale.first);
	box.h = (int)(frameSize.second * scale.second);
	scaleSize = { width, height };
	return *this;
}

std::pair<double, double> Sprite::getSize()
{
	return scaleSize;
}

Sprite & Sprite::setAlpha(Uint8 a)
{
	images[location].setAlpha(a);
	return *this;
}

Sprite & Sprite::pushFrameRow(std::string animationID, int startX, int startY, int spaceX, int spaceY, int numFrames)
{
	for ( int i = 0; i < numFrames; i++)
	{
		pushFrame(animationID, startX + spaceX * i, startY + spaceY * i);
	}
	return *this;
}

Sprite & Sprite::pushFrame(std::string animationID, int x, int y)
{
	animations[animationID].push_back({ x, y });
	return *this;
}

Sprite & Sprite::setAnimation(std::string animationID)
{
	currentAnimation = animationID;
	ticks = 0;
	currentFrame = 0;
	return *this;
}

Sprite & Sprite::setAnimationRaw(std::string animationID)
{
	currentAnimation = animationID;
	return *this;
}

std::string Sprite::getCurrentAnimation()
{
	return currentAnimation;
}

int Sprite::getCurrentAnimationSize()
{
	return animations[currentAnimation].size();
}

Sprite & Sprite::setFrame(int frame)
{
	currentFrame = frame;
	ticks = 0;
	return *this;
}

int Sprite::getFrame()
{
	return currentFrame+1;
}

Sprite & Sprite::setAngle(double ang)
{
	angle = ang;
	return *this;
}

Sprite & Sprite::setCenter(int x, int y)
{
	center = { x, y };
	return *this;
}

SDL_Point Sprite::getCenter()
{
	return center;
}

Sprite & Sprite::setDelay(unsigned int time)
{
	if (time >= 1)
	{
		delay = time;
	}
	else
	{
		delay = 1;
	}
	return *this;
}

Sprite & Sprite::resetTicks()
{
	ticks = 0;
	return *this;
}

Sprite & Sprite::setCollide(bool col)
{
	collide = col;
	return *this;
}

bool Sprite::getCollide()
{
	return collide;
}

Sprite & Sprite::nextFrame()
{
	if (visible && enabled) {
		if (ticks == delay)
		{
			currentFrame++;
			ticks = 0;
		}
		else
		{
			ticks++;
		}
	}
	return *this;
}

Sprite & Sprite::setEnabled(bool e)
{
	enabled = e;
	return *this;
}

bool Sprite::getEnabled()
{
	return enabled;
}

bool Sprite::finishedAnimation()
{
	if (getFrame() == getCurrentAnimationSize() && ticks == delay)
	{
		return true;
	}
	return false;
}

bool Sprite::finishedFrame()
{
	if (ticks == delay)
	{
		return true;
	}
	return false;
}

Sprite & Sprite::draw()
{
	if (visible && animations[currentAnimation].empty() == false)
	{
		currentFrame = currentFrame % animations[currentAnimation].size();
		int x = (int)position.first;
		int y = (int)position.second;
		SDL_Rect clip;
		clip.x = animations[currentAnimation][currentFrame].first;
		clip.y = animations[currentAnimation][currentFrame].second;
		clip.w = frameSize.first;
		clip.h = frameSize.second;
		if (camera == NULL)
			images[location].render(x, y, &clip, angle, &center);
		else if (camera != NULL && checkCollision(&box, camera))
			images[location].render(x - camera->x, y - camera->y, &clip, angle, &center);
	}
	return *this;
}

SDL_Rect Sprite::getBox()
{
	return box;
}

Sprite Sprite::getSprite()
{
	return *this;
}

Sprite & Sprite::getSpriteReference()
{
	return *this;
}

Sprite & Sprite::setSprite(Sprite s)
{
	*this = s;
	return *this;
}

Sprite & Sprite::setCamera(SDL_Rect * cam)
{
	camera = cam;
	return *this;
}

SDL_Rect * Sprite::getCamera()
{
	return camera;
}

SDL_Texture * Sprite::getTexture()
{
	return images[location].texture;
}

Sprite & Sprite::setVisible(bool vis)
{
	visible = vis;
	return *this;
}

bool Sprite::getVisible()
{
	return visible;
}

Sprite & Sprite::setName(std::string n)
{
	spriteName = n;
	return *this;
}

std::string Sprite::getName()
{
	return spriteName;
}

bool Sprite::hasAnimation(std::string anim)
{
	std::unordered_map<std::string, vector<std::pair<int,int>>>::const_iterator got = animations.find(anim);
	if (got == animations.end())
		return false;
	return true;
}

Sprite & Sprite::freeImageSet()
{
	for (auto image : images) {
		image.second.free();
	}
	return *this;
}

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

double distanceCheck(int &x1, int &y1, int &x2, int &y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
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
