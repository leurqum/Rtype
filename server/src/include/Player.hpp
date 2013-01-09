#ifndef __PLAYER__
#define __PLAYER__

#include <string>

class Player
{
private:
  int		_id;
  std::string	_name;
  int		_life;
  
public:
  Player(int id, std::string name, int life);
  ~Player(void);
  int getId()const;
  std::string getName()const;
  int getLife()const;
  void setLife(int life);
};

#endif
