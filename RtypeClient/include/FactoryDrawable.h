#pragma once

#include "DrawableGeneric.h"
#include "SpriteSheetFactory.h"

// TODO: we could make this a pool..
class FactoryDrawable
{
 public:
  static FactoryDrawable* getInstance();

  DrawableGeneric* createButton() const;
  DrawableGeneric* createSelectionArrow() const;
  DrawableGeneric* createFarBackground() const;
  DrawableGeneric* createMovingStarsBackground() const;
  DrawableGeneric* createShip() const;
  DrawableGeneric* createEnemyBasic() const;
  DrawableGeneric* createBarContainer() const;
  DrawableGeneric* createBullet() const;
  DrawableGeneric* createExplosion() const;
  
 private:
  static FactoryDrawable* instance;
  FactoryDrawable();
  DrawableGeneric* fromSpriteSheet(int id) const;

};
