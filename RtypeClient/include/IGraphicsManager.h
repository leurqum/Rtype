#pragma once

#include <list>
#include <map>

#include "IDrawable.h"
#include "../../protocol.h"
#include "SpriteSheet.h"
#include "Vector2.h"

class IGraphicsManager
{
 public:
  virtual void reset() = 0;
  virtual void clear() = 0;
  virtual void draw(IDrawable*, Vector2<float> translation = Vector2<float>()) = 0;
  virtual void display() = 0;
};
