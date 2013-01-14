#include "DrawerDrawable.h"

DrawerDrawable::DrawerDrawable(const Drawable& _d) : d(_d)
{
  
}

void DrawerDrawable::drawTo(IGraphicsManager* gm) const
{
  gm->draw(getDrawable(), getModifiedValue());
}

void DrawerDrawable::drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  gm->draw(getDrawable(), getModifiedValue() + v); 
}

const Drawable* DrawerDrawable::getDrawable() const
{
  return &d;
}
