#include "UThread.hpp"
#include "Game.hpp"

void	*callHandle(void * data)
{
  Server * s = static_cast<Server *>(data);
  s->launchGame(s->gameList.size());
  return 0;
}

UThread::UThread(const pthread_attr_t *parameter, void *(*function)(void *), void *ret, Server *s)
{
  int res = 0;
  //(*(Game *)(function))(NULL);
  // res = pthread_create(&this->_thread, parameter, (*(Game *)(function)), ret);
  res = pthread_create(&this->_thread, 0, callHandle, static_cast<void*>(s));
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
