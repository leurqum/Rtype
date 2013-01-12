#pragma once

#include "Vector2.h"

class ValueDrawable
{
 public:
 /* ValueDrawable(const ValueDrawable& cpy) : position(cpy.position), dimension(cpy.dimension) */
 /*    { */
      
 /*    } */
  ValueDrawable& operator+=(const ValueDrawable& incr)
    {
      this->position += incr.position;
      this->dimension += incr.dimension;
      return *this;
    }
  ValueDrawable operator+(const ValueDrawable& incr) const
    {
      ValueDrawable ret(incr);
      ret += incr;
      return ret;
    }
  Vector2<int> dimension;
  Vector2<int> position;
};
