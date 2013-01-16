#include "DrawerBullet.h"

DrawerBullet::DrawerBullet()
{
  updater = nullptr;
  drawable = FactoryDrawable::getInstance()->createBullet();
  // WONTFIX: if id incorrect, might crash
  // wont fix cuz learn to call correct constructor.
  drawable->animate(0);
  
}

void DrawerBullet::update(float ms)
{
  if (updater)
    {
      id = updater->id;
      if (initialValue.position.x < updater->xPosition)
	drawable->animate(0);
      else if (initialValue.position.x > updater->xPosition)
	drawable->animate(0);
      initialValue.position.x = updater->xPosition;
      initialValue.position.y = updater->yPosition;
      delete updater;
      updater = nullptr;
    }
  drawable->update(ms);

  // to call last because it stores the computed value and modify it when we call next update.
  ADrawer::update(ms); // Don't know if I should call Modifiable::update(ms) rather..?
}

void DrawerBullet::drawTo(IGraphicsManager* gm) const
{
  gm->draw(drawable, getModifiedValue());
}

void DrawerBullet::drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  gm->draw(drawable, getModifiedValue() + v); 
}

void DrawerBullet::setUpdate(const Protocol::drawable& u)
{
  delete updater;
  updater = new Protocol::drawable(u);
}

int DrawerBullet::getId() const
{
  return id;
}
