#pragma once

#include <string>

#include "IDrawable.h"
#include "IDrawer.h"
#include "Rectangle.h"
#include "Vector2.h"


class SimpleDrawable : public IDrawable, public IDrawer
{
 public:
  SimpleDrawable(const std::string& spriteSheet, const Rectangle<int>&, const Vector2<float>& p = Vector2<float>());
  virtual Vector2<float> getPosition() const;
  virtual void setPosition(const Vector2<float>&);
  
  virtual const std::string& getSpriteSheet() const;
  virtual Rectangle<int> getRectSpriteSheet() const;


  virtual void drawTo(IGraphicsManager*) const;
  virtual void update(float ms);

 protected:
  const std::string& spriteSheet;
  Rectangle<int> rectSpriteSheet;
  Vector2<float> position;
};
