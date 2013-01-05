#pragma once

#include <list>
#include <map>

#include "IDrawable.h"
#include "../../protocol.h"

class IGraphicsManager
{
 public:
  virtual void reset() = 0;
  virtual void clear() = 0;
  virtual void draw(IDrawable*) = 0;
  virtual void display() = 0;
  virtual void update(float) = 0;
  virtual IDrawable* updateDrawableFrom( const Protocol::drawable& d) = 0;
  virtual void deleteDrawable(const IDrawable*) = 0;
};
