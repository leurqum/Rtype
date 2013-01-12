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
      index_interpolation = 0;
      nextRect = new t_frameIterator(a.frames.begin());
      increase_iterator();
    }

    virtual const ValueDrawable& getFrame() const override
    {
      return calculated;
    }
    
    virtual void increase(float time) override
    {
      elapsedTime += time;
      while (elapsedTime > a.time_between_frames)
	{
	  index_interpolation++;
	  if (index_interpolation >= a.nb_interp)
	    increase_iterator();
	  elapsedTime -= a.time_between_frames;
	}
      update_calculated();
    }

    void increase_iterator()
    {
      index_interpolation = 0;
      if (a.frames.size() == 1)
	{
	  *nextRect = a.frames.begin();
	  current = &(*(*nextRect));
	  return ;
	}
	
      if (a.nb_interp == 1 && !a.smoothFrames && *nextRect == a.frames.end())
	*nextRect = a.frames.begin();
      current = &(*((*nextRect)++));
      if (*nextRect == a.frames.end() && (a.nb_interp != 1 || a.smoothFrames))
	{
	  *nextRect = a.frames.begin();
	  if (!a.smoothLoop)
	    increase_iterator(); // NOTE: this would not be infinite recursive because of the if before.
	}
      update_calculated();
    }

    // this is const, and it's pretty useful to access it, so public. (useless actually)
    const Animation<T>& a;
  private:

    void update_calculated()
    {
      calculated = *current;
      if (a.nb_interp != 0 && (*nextRect) != a.frames.end())
	calculated += (*(*nextRect) - calculated) / (float)a.nb_interp * index_interpolation;
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


  //  const std::list<Rectangle<int> >& getFrames() const;


 Animation(std::list<ValueDrawable > fs, float framingTime, bool sml = false, int nb_interpolation = 0, bool smoothF = false) :
  frames(fs),
  time_between_frames(framingTime),
  smoothLoop(sml),
  nb_interp(nb_interpolation + 1),
  smoothFrames(smoothF)
{
  
}

  // private: // FIXME: this should be private but friend with iterator
  // NOTE: might be public as long as it's constant.
  const std::list<T > frames;


  const float time_between_frames; // time between the start of a frame and the end of it.
  const bool smoothLoop; // if last frame goes instantly to first frame or interpole and/or smoothLoop.
  // FIXME: delete this smoothLoop, it's useless, it just avoids the creation of a single frame but add significant complexity.
  const int nb_interp; // interpolate the position of the different frames (it creates [nb_interp] new frames between the frames).
  // (kinda useless, if you think a bit, but it makes less lines sometimes for creating an animation, and it's pretty readable.
  const bool smoothFrames; // it's the high level of interpolate, it makes a full fluid interpolation depending on time between the frames (interpolated frames are counted as frames).
};
