#include "DrawableBar.h"

DrawableBar::DrawableBar(int id) : Drawable("sprites/bar_hp_mp.png")
{
  setInitialValue(ValueDrawable(106, 16, 0, 0 + 1 * id * 16));
  barValue = 100;
}

DrawableBar::~DrawableBar(void)
{
}

void DrawableBar::setBarValue(int v)
{
  barValue = v;
  // std::cout << 106 * ((float)v / 100) << std::endl;
  setInitialValue(ValueDrawable(106 * ((float)v / 100), 16, 0, getInitialValue().position.y));
}

int DrawableBar::getBarValue() const
{
  return barValue;
}
