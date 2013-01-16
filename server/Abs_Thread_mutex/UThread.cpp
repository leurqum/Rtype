#include "UThread.hpp"
#include "Game.hpp"

UThread::UThread(const pthread_attr_t *parameter, void *(*function)(void *), void *ret,void *s)
{
  int res = 0;
  //(*(Game *)(function))(NULL);
  // res = pthread_create(&this->_thread, parameter, (*(Game *)(function)), ret);
  res = pthread_create(&this->_thread, 0, function, s);
  if (res != 0)
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
