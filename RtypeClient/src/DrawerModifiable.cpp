#include "DrawerModifiable.h"

DrawerModifiable::DrawerModifiable(const Vector2<float>& p)
{
  
}

Vector2<float> DrawerModifiable::getPosition() const
{
  return position;
}

void DrawerModifiable::setPosition(const Vector2<float>& p)
{
  position = p;
}

void DrawerModifiable::update(float ms)
{
  for (Animation::Iterator& i : modifiers)
    {
      i.increase(ms);
    }

}

void DrawerModifiable::addModifier(const Animation& a)
{
  modifiers.push_back(Animation::Iterator(a));
}
