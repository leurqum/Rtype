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

DrawableGeneric* FactoryDrawable::createButton() const
{
  return fromSpriteSheet(3);
}

DrawableGeneric* FactoryDrawable::createSelectionArrow() const
{
  return fromSpriteSheet(4);
}

DrawableGeneric* FactoryDrawable::createFarBackground() const
{
  return fromSpriteSheet(1);
}

DrawableGeneric* FactoryDrawable::createMovingStarsBackground() const
{
  return fromSpriteSheet(2);
}

DrawableGeneric* FactoryDrawable::createShip() const
{
  return fromSpriteSheet(0);
}

DrawableGeneric* FactoryDrawable::createEnemyBasic() const
{
  return fromSpriteSheet(5);
}

DrawableGeneric* FactoryDrawable::createBarContainer() const
{
  return fromSpriteSheet(6);
}

DrawableGeneric* FactoryDrawable::createBullet() const
{
  return fromSpriteSheet(7);
}

DrawableGeneric* FactoryDrawable::fromSpriteSheet(int id) const
{
  SpriteSheet* s = SpriteSheetFactory::getInstance()->getSpriteSheet(id);

  if (s == nullptr)
    {
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      std::cout << "WAAAAAT" << std::endl;
      // wtf ?
      return nullptr;
    }
  return new DrawableGeneric(*s);
}
