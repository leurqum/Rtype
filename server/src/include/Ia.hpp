#ifndef __IALINEAR__
#define __IALINEAR__

#include "IIA.hpp"
#include "Game.hpp"


class Ia : public IIa
{
private:
  int				_id;
  std::pair<float, float>	_position;
  int				_speed;
  float				_height;
  float				_width;
  Protocol::move*		_direction;
  Protocol::type_drawable	_type;
  Game				*_game;
  Protocol::patern_enemie       _patern;
  bool				_canShoot;
  bool				_toShoot;
  long				_verif;
public:
  Ia(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game *g,Protocol::patern_enemie patern);
  virtual void move();
  virtual void fire();
  virtual void update(double time);
  virtual void takeDecision(double);
  virtual void executeDecision();
  virtual float getPositionX()const;
  virtual float getPositionY()const;
  virtual std::pair<float, float> getPosition()const;
  virtual int getSpeed()const;
  virtual float getHeight()const;
  virtual float getWidth()const;
  virtual int getId()const;
  virtual Protocol::type_drawable getType()const;
  virtual void setDirection(Protocol::move *m);
  void paternPack(int time);
  void paternSolo(int time);
  void paternLineToDiago(int time);
  void chooseDirection(double time);
};

Ia *getInstance(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game* g, Protocol::patern_enemie patern);

#endif
