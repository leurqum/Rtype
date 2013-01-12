#include "DrawableGeneric.h"

DrawableGeneric::DrawableGeneric(const SpriteSheet& ss) : Drawable(ss.getFilename()), spriteSheet(&ss)
{
  // rectIterator = nullptr;
  idAnimation = -1;
  animate(0);
}

DrawableGeneric::DrawableGeneric(const SpriteSheet& ss, const ValueDrawable& v) : Drawable(ss.getFilename(), v),spriteSheet(&ss)
{
  idAnimation = -1;
  // rectIterator = nullptr;
  animate(0);
}


DrawableGeneric::~DrawableGeneric(void)
{
}

#include <iostream>

bool DrawableGeneric::animate(int _idAnimation)
{
  std::cout << "animating: " << _idAnimation << std::endl;
  if (_idAnimation != idAnimation && spriteSheet->getAnimations().at(_idAnimation) != nullptr)
    {
      idAnimation = _idAnimation;
      // FIXME: lines too long.
      setAnimation(spriteSheet->getAnimations().at(idAnimation));
      std::cout << "animated" << std::endl;
    }
  else
    std::cout << "no animation" << std::endl;
  return true;
}

// void Drawable::_manual_next_frame()
// {
//   rectIterator->increase_iterator();
// }
