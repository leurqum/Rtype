#pragma once

#include "DrawableGeneric.h"
#include "SpriteSheetFactory.h"

// TODO: we could make this a pool..
class FactoryDrawable
{
 public:
  static FactoryDrawable* getInstance();

  DrawableGeneric* createButton();
  DrawableGeneric* createSelectionArrow();
  DrawableGeneric* createFarBackground();
  DrawableGeneric* createMovingStarsBackground();
  DrawableGeneric* createShip();
  
 private:
  static FactoryDrawable* instance;
  FactoryDrawable();
  DrawableGeneric* fromSpriteSheet(int id);

};
