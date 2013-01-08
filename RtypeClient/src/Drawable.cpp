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
  rectIterator = nullptr;
}

Rectangle<int> Drawable::getRectSpriteSheet() const
{
  return rectIterator->getValue();
}
bool Drawable::animate(int idAnimation)
{
  
  if (rectIterator == nullptr || &rectIterator->a != spriteSheet->getAnimations().at(idAnimation))
    {
      std::cout << "animating [" << spriteSheet->filename << "]: " << idAnimation << std::endl;

      delete rectIterator;
      rectIterator = new Animation::Iterator(*spriteSheet->getAnimations().at(idAnimation));
    }
  return true;
}

void Drawable::update(float elapsedTime)
{
  static float totalTime = 0; // we put 0 here to avoid redundant same values. (using a define/const would be great.)

  //totalTime += elapsedTime;
  //while ( totalTime > 250)// FIXME: maybe this should be handled by spritesheet ?
  //  {
      //std::cout << "NEXT FRAME !" << std::endl;
      rectIterator->increase(elapsedTime);
      //totalTime -= 250;
    //}
}

void Drawable::_manual_next_frame()
{
	rectIterator->increase_iterator();
}
