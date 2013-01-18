#include "DrawerShip.h"

DrawerShip::DrawerShip()
{
  id = -1;
  updater = nullptr;
  drawable = FactoryDrawable::getInstance()->createShip();
}

void DrawerShip::update(float ms)
{
  if (updater)
    {
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
