#include "Drawable.h"


Drawable::Drawable()
{
  rectIterator = nullptr;
  spriteSheet = nullptr; // fuck this shit, never forget to initiate the fkin variables..
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

const SpriteSheet* Drawable::getSpriteSheet() const
{
  return this->spriteSheet;
}

void Drawable::setSpriteSheet(const SpriteSheet* s)
{
  this->spriteSheet = s;
}

Rectangle<int> Drawable::getRectSpriteSheet() const
{
  return rectIterator->getValue();
}
bool Drawable::animate(int idAnimation)
{
  // FIXME: check if it's not already doing this animation.
  rectIterator->setAnimation(idAnimation);
  return true;
}

void Drawable::update(float elapsedTime)
{
  static float timeBeforeNextFrame = 0; // we put 0 here to avoid redundant same values. (using a define/const would be great.)

  timeBeforeNextFrame -= elapsedTime;
  if (timeBeforeNextFrame <= 0)
    {
      std::cout << "NEXT FRAME !" << std::endl;
      rectIterator->increase(/* elapsedTime ? */);
      std::cout << "ok" << std::endl;
      timeBeforeNextFrame = 250; // FIXME: maybe this should be handled by spritesheet ? (i.e line before)
    }
}
