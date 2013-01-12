#pragma once

#include "Modifiable.h"
#include "IGraphicsManager.h"
#include "ValueDrawer.h"

class ADrawer : public Modifiable<ValueDrawer>
{
public:
  virtual void drawTo(IGraphicsManager*) const = 0;
/* protected: */
  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const = 0;
};
