#pragma once

#include "Vector2.h"

class ValueDrawable
{
 public:
  Vector2<float> dimension;
  Vector2<float> position;

  ValueDrawable(float dimx = 0, float dimy = 0, float posx = 0, float posy = 0) : dimension(dimx, dimy), position(posx, posy) {}

  // Operators:

  ValueDrawable& operator+=(const ValueDrawable& incr)
    {
      this->position += incr.position;
      this->dimension += incr.dimension;
      return *this;
    }
  ValueDrawable operator+(const ValueDrawable& incr) const
    {
      ValueDrawable ret(*this);
      ret += incr;
      return ret;
    }

  ValueDrawable& operator-=(const ValueDrawable& incr)
    {
      this->position -= incr.position;
      this->dimension -= incr.dimension;
      return *this;
    }
  ValueDrawable operator-(const ValueDrawable& incr) const
  {
    ValueDrawable ret(*this);
    ret -= incr;
    return ret;
  }
  
  ValueDrawable& operator/=(float n)
    {
      this->position /= n;
      this->dimension /= n;
      return *this;
    }
  ValueDrawable operator/(float n) const
  {
    ValueDrawable ret(*this);
    ret /= n;
    return ret;
  }

  ValueDrawable& operator*=(float n)
    {
      this->position *= n;
      this->dimension *= n;
      return *this;
    }
  ValueDrawable operator*(float n) const
  {
    ValueDrawable ret(*this);
    ret *= n;
    return ret;
  }
 };
