#pragma once

#include "Drawable.h"
#include "SpriteSheet.h"

class DrawableGeneric :
virtual public Drawable
{
 protected:
  const SpriteSheet* spriteSheet;

 public:

  DrawableGeneric(const SpriteSheet& ss);
  DrawableGeneric(const SpriteSheet& ss, const ValueDrawable&);
  ~DrawableGeneric(void);

  virtual bool animate(int idAnimation);

 private:
  int idAnimation;
};
