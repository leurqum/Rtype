#pragma once 

#include <list>
#include "IGraphicsManager.h"
#include "IDrawable.h"
#include "Vector2.h"

class LayerDrawable
{
 public:
  void addDrawable(IDrawable* d);
  void removeDrawable(IDrawable* d);

  void setTranslation(const Vector2<float>&);
  void translate(const Vector2<float>&);

  void drawTo(IGraphicsManager*) const;
  void updateAll(float elapsedTime);

 private:
  std::list<IDrawable*> drawables;
  Vector2<float> translation;
};
