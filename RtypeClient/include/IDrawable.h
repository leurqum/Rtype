#pragma once

#include <iostream>
#include "Rectangle.h"
#include "Vector2.h"
#include "SpriteSheet.h"
/* #include "IDrawer.h" */

class IDrawable // : public IDrawer
{
 public:
  // FIXME: no ref ?
  // virtual Vector2<float> getPosition() const = 0;
  // Add rotation, etc.

  virtual const std::string& getSpriteSheet() const = 0;
  virtual const Rectangle<int>* getRectSpriteSheet() const = 0;




  // these are useless to draw smth :

  /* virtual bool animate(int idAnimation) = 0; */
  /* //virtual void queueModifier(Animation a); */
  /* virtual void _manual_next_frame() = 0; */
};
