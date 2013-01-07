#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(void)
{
  nb_interp = 0;
  smoothLoop = true;
}

SpriteSheet::~SpriteSheet(void)
{
}


void SpriteSheet::setFilename(const std::string& f)
{
  filename = f;
}

const std::string& SpriteSheet::getFilename() const
{
  return filename;
}

void SpriteSheet::setAnimations(const std::map<int, std::list<Rectangle<int> > >& a)
{
  animations = a;
}

const std::map<int, std::list<Rectangle<int> > >& SpriteSheet::getAnimations() const
{
  return animations;
}

void SpriteSheet::setInterpolation(int nb)
{
  nb_interp = nb;
}

void SpriteSheet::setSmoothLoop(bool smloop)
{
	smoothLoop = smloop;
}

SpriteSheet::Iterator::Iterator(const SpriteSheet& s) : ss(s), current(nullptr), nextRect(nullptr)
{

}

#include <iostream>

Rectangle<int> SpriteSheet::Iterator::getValue() const
{
  Rectangle<int> ret = *current;
  if (ss.nb_interp != 0)
    {
      std::cout << "last: " << current->position.x  << ";" << current->position.y << std::endl;
      std::cout << "next: " << (*nextRect)->position.x  << ";" << (*nextRect)->position.y << std::endl;
      std::cout << std::endl;

      ret.position.x += ((*nextRect)->position.x - current->position.x) / (float)ss.nb_interp * index_interpolation;
      ret.position.y += ((*nextRect)->position.y - current->position.y) / (float)ss.nb_interp * index_interpolation;
    }
  return ret;
}

void	SpriteSheet::Iterator::increase()
{
  if (++index_interpolation >= ss.nb_interp)
    {
      increase_iterator();
    }
}

void SpriteSheet::Iterator::setAnimation(int animId)
{
  animationId = animId;

  index_interpolation = 0;
  delete nextRect;
  nextRect = new std::list< Rectangle<int> >::const_iterator(ss.getAnimations().at(animationId).begin());
  increase_iterator();
}

void SpriteSheet::Iterator::increase_iterator()
{
  index_interpolation = 0;
  std::cout << "increase iterator" << std::endl;
  if (ss.getAnimations().at(animationId).size() == 1)
    {
      *nextRect = ss.getAnimations().at(animationId).begin();
      current = &(*(*nextRect));
      return ;
    }

  current = &(*((*nextRect)++));
  if (*nextRect == ss.getAnimations().at(animationId).end())
    {
      *nextRect = ss.getAnimations().at(animationId).begin();
	  if (!ss.smoothLoop)
		  increase_iterator(); // NOTE: this would not be infinite recursive because of the if before.
    }
}
