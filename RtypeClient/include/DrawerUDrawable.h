#pragma once

#include "ADrawer.h"
#include "DrawableGeneric.h"

class DrawerUDrawable : public ADrawer // we don't inherit from Drawable because it would cause diamond inheritance on a class potentially templated on a different class
{
 public:
  DrawerUDrawable(const DrawableGeneric&&);

  const Drawable* getDrawable() const;
  virtual void drawTo(IGraphicsManager*) const override;

  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const override;
  void animate(int id, float lastForMs = -1);
  virtual void update(float ms) override;
  void setTimerAnimation(float t);
 private:

  DrawableGeneric d;
};
