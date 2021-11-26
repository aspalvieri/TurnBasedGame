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
		if (!camera)
			images[location].render(x, y, &clip, angle, &center);
		else if (camera && checkCollision(&box, &SDLR::camera))
			images[location].render(x - SDLR::camera.x, y - SDLR::camera.y, &clip, angle, &center);
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

Sprite & Sprite::setCamera(bool cam)
{
	camera = cam;
	return *this;
}

bool Sprite::getCamera()
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
