#include "DrawerEnemyBasic.h"

DrawerEnemyBasic::DrawerEnemyBasic()
{
  drawable = FactoryDrawable::getInstance()->createEnemyBasic();
  drawable->animate(0);
}

void DrawerEnemyBasic::update(float ms)
{
  initialValue.position.x = updater.xPosition;
  initialValue.position.y = updater.yPosition;
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
  updater = u;
}
