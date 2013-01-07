#ifndef __COMMANDMANAGER__
#define __COMMANDMANAGER__

#include <string>
#include <vector>
#include <utility>

#include "Game.hpp"

class CommandManager
{
public:
  std::vector<std::pair<int, int> >_cmds;
  Game *_game;
public:
  CommandManager(Game *game) {_game = game;}
  void addCommandToQueue(int id, int cmd);
  void removeCommands();
};

#endif
