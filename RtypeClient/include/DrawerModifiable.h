#pragma once

#include "IDrawer.h"

class DrawerModifiable : virtual public IDrawer
{
 private:
  
  std::list<Animation::Iterator> modifiers;
  Vector2<float> position;
 public:
  DrawerModifiable(const Vector2<float>& p = Vector2<float>());
  
  virtual Vector2<float> getPosition() const;

  virtual void setPosition(const Vector2<float>&);
  
  virtual void update(float ms);

  void addModifier(const Animation& a);
  // TODO: removeModifier ?
};
