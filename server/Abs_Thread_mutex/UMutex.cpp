#include "UMutex.hpp"

UMutex::UMutex()
{
  _mutex = PTHREAD_MUTEX_INITIALIZER;
}

bool UMutex::MDestroy()
{
  int res = 0;
  
  res = pthread_mutex_destroy(&_mutex);
  if (res)
    return (false);
  return (true);
} 

bool UMutex::MLock()
{
  int res = 0;

  res = pthread_mutex_lock(&_mutex);
  if (res)
    return (false);
  return (true);
}

bool UMutex::MUnLock()
{
  int res = 0;

  res = pthread_mutex_unlock(&_mutex);
  if (res)
    return (false);
  return (true);
}

bool UMutex::MTryLock()
{
  int res = 0;

  res = pthread_mutex_trylock(&_mutex);
  if (res)
    return (false);
  return (true);
}
