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
  /* DrawableGeneric(const SpriteSheet& ss, ValueDrawable&&); */
  ~DrawableGeneric(void);

  virtual bool animate(int idAnimation);

  // encapsulated Low level control on the drawable.
  // TODO: reimplement this (maybe in Drawable)
  /* virtual void _manual_next_frame(); */
 private:
  int idAnimation;
};
