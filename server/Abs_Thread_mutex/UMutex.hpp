#ifndef __UMUTEX__
# define __UMUTEX__

#include <pthread.h>

class UMutex
{
private:
  pthread_mutex_t _mutex;
public:
  UMutex();
  virtual bool MDestroy(); 
  virtual bool MLock();
  virtual bool MUnlock();
  virtual bool MTrylock();
};


#endif
