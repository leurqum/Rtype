
#include "../../protocol.h"
#include <SFML/Network.hpp>


int main(int ac, char** av)
{
  sf::UdpSocket s;
  sf::IpAddress ip = sf::IpAddress::getLocalAddress();

  s.bind(4243);
  
  while (1);
  {
    Protocol::drawable d;
    d.type = Protocol::type_drawable::SHIP;
    d.id = 0;
    d.xPosition = 20;
    d.yPosition = 20;
    s.send(&d, sizeof(d), ip, 4243);
  }
  return 0;
}
