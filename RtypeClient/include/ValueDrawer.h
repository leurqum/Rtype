#pragma once

#include "Vector2.h"

class ValueDrawer
{
 public:
  Vector2<float> position;
  Vector2<float> scale;
  float rotation;

  ValueDrawer(float posx = 0, float posy = 0, float scalex = 0, float scaley = 0, float rot = 0) : position(posx, posy), scale(scalex, scaley), rotation(rot) {}

  // Operators:

  ValueDrawer& operator+=(const ValueDrawer& incr)
    {
      this->position += incr.position;
      this->scale += incr.scale;
      this->rotation += incr.rotation;
      return *this;
    }
  ValueDrawer operator+(const ValueDrawer& incr) const
    {
      ValueDrawer ret(*this);
      ret += incr;
      return ret;
    }

  ValueDrawer& operator-=(const ValueDrawer& incr)
    {
      this->position -= incr.position;
      this->scale -= incr.scale;
      this->rotation -= incr.rotation;
      return *this;
    }
  ValueDrawer operator-(const ValueDrawer& incr) const
  {
    ValueDrawer ret(*this);
    ret -= incr;
    return ret;
  }
  
  ValueDrawer& operator/=(float n)
    {
      this->position /= n;
      this->scale /= n;
      this->rotation /= n;
      return *this;
    }
  ValueDrawer operator/(float n) const
  {
    ValueDrawer ret(*this);
    ret /= n;
    return ret;
  }

  ValueDrawer& operator*=(float n)
    {
      this->position *= n;
      this->scale *= n;
      this->rotation *= n;
      return *this;
    }
  ValueDrawer operator*(float n) const
  {
    ValueDrawer ret(*this);
    ret *= n;
    return ret;
  }
};
