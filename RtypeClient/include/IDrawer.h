#pragma once

#include "IGraphicsManager.h"

class IDrawer
{
 public:
  // These are not exactly to draw, but to manage the drawable.

  virtual void drawTo(IGraphicsManager*) const = 0;

  virtual void update(float elapsedTime) = 0;

};
