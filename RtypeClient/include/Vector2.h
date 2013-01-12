#pragma once

template<typename T>
struct Vector2
{
public:
Vector2(T _x = T(), T _y = T()) : x(_x), y(_y)
  {
    
  }
  
Vector2(const Vector2<T>& v) : x(v.x), y(v.y)
  {

  }
  
  Vector2<T>& operator+=(const Vector2<T>& incr)
  {
    this->x += incr.x;
    this->y += incr.y;
    return *this;
  }

  Vector2<T> operator+(const Vector2<T>& incr)
  {
    Vector2<T> v(incr);
    this->x += incr.x;
    this->y += incr.y;
    return *this;
  }

  T x;
  T y;
};

