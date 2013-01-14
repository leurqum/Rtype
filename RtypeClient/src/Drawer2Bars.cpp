#include "Drawer2Bars.h"

Drawer2Bars::Drawer2Bars() : BarContainer(DrawableGeneric(*FactoryDrawable::getInstance()->createBarContainer())), bar1(0), bar2(1)
{
}


void Drawer2Bars::_drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  std::cout << v.position.x << " " << v.position.y << std::endl;
  ValueDrawable d(bar1.getModifiedValue());

  std::cout << d.position.x << " " << d.position.y << std::endl;
  std::cout << "drawing2 bars" << std::endl;
  BarContainer.drawTo(gm, v);
  std::cout << "drawn container" << std::endl;
  
  gm->draw(&bar1, v);
  std::cout << "drawn 1 bar" << std::endl;
  gm->draw(&bar2, v + ValueDrawer(0, 16));
}

void Drawer2Bars::drawTo(IGraphicsManager* gm) const
{
  _drawTo(gm, getModifiedValue());
}

void Drawer2Bars::drawTo(IGraphicsManager* gm, const ValueDrawer& v) const
{
  _drawTo(gm, getModifiedValue() + v);  
}


void Drawer2Bars::update(float ms)
{
  ADrawer::update(ms);
  BarContainer.update(ms);
  bar1.update(ms);
  bar2.update(ms);
}

void Drawer2Bars::setBar1(int v)
{
  bar1.setBarValue(v);
}
void Drawer2Bars::setBar2(int v)
{
  bar2.setBarValue(v);
}
int Drawer2Bars::getBar1() const
{
  return bar1.getBarValue();
}
int Drawer2Bars::getBar2() const
{
  return bar2.getBarValue();
}
