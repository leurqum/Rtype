#pragma once

#include "ADrawer.h"

#include "IGraphicsManager.h"

class DrawerLayer : public ADrawer
{
 public:
  virtual void drawTo(IGraphicsManager*) const override;

  virtual void addDrawer(const ADrawer*); // const, because I think pattern decorator should not modify its decorated target
 /* protected: */
  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const override;

  std::list<const ADrawer*> drawers;
};
