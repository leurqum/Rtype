#include "DrawerUDrawable.h"

DrawerUDrawable::DrawerUDrawable(const DrawableGeneric&& _d) : d(_d)
{
  
}

void DrawerUDrawable::drawTo(IGraphicsManager* gm) const
{
  gm->draw(getDrawable(), getModifiedValue());
}

void DrawerUDrawable::drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  gm->draw(getDrawable(), getModifiedValue() + v); 
}

const Drawable* DrawerUDrawable::getDrawable() const
{
  return &d;
}

void DrawerUDrawable::animate(int id, float t)
{
  d.animate(id, t);
}

void DrawerUDrawable::update(float ms)
{
  ADrawer::update(ms);
  d.update(ms);
}

void DrawerUDrawable::setTimerAnimation(float t)
{
  d.setTimer(t);
}
