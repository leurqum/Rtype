#include "Animation.h"


Animation::Iterator::Iterator(const Animation& animation) : a(animation), current(nullptr), nextRect(nullptr)
{
  elapsedTime = 0;
  index_interpolation = 0;
  nextRect = new std::list< ValueDrawable >::const_iterator(a.frames.begin());
  increase_iterator();
}

#include <iostream>

const ValueDrawable& Animation::Iterator::getFrame() const
{
  return calculated;
}

void	Animation::Iterator::increase(float time)
{
  elapsedTime += time;
  while (elapsedTime > a.time_between_frames)
    {
      std::cout << "spriteupdate: " << elapsedTime << std::endl;
      index_interpolation++;
      if (index_interpolation >= a.nb_interp)
	increase_iterator();
      elapsedTime -= a.time_between_frames;
    }
  update_calculated();
}

void Animation::Iterator::increase_iterator()
{
  index_interpolation = 0;
  // std::cout << "increase iterator" << std::endl;
  if (a.frames.size() == 1)
    {
      *nextRect = a.frames.begin();
      current = &(*(*nextRect));
      return ;
    }
	
  if (a.nb_interp == 1 && !a.smoothFrames && *nextRect == a.frames.end())
    {
      *nextRect = a.frames.begin();
    }
  current = &(*((*nextRect)++));
  if (*nextRect == a.frames.end() && (a.nb_interp != 1 || a.smoothFrames))
    {
      *nextRect = a.frames.begin();
	  if (!a.smoothLoop)
	    increase_iterator(); // NOTE: this would not be infinite recursive because of the if before.
    }
  update_calculated();
}

void Animation::Iterator::update_calculated()
{
  calculated = *current;
  if (a.nb_interp != 0 && (*nextRect) != a.frames.end())
    {
      // std::cout << (*nextRect)->position.x << std::endl;

      calculated.position.x += ((*nextRect)->position.x - calculated.position.x) / (float)a.nb_interp * index_interpolation;
      calculated.position.y += ((*nextRect)->position.y - calculated.position.y) / (float)a.nb_interp * index_interpolation;
    }
  if (a.smoothFrames)
    {
	  calculated.position.x += ((*nextRect)->position.x - calculated.position.x) * (elapsedTime / a.time_between_frames);
	  calculated.position.y += ((*nextRect)->position.y - calculated.position.y) * (elapsedTime / a.time_between_frames);
  }
}

IAnimation<ValueDrawable>::IIterator* Animation::getIterator() const
{
  return new Animation::Iterator(*this);
}

Animation::Animation(std::list<ValueDrawable > fs, float framingTime, bool sml, int nb_interpolation, bool smoothF) :
  frames(fs),
  time_between_frames(framingTime),
  smoothLoop(sml),
  nb_interp(nb_interpolation + 1),
  smoothFrames(smoothF)
{
  
}
