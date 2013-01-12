#include "FactoryDrawable.h"

FactoryDrawable* FactoryDrawable::instance;

FactoryDrawable* FactoryDrawable::getInstance()
{
  if (instance != nullptr)
    instance = new FactoryDrawable();
  return instance;
}

FactoryDrawable::FactoryDrawable()
{
  
}

DrawableGeneric* FactoryDrawable::createButton()
{
  return fromSpriteSheet(3);
}

DrawableGeneric* FactoryDrawable::createSelectionArrow()
{
  return fromSpriteSheet(4);
}

DrawableGeneric* FactoryDrawable::createFarBackground()
{
  return fromSpriteSheet(1);
}

DrawableGeneric* FactoryDrawable::createMovingStarsBackground()
{
  return fromSpriteSheet(2);
}

DrawableGeneric* FactoryDrawable::createShip()
{
  return fromSpriteSheet(0);
}

DrawableGeneric* FactoryDrawable::fromSpriteSheet(int id)
{
  SpriteSheet* s = SpriteSheetFactory::getInstance()->getSpriteSheet(id);

  if (s == nullptr)
    {
      // wtf ?
      return nullptr;
    }
  return new DrawableGeneric(*s);
}
