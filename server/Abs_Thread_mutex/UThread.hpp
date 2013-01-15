#ifndef __UTHREAD__
# define __UTHREAD__

#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include "Server.hpp"

class UThread
{
private:
  pthread_t _thread;
public:
  UThread(const pthread_attr_t *parameter, void *(*function)(void *), void *ret, Server *s);
  virtual bool THStart();
  virtual bool THWait();
  virtual bool THDestroy();
};

#endif
