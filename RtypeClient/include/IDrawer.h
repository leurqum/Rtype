#pragma once

#include "IGraphicsManager.h"

class IDrawer
{
public:
// These are not exactly to draw, but to manage the drawable.

  virtual Vector2<float> getPosition() const = 0;
  virtual void setPosition(const Vector2<float>&) = 0;
  virtual void drawTo(IGraphicsManager*) const = 0;

  virtual void update(float elapsedTime) = 0;

};
