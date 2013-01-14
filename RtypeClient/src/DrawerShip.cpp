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
  initialValue.position.x = updater.xPosition;
  initialValue.position.y = updater.yPosition;
  drawable->update(ms);

  // to call last because it stores the computed value and modify it when we call next update.
  ADrawer::update(ms); // Don't know if I should call Modifiable::update(ms) rather..?
}

void DrawerShip::drawTo(IGraphicsManager* gm) const
{
  gm->draw(drawable, getModifiedValue());
}

void DrawerShip::drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  gm->draw(drawable, getModifiedValue() + v); 
}

void DrawerShip::setUpdate(const Protocol::drawable& u)
{
  updater = u;
}
