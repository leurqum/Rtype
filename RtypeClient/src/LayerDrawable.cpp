#include "LayerDrawable.h"

void LayerDrawable::addDrawable(IDrawer* add)
{
  drawers.push_back(add);
}

void LayerDrawable::removeDrawable(IDrawer* del)
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
  for (IDrawer* d : drawers)
    {
      // TODO: use d->drawTo(gm), and pass translation then.
      d->drawTo(gm); // FIXME: apply translation
    }
}

void LayerDrawable::update(float t)
{
  for (IDrawer* d : drawers)
    {
      d->update(t);
    }
}
