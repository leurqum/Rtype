// #include "Drawable.h"


// Drawable::Drawable(const SpriteSheet& ss) : SimpleDrawable(ss.getFilename()), spriteSheet(&ss)
// {
//   rectIterator = nullptr;
//   animate(0);
// }


// Drawable::~Drawable(void)
// {
// }

// const std::string& Drawable::getSpriteSheet() const
// {
//   return this->spriteSheet->getFilename();
// }

// const Rectangle<int>* Drawable::getRectSpriteSheet() const
// {
//   // FIXME: store the value when updating so we can return a reference instead of copying.
//   // so we can modify it with the modifiers (bah that sentence..)
//   return new Rectangle<int>(rectIterator->getValue());
// }

// bool Drawable::animate(int idAnimation)
// {
//   if (rectIterator == nullptr || &rectIterator->a != spriteSheet->getAnimations().at(idAnimation))
//     {
//       std::cout << "animating [" << getSpriteSheet() << "]: " << idAnimation << std::endl;

//       delete rectIterator;
//       rectIterator = new Animation::Iterator(*spriteSheet->getAnimations().at(idAnimation));
//     }
//   return true;
// }


// void Drawable::update(float elapsedTime)
// {
//   SimpleDrawable::update(elapsedTime);

//   rectIterator->increase(elapsedTime);
// }

// void Drawable::_manual_next_frame()
// {
//   rectIterator->increase_iterator();
// }

#include "Drawable.h"

Drawable::Drawable(const std::string& spriteSheet) : spriteSheetFilename(spriteSheet)
{

}

Drawable::Drawable(const std::string& spriteSheet, const ValueDrawable& v) : Modifiable(v), spriteSheetFilename(spriteSheet)
{

}

const std::string& Drawable::getSpriteSheetFilename() const
{
  return spriteSheetFilename;
}
