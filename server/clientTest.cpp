#include "../protocol.h"
#include "./Abs_Socket/USocket.hpp"

int main(int ac, char ** av)
{
  if (ac != 2)
    {
      std::cerr << "missing argument" << std::endl;
      return 0;
    }
  ISocket  * sock = new USocket();
  //sock->setUDP(true); // probleme ...
  if (sock->connectToServer("127.0.0.1", av[1]) == false)
    return 0;

  int * header = new int[2];
  header[0] = Protocol::LOGIN;
  header[1] = sizeof(Protocol::login);

  Protocol::login datas;
  strcpy(datas.login, "login");
  strcpy(datas.passwd, "password");

  void * pckg = new char[(2 * sizeof(int)) + (sizeof(datas))];
  memcpy(pckg, (void*)header, 2 * sizeof(int));
  memcpy((((char*)pckg) + (2 * sizeof(int))), &datas, sizeof(datas));
  std::cout << "id:" << header[0] << std::endl;
  std::cout << "size:" << header[1] << std::endl;
  sock->sendv(((2 * sizeof(int)) + sizeof(datas)), pckg);
  sleep(1);
  return 0;
}
