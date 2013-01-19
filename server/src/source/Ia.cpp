#include <dlfcn.h>
#include "../include/Ia.hpp"

Ia::Ia()
{
  std::cout << "Une ia est nee en ce jour" << std::endl;
}

void Ia::init(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game *g, Protocol::patern_enemie patern)
{
  std::cout << "Une ia est initialisee en ce jour" << std::endl;
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
  _patern = patern;
  _canShoot = true;
  _toShoot = false;
  _verif = 0;
  if (patern == 1 || patern == 2 || patern == 3)
    _toShoot = true;
}

// Ia *getInstance(int id, std::pair<float, float> pos, int speed, float h, float w, Protocol::type_drawable t, Game* g
// 		, Protocol::patern_enemie  patern)
// {
//   static int i = 0;
//   Ia * ia;

//   if (i == 0)
//     {
//       std::cout<<"faire le dlopen bitch"<<std::endl;
//       i++;
//     } 
//   return new Ia(id, pos, speed, h, w, t, g, patern);
// }

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
      coll = new RectangleCollisionDefinition(_position, 20, 10);
      _game->createBullet(1, std::pair<float, float>(-1, -1), 0, coll, 1, true,  Protocol::BULLET_LINEAR);
    }    
  // else if (_type == Protocol::ENEMY_HARD)
  //   {
  //     coll = new RectangleCollisionDefinition(this->getPosition(), 18, 18);
  //     _game->createBullet(1, std::pair<float, float>(-1, -1), _game->bulletList.size(), coll, 1, true, Protocol::BULLET_RAYON);
  //   }
}

void Ia::update(double time)
{
  takeDecision(time);
  executeDecision();
  // move();
}

void Ia::setDirection(Protocol::move *m)
{
  _direction = m;
}

void Ia::chooseDirection(double time)
{
  if (this->_patern == 1)
    paternSolo(time);
  else if (this->_patern == 2)
    paternPack(time);
  else if (this->_patern == 4 || this->_patern == 5)
    paternLineToDiago(time);
}

void Ia::paternSolo(int time)
{
  (void)time;
  this->_direction->left = 1;
}

void Ia::paternLineToDiago(int time)
{
  (void)time;
  if (_position.first < XMAX / 2)
    {
      if (this->_patern == 5)
	this->_direction->down = 1;
      else
	this->_direction->top = 1;
      
      this->_canShoot = true;
    }
}

void Ia::paternPack(int time)
{
  if (time % 3 == 0)
    {
      if (_position.second >= 0 || _direction->top == 1)
	{
	  _direction->top = 0;
	  _direction->down = 1;
	}
      
      if (_position.second <= YMAX || this->_direction->down == 1)
	{
	  this->_direction->top = 1;
	  this->_direction->down = 0;
	}
    }
}


void Ia::takeDecision(double time)
{

   int		cadence = 4;
  
  if ((int)time % cadence == 0 && _verif != time)
    {
      // if (this->_canShoot == true)
      // 	this->_toShoot = true;
      // else
      // 	{
      // 	  this->_toShoot = false;
      // 	  chooseDirection(time);
      // 	}*
      fire();
      _verif =  time;
    }
}

void Ia::executeDecision()
{
  // if (_)
  //   fire();
  move();
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

extern "C" Ia *entry_point()
{
  Ia *ia = new Ia();
  return ia;
}
