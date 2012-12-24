#include "Drawable.h"


Drawable::Drawable(const SpriteSheet& ss)
	: animationId(0), spriteSheet(ss)
{
	currentRect = ss.animations.at(animationId).begin();
}


Drawable::~Drawable(void)
{
}

Vector2<float> Drawable::getPosition() const
{
	return this->position;
}

void Drawable::setPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

const std::string& Drawable::getSpriteSheetFilename() const
{
	return this->spriteSheet.filename;
}
const Rectangle<int>& Drawable::getRectSpriteSheet() const
{
	return *currentRect;
}
bool Drawable::animate(int idAnimation)
{
  return true;
}
void Drawable::update(float elapsedTime)
{
	static float timeBeforeNextFrame = 0; // we put 0 here to avoid redundant same values. (using a define/const would be great.)
	timeBeforeNextFrame -= elapsedTime;
	if (timeBeforeNextFrame <= 0)
	{
		// update image considering current animation.
		currentRect++;
		if (currentRect == spriteSheet.animations.at(animationId).end())
		currentRect = spriteSheet.animations.at(animationId).begin();
		timeBeforeNextFrame = 250; // FIXME: arbitrary rate is 4 img per second, based on tests with FAKED time ! 
	}
}
