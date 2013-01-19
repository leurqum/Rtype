#include "DrawerEnemyBasic.h"

DrawerEnemyBasic::DrawerEnemyBasic()
{
  drawable = FactoryDrawable::getInstance()->createEnemyBasic();
  drawable->animate(0);
  life = 1;
  timeFromLastUpdate = 0;
  updater = nullptr;
}

int DrawerEnemyBasic::getId() const
{
  return id;
}

void DrawerEnemyBasic::update(float ms)
{
  timeFromLastUpdate += ms;
  // FIXME: we don't have to calculate every time if we already calculated the value of this updater. (see DrawerShip)
  if (updater != nullptr)
    {
      timeFromLastUpdate = 0;
      initialValue.position.x = updater->xPosition - drawable->getModifiedValue().dimension.x / 2;;
      initialValue.position.y = updater->yPosition - drawable->getModifiedValue().dimension.y / 2;;
      life = updater->life;
      delete updater;
      updater = nullptr;
    }
  drawable->update(ms);
  if (timeFromLastUpdate >= 500)
    life = 0;
  // to call last because it stores the computed value and modify it when we call next update.
  ADrawer::update(ms); // Don't know if I should call Modifiable::update(ms) rather..?
}

void DrawerEnemyBasic::drawTo(IGraphicsManager* gm) const
{
  gm->draw(drawable, getModifiedValue());
}

void DrawerEnemyBasic::drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  gm->draw(drawable, getModifiedValue() + v); 
}

void DrawerEnemyBasic::setUpdate(const Protocol::drawable& u)
{
  id = u.id;
  delete updater;
  updater = new Protocol::drawable(u);
}

DrawerUDrawable* DrawerEnemyBasic::createExplosion() const
{
  DrawerUDrawable* d = new DrawerUDrawable(DrawableGeneric(*FactoryDrawable::getInstance()->createExplosion()));
  
  d->setTimerAnimation(480);
  ValueDrawer r(getInitialValue());

  // FIXME: -= x en dur.. berk
  r.position.x -= 0;
  r.position.y -= 0;
  r.scale.x += 0.2;
  r.scale.y += 0.2;
  d->setInitialValue(r);
  return d;
}

int DrawerEnemyBasic::getLife() const
{
  return life;
}

