#ifndef IMUTEX
# define IMUTEX

class IMutex
{
public:
  
  virtual bool		MUnLock() = 0;
  virtual bool		MLock() = 0;
  virtual bool		MDestroy() = 0;
  virtual bool		MTryLock() = 0;
};

#endif
