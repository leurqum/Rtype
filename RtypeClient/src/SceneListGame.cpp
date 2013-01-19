#include "SceneListGame.h"

SceneListGame::SceneListGame(IScene& decoratedScene, Network* n) :
  ASceneHover(decoratedScene), menuGames("Back"), network(n)
{
  // first automaticly generated button is Back.

  refreshGames();
  // menuGames.addButton("Game 1"); // TODO: do a proper list..
  menuGames.setInitialValue(ValueDrawer(400, -160, 0, 0, 0));

  std::list<ValueDrawer > arriveAnimation;
  arriveAnimation.push_back(ValueDrawer());
  arriveAnimation.push_back(ValueDrawer(0, 320, 0, 0)); // TODO: scaling :D

  menuGames.setAnimation((new Animation<ValueDrawer>(arriveAnimation, 500, true)), 480); // 17 is the aver

  // it's to avoid unset values
  update(0);
}


SceneListGame::~SceneListGame(void)
{
}

IScene* SceneListGame::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);
  menuGames.checkInput(SceneManager::getInstance()->getInputManager());
  menuGames.update(elapsedTime);
  if (menuGames.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
    {
      if (menuGames.getSelectedId() == 0)
	{
	  decoratedScene.setToForeground();
	  delete network;
	  // FIXME: DAT FAT LEAK
	  return &this->decoratedScene;
	}
      else if (menuGames.getSelectedId() == 1)
	{
	  if (network->Create() == Protocol::VALIDE)
	    {
	      std::cout << "create da game" << std::endl;
	      return SceneManager::getInstance()->changeScene(new SceneGame(* (new SceneBackground()), network));
	    }
	  else
	    std::cout << "FAIL CREATING GAME" << std::endl;
	}
      else
	{
	  // minus 2 because 2 buttons before list
	  if (network->Join(menuGames.getSelectedId() - 2) == Protocol::VALIDE)
	    {
	      std::cout << "Join da game" << std::endl;
	      return SceneManager::getInstance()->changeScene(new SceneGame(* (new SceneBackground()), network));
	    }
	  else
	    std::cout << "FAIL JOIN " << std::endl;
	}
    }
  return this;
}

void SceneListGame::draw()
{
  ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  menuGames.drawTo(gm);
}

void SceneListGame::load()
{

}

void SceneListGame::unload()
{

}

void SceneListGame::setToBackground()
{

}

void SceneListGame::setToForeground()
{

}

void SceneListGame::refreshGames()
{
  std::cout << "ask list" << std::endl;
  games = network->GetGameList();
  std::cout << "list received" << std::endl;
  
  int i = 0;

  menuGames.addButton("New");
  for (Protocol::party g : games)
    {
      std::ostringstream oss;
      oss << "#";
      oss << i;
      oss << " ";
      oss << g.nb_players;
      oss << " players";
      menuGames.addButton(oss.str()); // TODO: do a proper list..
    }
}
