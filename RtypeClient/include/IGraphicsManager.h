#pragma once

#include <list>
#include <map>

#include "IDrawable.h"
#include "DrawableRemote.h"
#include "../../protocol.h"
#include "SpriteSheet.h"


class IGraphicsManager
{
 public:
  virtual void reset() = 0;
  virtual void clear() = 0;
  virtual void draw(IDrawable*) = 0;
  virtual void display() = 0;
  virtual void update(float) = 0;
  
  virtual DrawableRemote* updateDrawableFrom(DrawableRemote* old, const Protocol::drawable& d) = 0;
  virtual void deleteDrawable(const IDrawable*) = 0;
  /* virtual const SpriteSheet* getSpriteSheetFor(int drawableType) const = 0; */
};
