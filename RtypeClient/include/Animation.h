#pragma once

#include <list>

#include "Rectangle.h"
#include "ValueDrawable.h"
#include "IAnimation.h"

template<typename T>
class Animation : public IAnimation<T>
{
public:
  
  class Iterator : public IAnimation<T>::IIterator
  {
  public:
    Iterator(const Animation<T>& animation) : a(animation), current(nullptr), nextRect(nullptr)
    {
      elapsedTime = 0;
      nextRect = new t_frameIterator(a.frames.begin());
      increase_iterator();
    }

    virtual const T& getFrame() const override
    {
      return calculated;
    }
    
    virtual void increase(float time) override
    {
      elapsedTime += time;
      while (elapsedTime > a.time_between_frames)
	{
	    increase_iterator();
	  elapsedTime -= a.time_between_frames;
	}
      update_calculated();
    }

    void increase_iterator()
    {
      if (a.frames.size() == 1)
	{
	  *nextRect = a.frames.begin();
	  current = &(*(*nextRect));
	  return ;
	}
      if (*nextRect == a.frames.end())
	{
	  *nextRect = a.frames.begin();
	}
      current = &(*((*nextRect)++));

      if (*nextRect == a.frames.end() && a.smoothFrames)
      	{
      	  *nextRect = a.frames.begin();
	  increase_iterator(); // NOTE: this would not be infinite recursive because of the if before.
      	}
    }

    // this is const, and it's pretty useful to access it, so public. (used by iterator)
    const Animation<T>& a;
  private:

    void update_calculated()
    {
      calculated = *current;
      if (a.smoothFrames)
	calculated += (*(*nextRect) - calculated) * (elapsedTime / a.time_between_frames);
    }

    T const * current;
    
    typedef typename std::list< T >::const_iterator t_frameIterator;
    t_frameIterator* nextRect;
    T calculated;

    int index_interpolation;
    float elapsedTime;
  };

 virtual typename IAnimation<T>::IIterator* getIterator() const override
 {
   return new Iterator(*this);
 }


 Animation(std::list<T > fs, float framingTime, bool smoothF = false) :
 frames(fs),
   time_between_frames(framingTime),
   smoothFrames(smoothF)
{
  
}

  // private: // FIXME: this should be private but friend with iterator
  // NOTE: might be public as long as it's constant.
  const std::list<T > frames;

  const float time_between_frames; // time between the start of a frame and the end of it.

  const bool smoothFrames; // it makes a full fluid interpolation depending on time between the frames.
};
