#pragma once

template<typename T>
struct Vector2
{
public:
  T x;
  T y;

Vector2(T _x = T(), T _y = T()) : x(_x), y(_y)
  {
    
  }
  
Vector2(const Vector2<T>& v) : x(v.x), y(v.y)
  {

  }
  

  // operators:

  Vector2<T>& operator+=(const Vector2<T>& incr)
  {
    this->x += incr.x;
    this->y += incr.y;
    return *this;
  }
  Vector2<T> operator+(const Vector2<T>& incr) const
  {
    Vector2<T> v(*this);
    v += incr;
    return v;
  }

  Vector2<T>& operator-=(const Vector2<T>& incr)
  {
    this->x -= incr.x;
    this->y -= incr.y;
    return *this;
  }
  Vector2<T> operator-(const Vector2<T>& incr) const
  {
    Vector2<T> v(*this);
    v -= incr;
    return v;
  }

  Vector2<T>& operator/=(float incr)
  {
    this->x /= incr;
    this->y /= incr;
    return *this;
  }

  Vector2<T> operator/(float incr) const
  {
    Vector2<T> v(*this);
    v /= incr;
    return *this;
  }
  Vector2<T>& operator*=(float incr)
  {
    this->x *= incr;
    this->y *= incr;
    return *this;
  }

  Vector2<T> operator*(float incr) const
  {
    Vector2<T> v(*this);
    v *= incr;
    return *this;
  }
};

