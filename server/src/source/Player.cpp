#include "../include/Player.hpp"

Player::~Player(void)
{
}

Player::Player(int id, std::string name, ISocket *socket_tcp, ISocket *socket_udp)
{
  _id = id;
  _name = name;
  _socket_tcp= socket_tcp;
  _socket_udp = socket_udp;
}

int Player::getId()const
{
  return (_id);
}

std::string Player::getName()const
{
  return (_name);
}

ISocket *Player::getSocketTcp()const
{
  return (_socket_tcp);
}

ISocket *Player::getSocketUdp()const
{
  return (_socket_udp);
}
