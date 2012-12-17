#ifndef ITHREAD
# define ITHREAD

class IThread
{
public:

  virtual bool		THSart() = 0;
  virtual bool		THWait() = 0;
  virtual bool		THDestroy() = 0;
};

#endif
