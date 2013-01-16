#ifndef __UMUTEX__
# define __UMUTEX__

#include <pthread.h>
#include "IMutex.h"

class UMutex : public IMutex
{
private:
  pthread_mutex_t _mutex;
public:
  UMutex();
  virtual bool MDestroy(); 
  virtual bool MLock();
  virtual bool MUnLock();
  virtual bool MTryLock();
};


#endif
