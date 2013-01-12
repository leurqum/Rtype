#pragma once

#include "Vector2.h"

class ValueDrawer
{
 public:
  /* ValueDrawer& operator+(const ValueDrawer& incr) */
  /*   { */
  /*     this->position += incr.position; */
  /*     this->scale += incr.scale; */
  /*     this->rotation += incr.rotation; */
  /*     return *this; */
  /*   } */
  ValueDrawer operator+(const ValueDrawer& a) const
  {
    ValueDrawer v = a;
    v += a;
    return v;
  }
  ValueDrawer& operator+=(const ValueDrawer& a)
  {
    this->position += a.position;
    this->scale += a.scale;
    this->rotation += a.rotation;
    return *this;
  }
  Vector2<float> position;
  Vector2<float> scale;
  float rotation;
};
