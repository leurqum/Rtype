#pragma once

#include "ADrawer.h"
#include "DrawableGeneric.h"
#include "FactoryDrawable.h"
#include "../../protocol.h"
#include "DrawerUDrawable.h"

class DrawerBullet : public ADrawer // NOTE: I do not inherit from DrawableDrawer because I might be interested in linking other drawers to my ship (explosions... bonuses..); and neither from DrawerLayer because... well, I want to have explicit verbose control over my attributes (maintenance stuff)
{
 public:
  DrawerBullet();

  virtual void drawTo(IGraphicsManager*) const override;
  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const override;

  virtual void update(float ms) override;
  virtual void setUpdate(const Protocol::drawable& u);

  int getId() const;
  DrawerUDrawable* createExplosion() const;
 private:
  int id;
  DrawableGeneric* drawable;
  Protocol::drawable* updater;
};
