#include "Player.hpp"

Player::~Player(void)
{
}

Player::Player(int id, std::string name, int life)
{
  _id = id;
  _name = name;
  _life = life;
}

int Player::getId()const
{
  return (_id);
}

std::string Player::getName()const
{
  return (_name);
}

int Player::getLife()const
{
  return (_life);
}

void Player::setLife(int life)
{
  _life = life;
}
