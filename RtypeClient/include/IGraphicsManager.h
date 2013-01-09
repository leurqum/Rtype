#pragma once

#include <list>
#include <map>

#include "IDrawable.h"
#include "../../protocol.h"
#include "SpriteSheet.h"
#include "Vector2.h"

class IDrawer;

class IGraphicsManager
{
 public:
  virtual void reset() = 0;
  virtual void clear() = 0;
  virtual void draw(IDrawable*, const IDrawer*) = 0;
  virtual void display() = 0;
};

#include "IDrawer.h"
