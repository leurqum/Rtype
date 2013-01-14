#pragma once

#include "ADrawer.h"
#include "DrawableGeneric.h"
#include "DrawerUDrawable.h"
#include "FactoryDrawable.h"
#include "../../protocol.h"
#include "DrawableBar.h"

class Drawer2Bars : public ADrawer
{
 public:
  Drawer2Bars();

 protected:
  void _drawTo(IGraphicsManager*, const ValueDrawer&) const; // TODO: we should verride this and not the others

 public:
  virtual void drawTo(IGraphicsManager*) const override;
  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const override;

  virtual void update(float ms) override;
  void setBar1(int v);
  void setBar2(int v);
  int getBar1() const;
  int getBar2() const;
 private:
  DrawerUDrawable BarContainer;
  DrawableBar bar1;
  DrawableBar bar2;
};
