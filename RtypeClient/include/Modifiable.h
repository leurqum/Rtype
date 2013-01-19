#pragma once

#include "IAnimation.h"

#include <iostream>

template<typename T>
class Modifiable
{
 public:
 Modifiable() : it(nullptr) {}
 Modifiable(const T& v) : initialValue(v), it(nullptr), timeLeft(-1) {}
  virtual ~Modifiable() {}

  virtual void update(float ms)
  {
    modifiedValue = initialValue;
    if (it != nullptr)
      {
	it->increase(ms);
	
	modifiedValue += it->getFrame(); // assume T has an operator+(const& T) and then copy assign	
	if (timeLeft > -1)
	  {
	    timeLeft -= ms;
	
	    if (timeLeft <= 0)
	      {
		initialValue = modifiedValue;
		delete it;
		it = nullptr;
	      }
	  }    
      }
  }

  void setInitialValue( const T& v)
  {
    initialValue = v; // copy...
  }
  const T& getInitialValue() const
  {
    return initialValue;
  }
  virtual const T& getModifiedValue() const
  {
    return modifiedValue;
  }

  void setAnimation(const IAnimation<T>* m, float lastForMs = -1)
  {
    delete it;
    if (m != nullptr)
      {
	it = m->getIterator();
	timeLeft = lastForMs;
      }
    else
      {
	it = nullptr; // yeah, delete is not forced to nullify its pointer...
	std::cout << "animation to null" << std::endl;
      }
  }
  void setTimer(float timer)
  {
    timeLeft = timer;
  }
  bool isSetAnimation() const
  {
    return it != nullptr;
  }

 protected:
  T initialValue;
 private:
  T modifiedValue; // move too ?

  typename IAnimation<T>::IIterator* it; // TODO: try to use move syntax ( && )

  float timeLeft;
};
