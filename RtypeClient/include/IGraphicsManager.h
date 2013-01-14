#pragma once

#include <list>
#include <map>

#include "Drawable.h"
#include "ValueDrawer.h"
#include "../../protocol.h"
#include "SpriteSheet.h"
#include "Vector2.h"

class IDrawer;

class IGraphicsManager
{
 public:
  virtual void reset() = 0;
  virtual void clear() = 0;
  virtual void draw(const Drawable*, const ValueDrawer&) = 0;
  virtual void write(const std::string&, const ValueDrawer&) = 0;
  virtual void display() = 0;
};

#include "IDrawer.h"
