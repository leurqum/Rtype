#pragma once 

#include <list>
#include "DrawerModifiable.h"
#include "Vector2.h"

class LayerDrawable : public DrawerModifiable
{
 public:
  void addDrawable(IDrawer* d);
  void removeDrawable(IDrawer* d);

  void setTranslation(const Vector2<float>&);
  void translate(const Vector2<float>&);

  void drawTo(IGraphicsManager*) const;
  void update(float elapsedTime);

 private:
  std::list<IDrawer*> drawers;
  Vector2<float> translation;
};
