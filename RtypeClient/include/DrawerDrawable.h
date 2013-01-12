#pragma once

#include "ADrawer.h"

class DrawerDrawable : public ADrawer // we don't inherit from Drawable because it would cause diamond inheritance on a class potentially templated on a different class
{
 public:
  DrawerDrawable(const Drawable&);

  const Drawable* getDrawable() const;
  virtual void drawTo(IGraphicsManager*) const override;

private:
  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const override;

  const Drawable& d;
};
