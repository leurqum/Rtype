#include "CommandManager.hpp"

void CommandManager::addCommandToQueue(int id, int cmd)
{
  _cmds.push_back(std::pair<int, int>(id, cmd));
}
void CommandManager::removeCommands()
{
  while (_cmds.size() > 0)
    _cmds.pop_back();
}
