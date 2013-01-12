#pragma once

#include "IAnimation.h"

#include <iostream>

template<typename T>
class Modifiable
{
 public:
 Modifiable() : it(nullptr) {}
 Modifiable(const T& v) : initialValue(v), it(nullptr) {}
 /* Modifiable(T&& v) : initialValue(v) {} */

  virtual void update(float ms)
  {
    modifiedValue = initialValue;
    if (it != nullptr)
      {
	it->increase(ms);
	modifiedValue += it->getFrame(); // assume T has an operator+(const& T) and then copy assign
      }
  }

  void setInitialValue( const T& v)
  {
    initialValue = v; // copy...
  }
  virtual const T& getModifiedValue() const
  {
    return modifiedValue;
  }
  void setAnimation(const IAnimation<T>* m)
  {
    delete it;
    if (m != nullptr)
      {
	it = m->getIterator();
      }
    else
      {
	it = nullptr; // yeah, delete is not forced to nullify its pointer...
	std::cout << "animation to null" << std::endl;
      }
  }
 protected:
  T initialValue;
 private:
  T modifiedValue; // move too ?

  // in c++11, we can initialize here :
  typename IAnimation<T>::IIterator* it = nullptr; // TODO: try to use move syntax ( && )
};
