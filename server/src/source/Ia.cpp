#include <dlfcn.h>
#include "../include/Ia.hpp"

Ia::Ia(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game *g)
{
  _id = id;
  _position = pos;
  _speed = speed;
  _height = h;
  _width = w;
  _direction = new Protocol::move();
  memset(_direction, 0, sizeof(Protocol::move));
  _direction->left = 1;
  _type = t;
  _game = g;
}

Ia *getInstance(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game* g)
{
  static int i = 0;
  Ia * ia;

  std::cout<<"CREATE"<<std::endl;
  if (i == 0)
    {
      std::cout<<"faire le dlopen bitch"<<std::endl;
      i++;
    } 
  return new Ia(id, pos, speed, h, w, t, g);
}

void Ia::move()
{
  _position.second = (_direction->top == 1) ?  _position.second + _speed : _position.second;
  _position.first = (_direction->right == 1) ? _position.first + _speed : _position.first;
  _position.second = (_direction->down == 1) ?  _position.second - _speed : _position.second;
  _position.first = (_direction->left == 1) ?  _position.first - _speed : _position.first;
}

void Ia::fire()
{
  RectangleCollisionDefinition *coll;

  if (_type == Protocol::ENEMY_EASY)
    {
      coll = new RectangleCollisionDefinition(this->getPosition(), 1, 1);
      _game->createBullet(1, std::pair<float, float>(-1, -1), _game->bulletList.size(), coll, 1, true,  Protocol::BULLET_LINEAR);
    }    
  else if (_type == Protocol::ENEMY_HARD)
    {
      coll = new RectangleCollisionDefinition(this->getPosition(), 50, 1);
      _game->createBullet(1, std::pair<float, float>(-1, -1), _game->bulletList.size(), coll, 1, true, Protocol::BULLET_RAYON);
    }
}

void Ia::update(double time)
{
  takeDecision(time);
  executeDecision();
}

void Ia::setDirection(Protocol::move *m)
{
  _direction = m;
}

void Ia::takeDecision(double)
{
  move();
}

void Ia::executeDecision()
{
}

float Ia::getPositionX()const
{
  return _position.first;
}

float Ia::getPositionY()const
{
  return _position.second;
}

std::pair<float, float> Ia::getPosition()const
{
  return _position;
}

int Ia::getSpeed()const
{
  return _speed;
}

float Ia::getHeight()const
{
  return _height;
}

float Ia::getWidth()const
{
  return _width;
}

int Ia::getId()const
{
  return _id;
}

Protocol::type_drawable Ia::getType()const
{
  return _type;
}

// extern "C" IIa *entry_point()
// {
//   IIa *ia = new Ia();
//   return ia;
// }
