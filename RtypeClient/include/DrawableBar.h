#pragma once

#include "Drawable.h"

class DrawableBar :
virtual public Drawable
{
 public:

  DrawableBar(int id); // 0 or 1 (we use the same spritesheet as its component, and there are only 2 choices (red or blue))
  // TODO: use separate spritesheet for the bars ?
  ~DrawableBar(void);

  virtual void setBarValue(int v); // between 0 and 100
  int getBarValue() const;
 private:
  int barValue;
};
