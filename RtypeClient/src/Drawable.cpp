#include "Drawable.h"


Drawable::Drawable()
  : animationId(0), updater(nullptr)
{
  currentRect = nullptr;
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
const Rectangle<int>& Drawable::getRectSpriteSheet() const
{
  return *(*currentRect);
}
bool Drawable::animate(int idAnimation)
{
  animationId = idAnimation; // FIXME: check if the idAnimation is supported by current SpriteSheet
  return true;
}

void Drawable::update(float elapsedTime)
{
  static float timeBeforeNextFrame = 0; // we put 0 here to avoid redundant same values. (using a define/const would be great.)

  // TODO: some Drawable might be interested in deleting themselves if they havn't been updated.
  if (updater != nullptr)
    {
      // TODO: seek spritesheet ?
      if (spriteSheet == nullptr)
	spriteSheet = SceneManager::getInstance()->getGraphicsManager()->getSpriteSheetFor(updater->type);
      // TODO: animate properly depending on whatever.
      // NOTE: in case of ship, i
      this->animate(1);

      if (currentRect == nullptr)
	currentRect = new std::list< Rectangle<int> >::const_iterator(spriteSheet->getAnimations().at(animationId).begin());
      this->setPosition(updater->xPosition, updater->yPosition);

      delete updater;
      updater = nullptr;
    }
  timeBeforeNextFrame -= elapsedTime;
  if (timeBeforeNextFrame <= 0)
    {
      std::cout << "NEXT FRAME !" << std::endl;
      // update image considering current animation.
      (*currentRect)++;
      if (*currentRect == spriteSheet->getAnimations().at(animationId).end())
	{
	  *currentRect = spriteSheet->getAnimations().at(animationId).begin();
	}
      timeBeforeNextFrame = 250; // FIXME: arbitrary rate is 4 img per second, based on tests with FAKED time ! 
    }
}

void Drawable::setUpdate(const Protocol::drawable& d)
{
  updater = new Protocol::drawable(d);
}
