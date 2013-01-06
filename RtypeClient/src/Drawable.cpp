#include "Drawable.h"


Drawable::Drawable()
  : updater(nullptr)
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

  // TODO: some Drawable might be interested in deleting themselves if they havn't been updated.
  if (updater != nullptr)
    {
      if (spriteSheet == nullptr)
	spriteSheet = SpriteSheetFactory::getInstance()->getSpriteSheet(0); // FIXME: 0 means type
      if (rectIterator == nullptr)
	{
	  rectIterator = new SpriteSheet::Iterator(*spriteSheet);
	  
	  // TODO: animate properly depending on whatever.
	  this->animate(1);
	}
      this->setPosition(updater->xPosition, updater->yPosition);

      delete updater;
      updater = nullptr;
    }
  timeBeforeNextFrame -= elapsedTime;
  if (timeBeforeNextFrame <= 0)
    {
      std::cout << "NEXT FRAME !" << std::endl;
      rectIterator->increase(/* elapsedTime ? */);
      std::cout << "ok" << std::endl;
      timeBeforeNextFrame = 250; // FIXME: maybe this should be handled by spritesheet ? (i.e line before)
    }
}

void Drawable::setUpdate(const Protocol::drawable& d)
{
  updater = new Protocol::drawable(d);
}
