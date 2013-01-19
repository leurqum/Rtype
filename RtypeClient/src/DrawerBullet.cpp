#include "DrawerBullet.h"

DrawerBullet::DrawerBullet()
{
  updater = nullptr;
  drawable = FactoryDrawable::getInstance()->createBullet();
  // WONTFIX: if id incorrect, might crash
  // wont fix cuz learn to call correct constructor.
  drawable->animate(0);
  life = 1;
  timeFromLastUpdate = 0;
}

void DrawerBullet::update(float ms)
{
  timeFromLastUpdate += ms;
  if (updater)
    {
      timeFromLastUpdate = 0;
      id = updater->id;
      if (initialValue.position.x + drawable->getModifiedValue().dimension.x / 2 < updater->xPosition)
	drawable->animate(0);
      else if (initialValue.position.x + drawable->getModifiedValue().dimension.y / 2 > updater->xPosition)
	drawable->animate(1);
      initialValue.position.x = updater->xPosition - drawable->getModifiedValue().dimension.x / 2;;
      initialValue.position.y = updater->yPosition - drawable->getModifiedValue().dimension.y / 2;;
      life = updater->life;

      delete updater;
      updater = nullptr;
    }
  drawable->update(ms);
  if (timeFromLastUpdate > 500)
    life = 0;

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
  id = u.id;
  delete updater;
  updater = new Protocol::drawable(u);
}

int DrawerBullet::getId() const
{
  return id;
}

DrawerUDrawable* DrawerBullet::createExplosion() const
{
  return nullptr;
}

int DrawerBullet::getLife() const
{
  return life;
}
