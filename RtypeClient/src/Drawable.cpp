#include "Drawable.h"


Drawable::Drawable(void)
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
  return this->spriteFilename;
}
const Rectangle<int>& Drawable::getRectSpriteSheet() const
{
  return *this->rectSource;
}
bool Drawable::animate(int idAnimation)
{
  return true;
}
void Drawable::update(float elapsedTime)
{

}
