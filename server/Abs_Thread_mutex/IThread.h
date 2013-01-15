#ifndef ITHREAD
# define ITHREAD

class IThread
{
public:

  virtual bool		THStart() = 0;
  virtual bool		THWait() = 0;
  virtual bool		THDestroy() = 0;
};

#endif
