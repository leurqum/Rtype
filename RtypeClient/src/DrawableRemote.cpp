#include "DrawableRemote.h"

DrawableRemote::DrawableRemote() : updater(nullptr)
{

}

void DrawableRemote::update(float elapsedTime)
{
  if (updater != nullptr)
    {
      if (spriteSheet == nullptr)
	spriteSheet = SpriteSheetFactory::getInstance()->getSpriteSheet(0); // FIXME: 0 means type
      if (rectIterator == nullptr)
	{
	  rectIterator = new SpriteSheet::Iterator(*spriteSheet);
	  
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
