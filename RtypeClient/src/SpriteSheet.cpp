#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(void)
{

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
