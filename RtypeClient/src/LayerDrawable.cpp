#include "LayerDrawable.h"

void LayerDrawable::addDrawable(IDrawable* add)
{
  drawables.push_back(add);
}

void LayerDrawable::removeDrawable(IDrawable* del)
{
  // TODO: delete the drawable
}

void LayerDrawable::setTranslation(const Vector2<float>& t)
{
  translation = t;
}

void LayerDrawable::translate(const Vector2<float>& t)
{
  translation.x += t.x;
  translation.y += t.y;
}

void LayerDrawable::drawTo(IGraphicsManager* gm) const
{
  for (IDrawable* d : drawables)
    {
      gm->draw(d, translation);
    }
}

void LayerDrawable::updateAll(float t)
{
  for (IDrawable* d : drawables)
    {
      d->update(t);
    }
}
