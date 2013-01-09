#include "SimpleDrawable.h"

SimpleDrawable::SimpleDrawable(const std::string& ssFilename, const Vector2<float>& p) : spriteSheet(ssFilename), rectSpriteSheet(nullptr), position(p)
{
  
}

SimpleDrawable::SimpleDrawable(const std::string& ssFilename, const Rectangle<int>& r, const Vector2<float>& p) : spriteSheet(ssFilename), rectSpriteSheet(new Rectangle<int>(r)), position(p)
{

}

Vector2<float> SimpleDrawable::getPosition() const
{
  return position;
}

void SimpleDrawable::setPosition(const Vector2<float>& p)
{
  position = p;
}

const std::string& SimpleDrawable::getSpriteSheet() const
{
  return spriteSheet;
}

const Rectangle<int>* SimpleDrawable::getRectSpriteSheet() const
{
  return rectSpriteSheet;
}

void SimpleDrawable::drawTo(IGraphicsManager* gm) const
{
  gm->draw((IDrawable*)this);
}

void SimpleDrawable::update(float ms)
{

}
