#include "DrawerShip.h"

DrawerShip::DrawerShip()
{
  id = -1;
  updater = nullptr;
  drawable = FactoryDrawable::getInstance()->createShip();
  timeFromLastUpdate = 0;
  life = 1;
}

void DrawerShip::update(float ms)
{
  timeFromLastUpdate += ms;
  if (updater)
    {
      timeFromLastUpdate = 0;
      drawable->animate(id % 5); // there are only 5 animations/colors.
      drawable->update(ms); // we do it here because otherwise the initial (and modified) value would be 0, we then couldn't center the sprite.
      initialValue.position.x = updater->xPosition - drawable->getModifiedValue().dimension.x / 2;
      initialValue.position.y = updater->yPosition - drawable->getModifiedValue().dimension.y / 2;
      std::cout << drawable->getModifiedValue().dimension.x << std::endl;
      
      life = updater->life;

      // FIXME: doing this each update is redundant.

      delete updater;
      updater = nullptr;
    }
  else
    drawable->update(ms);

  if (timeFromLastUpdate > 500)
    life = 0; // we consider it might be dead, so we set the life to 0.

  ADrawer::update(ms);  
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
  id = u.id;
  delete updater;
  updater = new Protocol::drawable(u);
}

int DrawerShip::getId() const
{
  return id;
}

int DrawerShip::getLife() const
{
  return life;
}

DrawerUDrawable* DrawerShip::createExplosion() const
{
  DrawerUDrawable* d = new DrawerUDrawable(DrawableGeneric(*FactoryDrawable::getInstance()->createExplosion()));
  
  d->setTimerAnimation(480);
  ValueDrawer r(getInitialValue());

  // FIXME: -= x en dur.. berk
  r.position.x -= 11;
  r.position.y -= 12;
  r.scale.x += 0.7;
  r.scale.y += 0.7;
  d->setInitialValue(r);
  return d;
}
