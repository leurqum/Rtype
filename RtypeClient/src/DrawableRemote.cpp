#include "DrawableRemote.h"

DrawableRemote::DrawableRemote() : updater(nullptr)
{

}

void DrawableRemote::update(float elapsedTime)
{
  if (updater != nullptr)
    {
      if (spriteSheet == nullptr)
		{
		setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(0)); // FIXME: 0 means type
	  // TODO: animate properly depending on whatever from the updater
	  this->animate(1);
	  }
	  this->setPosition(updater->xPosition, updater->yPosition);

      delete updater;
      updater = nullptr;
    }
  Drawable::update(elapsedTime);
}

void DrawableRemote::setUpdate(const Protocol::drawable& d)
{
  updater = new Protocol::drawable(d);
}
