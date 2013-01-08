#include "Animation.h"


Animation::Iterator::Iterator(const Animation& animation) : a(animation), current(nullptr), nextRect(nullptr)
{
  elapsedTime = 0;
  index_interpolation = 0;
  delete nextRect;
  nextRect = new std::list< Rectangle<int> >::const_iterator(a.frames.begin());
  increase_iterator();
}

#include <iostream>

Rectangle<int> Animation::Iterator::getValue() const
{
  Rectangle<int> ret = *current;
	  // INNER NOTE: revenir au truc d'avant, mais rajouter ce qui suit (github)
  if (a.nb_interp != 0 && (*nextRect) != a.frames.end())
    {
      // std::cout << (*nextRect)->position.x << std::endl;

      ret.position.x += ((*nextRect)->position.x - ret.position.x) / (float)a.nb_interp * index_interpolation;
      ret.position.y += ((*nextRect)->position.y - ret.position.y) / (float)a.nb_interp * index_interpolation;
    }
  if (a.smoothFrames)
    {
	  ret.position.x += ((*nextRect)->position.x - ret.position.x) * (elapsedTime / a.time_between_frames);
	  ret.position.y += ((*nextRect)->position.y - ret.position.y) * (elapsedTime / a.time_between_frames);
  }

  return ret;
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
}

//  const std::list<Rectangle<int> >& getFrames() const;

Animation::Animation(std::list<Rectangle<int> > fs, float framingTime, bool sml, int nb_interpolation, bool smoothF) :
  frames(fs),
  time_between_frames(framingTime),
  smoothLoop(sml),
  nb_interp(nb_interpolation + 1),
  smoothFrames(smoothF)
{
  
}
