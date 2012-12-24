#include "Drawable.h"


Drawable::Drawable(const SpriteSheet& ss)
	: spriteSheet(ss)
{

}


Drawable::~Drawable(void)
{
}

Vector2<float> Drawable::getPosition() const
{
  return Vector2<float>();
}
const std::string& Drawable::getSpriteSheetFilename() const
{
	return this->spriteSheet.filename;
}
const Rectangle<int>& Drawable::getRectSpriteSheet() const
{

	return spriteSheet.animations.at(0).front(); // FIXME: front() = animationPosition ; at(0) = at(animationId)
}
bool Drawable::animate(int idAnimation)
{
  return true;
}
void Drawable::update(float elapsedTime)
{

}
