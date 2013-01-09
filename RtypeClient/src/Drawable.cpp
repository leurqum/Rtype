#include "Drawable.h"


Drawable::Drawable(const SpriteSheet& ss) : SimpleDrawable(ss.getFilename()), spriteSheet(&ss)
{
  rectIterator = nullptr;
  animate(0);
}


Drawable::~Drawable(void)
{
}

Vector2<float> Drawable::getPosition() const
{
  return this->position;
}

void Drawable::setPosition(float x, float y)
{
  this->position.x = x;
  this->position.y = y;
}

const std::string& Drawable::getSpriteSheet() const
{
  return this->spriteSheet->getFilename();
}

const Rectangle<int>* Drawable::getRectSpriteSheet() const
{
  // FIXME: store the value when updating so we can return a reference instead of copying.
  // so we can modify it with the modifiers (bah that sentence..)
  return new Rectangle<int>(rectIterator->getValue());
}

void	Drawable::drawTo(IGraphicsManager* gm) const
{
  gm->draw((IDrawable*)this);
}


bool Drawable::animate(int idAnimation)
{
  if (rectIterator == nullptr || &rectIterator->a != spriteSheet->getAnimations().at(idAnimation))
    {
      std::cout << "animating [" << getSpriteSheet() << "]: " << idAnimation << std::endl;

      delete rectIterator;
      rectIterator = new Animation::Iterator(*spriteSheet->getAnimations().at(idAnimation));
    }
  return true;
}

void Drawable::addModifier(const Animation& a)
{
  modifiers.push_back(Animation::Iterator(a));
}

void Drawable::update(float elapsedTime)
{
  rectIterator->increase(elapsedTime);
  // TODO: update modifiers
  for (Animation::Iterator& i : modifiers)
    {
      i.increase(elapsedTime);
    }
}

void Drawable::_manual_next_frame()
{
	rectIterator->increase_iterator();
}
