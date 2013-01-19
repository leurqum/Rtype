#include "DrawerEnemyBasic.h"

DrawerEnemyBasic::DrawerEnemyBasic()
{
  drawable = FactoryDrawable::getInstance()->createEnemyBasic();
  drawable->animate(0);
}

int DrawerEnemyBasic::getId() const
{
  return id;
}

void DrawerEnemyBasic::update(float ms)
{
  // FIXME: we don't have to calculate every time if we already calculated the value of this updater. (see DrawerShip)
  initialValue.position.x = updater.xPosition - drawable->getModifiedValue().dimension.x / 2;;
  initialValue.position.y = updater.yPosition - drawable->getModifiedValue().dimension.y / 2;;
  drawable->update(ms);

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
  updater = u;
}

DrawerUDrawable* DrawerEnemyBasic::createExplosion() const
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
