#ifndef __UTHREAD__
# define __UTHREAD__

#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include "IThread.h"

class UThread : public IThread
{
private:
  pthread_t _thread;
public:
  UThread(const pthread_attr_t *parameter, void *(*function)(void *), void *ret, void *s);
  virtual bool THStart();
  virtual bool THWait();
  virtual bool THDestroy();
};

#endif
