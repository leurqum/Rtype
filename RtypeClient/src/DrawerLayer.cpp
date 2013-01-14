#include "DrawerLayer.h"

void DrawerLayer::drawTo(IGraphicsManager* gm) const
{
  for (const ADrawer* d : drawers)
    d->drawTo(gm, this->getModifiedValue());
}

void DrawerLayer::drawTo(IGraphicsManager* gm, const ValueDrawer& modifier) const
{
  for (const ADrawer* d : drawers)
    d->drawTo(gm, this->getModifiedValue() + modifier); // NOTE: That is why we might want to make a move constructor for ValueDrawer,
}

void DrawerLayer::addDrawer(const ADrawer* d)
{
  drawers.push_back(d);
}
