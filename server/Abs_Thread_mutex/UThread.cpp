#include "UThread.hpp"

UThread::UThread(const pthread_attr_t *parameter, void *(*function)(void *), void *ret)
{
  int res = 0;
  res = pthread_create(&this->_thread, parameter, function, ret);
  if (res == 0)
    {
      std::cout<<"Erreur start on thread !"<<std::endl;
      exit(0);
    }
}

bool UThread::THStart()
{
  std::cout<<"start thread"<<std::endl;
  return (true);
}

bool UThread::THWait()
{
  int res = 0;

  res = pthread_join(this->_thread, NULL);
  if (res)
    return (false);
  return (true);
}

bool UThread::THDestroy()
{
  return (true);
}
