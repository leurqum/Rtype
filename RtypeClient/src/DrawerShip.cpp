#include "DrawerShip.h"

DrawerShip::DrawerShip(int id)
{
  drawable = FactoryDrawable::getInstance()->createShip();
  // WONTFIX: if id incorrect, might crash
  // wont fix cuz learn to call correct constructor.
  drawable->animate(id);
}

void DrawerShip::update(float ms)
{
  ADrawer::update(ms); // Don't know if I should call Modifiable::update(ms) rather..?
  drawable->update(ms);
}

void DrawerShip::drawTo(IGraphicsManager* gm) const
{
  gm->draw(drawable, getModifiedValue());
}

void DrawerShip::drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  gm->draw(drawable, getModifiedValue() + v); 
}


