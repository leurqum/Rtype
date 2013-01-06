#pragma once

#include <iostream>
#include "Rectangle.h"
#include "Vector2.h"
#include "SpriteSheet.h"

class IDrawable
{
 public:
  virtual Vector2<float> getPosition() const = 0;
  virtual const SpriteSheet* getSpriteSheet() const = 0;
  virtual Rectangle<int> getRectSpriteSheet() const = 0;
  virtual bool animate(int idAnimation) = 0;
  virtual void update(float elapsedTime) = 0;
};
