#ifndef __IIA__
#define __IIA__

#include "../../../protocol.h"
#include "Game.hpp"

class IIa
{
public:
  virtual void init(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game *g,Protocol::patern_enemie patern) = 0;
  virtual void move() = 0;
  virtual void fire() = 0;
  virtual void update(double time) = 0;
  virtual void takeDecision(double) = 0;
  virtual void executeDecision() = 0;
  virtual float getPositionX()const = 0;
  virtual float getPositionY()const = 0;
  virtual std::pair<float, float> getPosition()const = 0;
  virtual int getSpeed()const = 0;
  virtual float getHeight()const = 0;
  virtual float getWidth()const = 0;
  virtual int getId()const = 0;
  virtual Protocol::type_drawable getType()const = 0;
  virtual void setDirection(Protocol::move *m) = 0;
  // virtual void init(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game *g,Protocol::patern_enemie patern) = 0;
  // virtual void move() = 0;
  // virtual void fire() = 0;
  // virtual void update(double time) = 0;
  // virtual void takeDecision(double) = 0;
  // virtual void executeDecision() = 0;

  // virtual float getPositionX()const = 0;
  // virtual float getPositionY()const = 0;
  // virtual std::pair<float, float> getPosition()const = 0;
  // virtual int getSpeed()const = 0;
  // virtual float getHeight()const = 0;
  // virtual float getWidth()const = 0;
  // virtual int getId()const = 0;
  // virtual Protocol::type_drawable getType()const = 0;
  // virtual void setDirection(Protocol::move *m) = 0;
};

#endif
